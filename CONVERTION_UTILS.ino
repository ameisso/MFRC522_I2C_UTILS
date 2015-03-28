
int convertHexDigit(byte c)
{
  if (c >= '0' && c <= '9') {
    return c - '0';
  } 
  else if (c >= 'a' && c <= 'f') {
    return c - 'a' + 10;
  } 
  else if (c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  } 
  else 
  {
    Serial.println("error in Hex convertion");
    return -1;   // getting here is bad: it means the character was invalid
  }
}

String decToHex(byte decValue) 
{
  return String(decValue, HEX);
}

unsigned int hexToDec(String hexString) {
  unsigned int decValue = 0;
  int nextInt;
  for (int i = 0; i < hexString.length(); i++) {
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);
    decValue = (decValue * 16) + nextInt;
  }
  return decValue;
}

char hexToChar(String input)
{
  return hexNibbleToChar(input[0]) * 16 + hexNibbleToChar(input[1]);
}

String charToHex(char c)
{
  return String(c, HEX);
}

char hexNibbleToChar(char nibble)
{
  if (nibble >= '0' && nibble <= '9')
    return nibble - '0';
  else if (nibble >= 'a' && nibble <= 'f')
    return 10 + nibble - 'a';
  else
    return 10 + nibble - 'A';
}

