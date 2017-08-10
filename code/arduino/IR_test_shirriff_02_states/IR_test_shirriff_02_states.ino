#include <IRremote.h>

/* 
*  Default is Arduino pin D11. 
*  You can change this to another available Arduino Pin.
*  Your IR receiver should be connected to the pin defined here
*/
int RECV_PIN = 11; 
int LED = 13;

IRrecv irrecv(RECV_PIN, LED);

decode_results results;
unsigned long value;

boolean bBusyState = false;
unsigned long initialTime;
unsigned int busyTime = 2000;


// SETUP /////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13( true );
  initialTime = 0;
}

// LOOP //////////////////////////////////////////////////////
void loop() {
  if( !bBusyState ) 
  {
    if ( irrecv.decode(&results) ) 
    {
      value = results.value;
      Serial.println(value, HEX);
      if( value == 0xC1C7847B )
      {
        bBusyState = true;
        initialTime = millis();
        return;
      }
            
      irrecv.resume(); // Receive the next value
      delay(5);
    }
  }
  else
  {
    if(millis()-initialTime < busyTime )
    {
      Serial.println("\tbusy");
    }
    else
    {
      bBusyState = false;
      irrecv.resume(); // Receive the next value
    }
  }
}
