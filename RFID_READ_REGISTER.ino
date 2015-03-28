//TX _TEENSY 9
//RX _TEENSY 10

#define HWSERIAL Serial1
void setup() 
{ 
  Serial.begin(9600);
  delay(1000);

  HWSERIAL.begin(9600); 
  delay(1000); 
  Serial.println("init OK\n"); 

} 
void loop() 
{ 

  writeDataToBlock("INTER.WAV",2);

 //readDataInBlock(2) ;

}













