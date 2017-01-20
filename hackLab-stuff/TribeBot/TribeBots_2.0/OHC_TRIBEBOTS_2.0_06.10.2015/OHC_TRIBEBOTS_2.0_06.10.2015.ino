
#include <IRremote.h>


/*
 * Over Head Controller TribeBots
 * author : moRenox
 * last update: 06.10.2015
 * http://dev.hacklabterni.org
 */
 



IRsend irsend;

boolean right;
boolean left;
boolean stopped;
boolean play_1;
boolean play_2;

byte com;


void setup()
{
  Serial.begin(9600);

}

void loop() {
  

if (Serial.available() > 0) {
  com = Serial.read();
  
  Serial.println(com, DEC);

   if (com == '1') {     Serial.println("UNO");}
   
 switch  (com) {
      case 49: // Play
        for (int i = 0; i < 3; i++) {
            irsend.sendSony(0x59C, 12); // Codifica Sony TV power code
            delay(40);
         }
    
         break;
      case 50: // Stop
        for (int i = 0; i < 3; i++) {
            irsend.sendSony(0x19C, 12); // Codifica Sony TV power code
            delay(40);
         }
        break;
       
      case 51: // Rewind LEFT
        for (int i = 0; i < 3; i++) {
            irsend.sendSony(0xD9C, 12); // Codifica Sony TV power code
            delay(40);
         }
        break;
      case 52: // Forward RIGHT
        for (int i = 0; i < 3; i++) {
            irsend.sendSony(0x39C, 12); // Codifica Sony TV power code
            delay(40);
         }
        break;
      case 53: // P3
        for (int i = 0; i < 3; i++) {
            irsend.sendSony(0x549D, 16); // Codifica Sony TV power code
            delay(40);
         }
        break;
      case 54: // P4
        for (int i = 0; i < 3; i++) {
            irsend.sendSony(0x5BC, 12); // Codifica Sony TV power code
            delay(40);
         }
        break;
      case 55: // Game of Life
        for (int i = 0; i < 3; i++) {
            irsend.sendSony(0x199D, 16); // Codifica Sony TV power code
            delay(40);
         }
        break;
   }
}
}
