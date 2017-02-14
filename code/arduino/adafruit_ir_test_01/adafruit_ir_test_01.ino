// We need to use the 'raw' pin reading methods
// because timing is very important here and the digitalRead()
// procedure is slower!

// Digital pin #2 is the same as Pin D2 see
// http://arduino.cc/en/Hacking/PinMapping168 for the 'raw' pin mapping
#define IRpin_PIN PIND
#define IRpin 2

// for MEGA use these!
//#define IRpin_PIN PINE
//#define IRpin 4

// the maximum pulse we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 65000

// what our timing resolution should be, larger is better
// as its more 'precise' - but too large and you wont get
// accurate timing
#define RESOLUTION 20

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[100][2]; // pair is high and low pulse
uint8_t currentpulse = 0; // index for pulses we're storing

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Ready to decode IR!");
}

void loop(void) 
{
  
  // while (digitalRead(IRpin)) { // this is too slow!
  while (IRpin_PIN & (1 << IRpin))
  {
    // pin is still HIGH
    
    Serial.println(1);
    delayMicroseconds(RESOLUTION);
  }

  
  
  // same as above
  while (! (IRpin_PIN & _BV( IRpin )) ) 
  {
     // pin is still LOW
    
     delayMicroseconds(RESOLUTION);
     Serial.println(0);
  }

  delay(10);
  
}


void printpulses(void) 
{
  Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
  
  for (uint8_t i = 0; i < currentpulse; i++) 
  {
    Serial.print(pulses[i][0] * RESOLUTION, DEC);
    Serial.print(" usec, ");
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.println(" usec");
  }
  
  // print it in a 'array' format
  Serial.println("int IRsignal[] = {");
  Serial.println("// ON, OFF (in 10's of microseconds)");
  
  for (uint8_t i = 0; i < currentpulse-1; i++) 
  {
    Serial.print("\t"); // tab
    Serial.print(pulses[i][1] * RESOLUTION / 10, DEC);
    Serial.print(", ");
    Serial.print(pulses[i+1][0] * RESOLUTION / 10, DEC);
    Serial.println(",");
  }
  
  Serial.print("\t"); // tab
  Serial.print(pulses[currentpulse-1][1] * RESOLUTION / 10, DEC);
  Serial.print(", 0};");
}
