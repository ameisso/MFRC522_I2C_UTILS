//TX _TEENSY 9
//RX _TEENSY 10


void setup() 
{ 
  Serial.begin(9600);
  delay(1000);

  Serial2.begin(9600); 
  delay(1000); 
  Serial.println("init OK\n"); 

} 
void loop() 
{ 
  delay (10000);
  writeDataToBlock("salut c'est beverley",2);
  delay (10000);
  readDataInBlock(2) ;

}













