int red = 8;
int green = 9;
int blue = 10;
int white = 11;

int sat = 0;
int lum = 1;

int re0 = 2;
int re1 = 3;
int lastRE = -1;
int reVal = 0;

float h = 0;
float s = 1.0;
float l = 1.0;

int r = 0;
int g = 0;
int b = 0;

void setup() 
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(white, OUTPUT);

  pinMode(re0, INPUT);
  pinMode(re1, INPUT);

  //Serial.begin(9600);
}

void loop() 
{
  updateRE();
  updateHSL();
  updateRGB();

  
  analogWrite(red, r);
  analogWrite(green, g);
  analogWrite(blue, b);
  
  analogWrite(white, round(l*(1.0-s)*255));
}

void updateRGB()
{
  float tempR;
  float tempG;
  float tempB;

    if(s == 0)
    {
      //Serial.println("grey");
      tempR = 1;
      tempG = 1;
      tempB = l;
    }
    else
    {
        float q = l < 0.5 ? l * (1.0 + s) : l + s - l * s;
        float p = 2.0 * l - q;
        tempR = hue2rgb(p, q, h + 1.0/3.0);
        tempG = hue2rgb(p, q, h);
        tempB = hue2rgb(p, q, h - 1.0/3.0);
        
        //Serial.println(String(tempR) + ", " + String(tempG) + ", " + String(tempB));
    }

    r = round(tempR * tempR * 255);
    g = round(tempG * tempG * 255);
    b = round(tempB * tempB * 255);
}

float hue2rgb(float p, float q, float t)
{
  if(t < 0.0) t += 1.0;
  if(t > 1.0) t -= 1.0;
  if(t < 1.0/6.0) return p + (q - p) * 6.0 * t;
  if(t < 1.0/2.0) return q;
  if(t < 2.0/3.0) return p + (q - p) * (2.0/3.0 - t) * 6.0;
  return p;
}

void updateHSL()
{
  h = float(reVal % 36) / 36.0;
  s = analogRead(sat) / 1024.0;
  l = analogRead(lum) / 1024.0;
}

void updateRE()
{
  int newRE = digitalRead(re0) + digitalRead(re1)*2;
  
  if(lastRE != newRE)
  {
    if(lastRE == 3)
    {
      if(newRE == 1)
      {
        reVal--;
      }
      else
      {
        reVal++;
      }
    }
    
    lastRE = newRE;
  }
}