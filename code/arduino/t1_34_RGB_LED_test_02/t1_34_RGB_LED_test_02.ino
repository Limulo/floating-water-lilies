#define RED 11
#define GREEN 10
#define BLUE 9
int r_lum = 0;
int g_lum=85;
int b_lum=170;

void setup() 
{
//  Serial.begin(9600);
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

//  color(0, 0, 1);
//  color(0, 1, 0);
//  color(1, 0, 0);
  r_lum=(++r_lum)%255;
  g_lum+=2;
  g_lum%=255;
  b_lum+=4;
  b_lum%=255;

  mix(r_lum, g_lum, b_lum);

}

void color(int r, int g, int b)
{
  digitalWrite(RED, 1-r);
  digitalWrite(GREEN, 1-g);
  digitalWrite(BLUE, 1-b);
  delay(1000);
}

void mix(int r, int g, int b)
{
  analogWrite(RED, 255-r);
  analogWrite(GREEN, 255-g);
  analogWrite(BLUE, 255-b);
  delay(100);
  }
 

