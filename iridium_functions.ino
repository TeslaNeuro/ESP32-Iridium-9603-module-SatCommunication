/*
 * Name: iridium_functions
 * Version: 02
 * Author: Arshia Keshvari
 * Date: 15th of Febuary 2025
 * 
 * Description:
 * This script holds the code for the following functions
 * 'check9603linkquality' Requests the link quality and returns on serial port
 * 'get9603time' Requests the network time and returns on serial port
 * 'send9603message' sends a message to the network in for form of a char*
 * 'check9603recieve' checks for messages on the network
 */

void start9603() {
  Serial.println("Starting modem...");

  err = modem.begin();
  Serial.print("Modem begin result: ");
  Serial.println(err);

  if (err != ISBD_SUCCESS) {
    Serial.print("Begin failed: error ");
    Serial.println(err);

    if (err == ISBD_NO_MODEM_DETECTED) {
      Serial.println("No modem detected: check wiring.");
    } else if (err == ISBD_SERIAL_FAILURE) {
      Serial.println("Serial failure: check connections.");
    } else if (err == ISBD_PROTOCOL_ERROR) {
      Serial.println("Protocol error: check AT commands.");
    } else {
      Serial.println("Modem initialization failed.");
    }

    return;
  }

  Serial.println("Modem initialized successfully.");
}



void check9603FWversion(){
  err = modem.getFirmwareVersion(version, sizeof(version));
  if (err != ISBD_SUCCESS){
     Serial.print("FirmwareVersion failed: error ");
     Serial.println(err);
     return;
  }
  Serial.print("Firmware Version is ");
  Serial.println(version);
}

void check9603linkquality(){
  err = modem.getSignalQuality(signalQuality);
  if (err != ISBD_SUCCESS){
    Serial.println(err);    
    Serial.print("SignalQuality failed: error ");
    return;
  }
  Serial.print("On a scale of 0 to 5, signal quality is currently ");
  Serial.print(signalQuality);
  Serial.print("(2 or higher prefered)\n");
}

void send9603message(char* message){
  Serial.print("Message ready to send is '");
  Serial.print(message);
  Serial.print("'\n");
  Serial.print("Trying to send the message.  This might take several minutes.\n");
  err = modem.sendSBDText(message);
  if (err != ISBD_SUCCESS){
    Serial.print("sendSBDText failed: error ");
    Serial.println(err);
    if (err == ISBD_SENDRECEIVE_TIMEOUT)
      Serial.print("Try again with a better view of the sky.\n");
  }
  else{
    Serial.print("Message '");
    Serial.print(message);
    Serial.print("' sent successfully...\n");
  }
}

void get9603time(){
  err = modem.getSystemTime(t);
  if (err == ISBD_SUCCESS)
   {
      char buf[32];
      sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d",
         t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
      Serial.print("Iridium time/date is ");
      Serial.println(buf);
   }
   else if (err == ISBD_NO_NETWORK){
      Serial.println("No network detected.  Waiting 10 seconds.");
   }
   else {
      Serial.print("Unexpected error ");
      Serial.println(err);
      return;
   }
}

void check9603recieve(){
  err = modem.sendReceiveSBDText(NULL, buffer, bufferSize);    
  if (err != ISBD_SUCCESS){
      Serial.print("sendReceiveSBD* failed: error ");
      Serial.println(err);
    }
  else {
    messageSent = true;
    Serial.print("Inbound buffer size is ");
    Serial.println(bufferSize);
    for (int i=0; i<bufferSize; ++i){
      Serial.print(buffer[i], HEX);
      if (isprint(buffer[i])){
          Serial.print("(");
          Serial.write(buffer[i]);
          Serial.print(")");
        }
        Serial.print(" ");
      }
      Serial.println();
      Serial.print("Messages remaining to be retrieved: ");
      Serial.println(modem.getWaitingMessageCount());
    }
}

#if DIAGNOSTICS
void ISBDConsoleCallback(IridiumSBD *device, char c)
{
  Serial.write(c);
}

void ISBDDiagsCallback(IridiumSBD *device, char c)
{
  Serial.write(c);
}
#endif