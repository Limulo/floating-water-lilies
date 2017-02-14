#define RED 11
#define GREEN 10
#define BLUE 9
//void cycle_color(int r, int g, int b);

void setup() 
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  int i;
  for(i=BLUE; i<=RED; i++)
  {
    digitalWrite(i, HIGH); // LED OFF
   }

}

void loop() {

  color(0, 0, 1);
  color(0, 1, 0);
  color(1, 0, 0);
}

void color(int r, int g, int b)
{
  digitalWrite(RED, 1-r);
  digitalWrite(GREEN, 1-g);
  digitalWrite(BLUE, 1-b);
  delay(1000);
}

