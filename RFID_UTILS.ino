
byte readCardType()
{
  Serial2.write(0x01);
  byte C;
  while (Serial2.available())
  {
    C = Serial2.read();
  }
  return C;
}

void readUID(byte *uid)
{
  Serial2.write(0x02);
  int increment = 0;
  while (Serial2.available())
  {
    byte C = Serial2.read();
    if (C<16) C=0;
    uid[increment] = C;
    increment++;
    delay(10);
  }
}

void printUID(byte *uid)
{
  if (uid[0] != 0 || uid[1] != 0 || uid[2] != 0 || uid[3] != 0)
  {
    for (int i = 0 ; i < 4 ; i++) 
    {
      Serial.print(uid[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}

void sendStringCommand(String command)
{
  int CMD[64];
  int comlen =0;
  for (int i = 0 ; i < command.length() ; i++)
  {
    char c = command.charAt(i);
    if( c != ' ')
    {
      int a = convertHexDigit(c); 
      if(a>=0)
      {
        CMD[comlen] = a; 
        comlen++;
      }
    }
  }
  for(int i=0; i<comlen; i+=2)
  {
    int c = Serial2.write( CMD[i]*16 + CMD[i+1]);
  }
}


void readDataInBlock(int blockNumber) 
{
  String blockNumberString = " "; 
  String keyType = "00"; 
  String key = "FF FF FF FF FF FF"; 
  blockNumberString =  String(blockNumber, HEX);
  if ( blockNumberString.length() == 1) 
  {
    blockNumberString = "0"+blockNumberString;
  }

  String s = "AB 0A 03 "+ blockNumberString + " " + keyType + " " + key;
  sendStringCommand(s); 
  String response; 
  while (Serial2.available()) {
    byte C = Serial2.read();
    if (C<16) response += "0";
    response += decToHex(C);
    response += " ";
  }
  if (! response.startsWith("AB 12 03"))
  {
    Serial.println("error reading data");
  }
  else
  {
    String humanRedableResponse ="";
    response = response.substring(9);
    printResponse(response);
  }
  delay(100);
}

void writeDataToBlock(String data, int blockNumber)
{
  //convert data to HEX  
  String hexData ="";
  data += " "; 
  char charArray[data.length()];
  data.toCharArray(charArray, data.length());
  for (int i = 0 ; i < data.length() ; i++)
  {
    hexData += charToHex(charArray[i]);
    hexData += " ";
  }
  hexData = hexData.substring(0, hexData.length()-3);

  int charsToAdd = 16- data.length() ; 
  for (int i = 0 ; i < charsToAdd+1 ; i++)
  {
    hexData += " FF";
  }
  String blockNumberString = " "; 
  String keyType = "00"; 
  String key = "FF FF FF FF FF FF"; 
  blockNumberString =  String(blockNumber, HEX);
  if ( blockNumberString.length() == 1) 
  {
    blockNumberString = "0"+blockNumberString;
  }

  String s = "AB 1A 04 "+ blockNumberString + " " + keyType + " " + key+" "+ hexData;
  sendStringCommand(s); 
  String response; 
  while (Serial2.available()) {
    byte C = Serial2.read();
    if (C<16) response += "0";
    response += decToHex(C);
    response += " ";
  }
  if (! response.startsWith("AB 02 04"))
  {
    Serial.println("error writing data");
  }
  else
  {
    Serial.println("data writen");
  }
  delay(1000);
}

void printResponse(String response) 
{
  String humanRedableResponse ="";
  for(int i=0; i<response.length(); i+=3)
  {
    humanRedableResponse += hexToChar(response.substring(i,i+2));
  }
  Serial.println(humanRedableResponse);
}

void standbyMode()
{
  sendStringCommand("AB 02 10"); 
  String response; 
  while (Serial2.available()) {
    byte C = Serial2.read();
    if (C<16) response += "0";
    response += decToHex(C);
    response += " ";
  }
  if (! response.startsWith("AB 02 10 "))
  {
    Serial.println("fail to standby module");
  }
}




