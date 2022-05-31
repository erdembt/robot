#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  125 
#define SERVOMAX  575 

#define echoPin 5
#define trigPin 6

char dataIn = 'E'; char determinant; char det; int adim=80; int adim4,adim3=0; int adim2=10;
const int pinileri = 12; const int pingeri =4; const int pinsol = 7;   const int pinsag = 13;  

int maximumRange = 50;
int minimumRange = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pwm.begin();
  pwm.setPWMFreq(60);  
}
void loop() {

    int olcum = mesafe(maximumRange, minimumRange);
    Serial.print("olcum: "); Serial.println(olcum);
    det = check(); 
    while (det == 'O')
    {
        det= check();
    }
    while (det == 'P')
    {
        det= check();
    }
    
    while (det == 'K') 
    {
        det= check();
    }
    
    while (det == 'N') 
    {
        det= check();
    }
    while (det == 'B') //BACK
    {
     
        digitalWrite(pingeri, HIGH);
        digitalWrite(pinsol, HIGH);
        det = check();            
    }
    while (det == 'S') 
    {
        digitalWrite(pinileri, LOW);
        digitalWrite(pingeri, LOW);
        digitalWrite(pinsol, LOW);
        digitalWrite(pinsag, LOW);
        det = check();
    }
    int olcum2;
    if(olcum>25 || olcum==0)
    {
        det = check();
        while (det == 'F' && (olcum>10 || olcum==0)) //FORWARD
        {    
            olcum2 = mesafe(maximumRange, minimumRange);
            digitalWrite(pinileri, HIGH);
            digitalWrite(pinsag, HIGH);
            det = check(); 
            if(olcum2<25)
            {
                break;
            }
        }
        while (det == 'L') //LEFT
        {
            olcum2 = mesafe(maximumRange, minimumRange);
            digitalWrite(pinileri, HIGH);
            digitalWrite(pinsol, LOW);
            det = check();
            if(olcum2<25)
            {
                  break;
            }
        }
      while (det == 'R') //RIGHT
      {     
            olcum2 = mesafe(maximumRange, minimumRange);
            digitalWrite(pingeri, LOW);
            digitalWrite(pinsag, HIGH);  
            det = check();
            if(olcum2<25)
            {
                  break;
            }
      }
    }
    else
    {
        digitalWrite(pinileri, LOW);
        digitalWrite(pingeri, LOW);
        digitalWrite(pinsol, LOW);
        digitalWrite(pinsag, LOW);
    }  
}
int mesafe(int maxrange, int minrange)
{
  long duration, distance;

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  delay(40);

  if(distance >= maxrange || distance <= minrange)
  return 0;
  return distance;
}

int check()
{
if (Serial.available() >0) //SERIAL PORT CHECK
{
      dataIn = Serial.read(); 
          if (dataIn == 'O') // UP
          {     
              determinant = 'O';
              if(adim <161 )
              {
                adim=adim+10;
                Serial.print("servo 1 det: "); Serial.println(determinant);
                Serial.print("adim: ");Serial.println(adim);
                pwm.setPWM(0, 0, angleToPulse5(adim));
                delay(300);
              }
              else{
                adim=90;
                Serial.print("servo 1 det: "); Serial.println(determinant);
                Serial.print("adim: ");Serial.println(adim);
                pwm.setPWM(0, 0, angleToPulse6(adim));
                delay(300);
              }
          }
          else if (dataIn == 'P') // GRASP
          {     
              determinant = 'P';
              if(adim2 <51 )
              {
                adim2=adim2+10;
                Serial.print("servo 3 det: "); Serial.println(determinant);
                Serial.print("adim2: ");Serial.println(adim2);
                pwm.setPWM(2, 0, angleToPulse(adim2));
                delay(300);
              }
              else{
                adim2=10;
                Serial.print("servo 3 det: "); Serial.println(determinant);
                Serial.print("adim2: ");Serial.println(adim2);
                pwm.setPWM(2, 0, angleToPulse2(adim2));
                delay(300);
              }
          }
           else if (dataIn == 'N')  // DOWN
          {     
              determinant = 'N';
              if(adim4 <81 )
              {
                adim4=adim4+10;
                Serial.print("servo 4 det: "); Serial.println(determinant);
                Serial.print("adim4: ");Serial.println(adim4);
                pwm.setPWM(1, 0, angleToPulse7(adim4));
                delay(300);
              }
              else{
                adim4=10;
                Serial.print("servo 4 det: "); Serial.println(determinant);
                Serial.print("adim4: ");Serial.println(adim4);
                pwm.setPWM(1, 0, angleToPulse8(adim4));
                delay(300);
              }
          }
             else if (dataIn == 'K') // CENTRE
          {     
              determinant = 'K';
              if(adim3 <81 )
              {
                adim3=adim3+10;
                Serial.print("servo 2 det: "); Serial.println(determinant);
                Serial.print("adim3: ");Serial.println(adim3);
                pwm.setPWM(3, 0, angleToPulse3(adim3));
                delay(300);
              }
              else{
                adim3=0;
                Serial.print("servo 2 det: "); Serial.println(determinant);
                Serial.print("adim3: ");Serial.println(adim3);
                pwm.setPWM(3, 0, angleToPulse4(adim3));
                delay(300);
              }
          }

                else if (dataIn == 'F')
                {
                determinant = 'F';
                
                Serial.println(determinant);
                }
                else if (dataIn == 'B')
                {
                determinant = 'B';
                Serial.println(determinant);
                }
                else if (dataIn == 'L')
                {
                determinant = 'L';
                Serial.println(determinant);
                }
                else if (dataIn == 'R')
                {
                determinant = 'R';
                Serial.println(determinant);
                }
                
                else if (dataIn == 'S')
                {
                determinant = 'S';
                Serial.println(determinant);
                }
}
return determinant;
}

int angleToPulse(int ang){
  int pulse= map(ang,0,80,SERVOMIN,SERVOMAX);
  Serial.print("Angle: "); Serial.print(ang);
  Serial.print(" pulse: "); Serial.println(pulse);
  return pulse;
}
int angleToPulse2(int ang){
  int pulse= map(ang,80,0,SERVOMAX,SERVOMIN);
  Serial.print("Angle: "); Serial.print(ang);
  Serial.print(" pulse: "); Serial.println(pulse);
  return pulse;
}
int angleToPulse3(int ang){
  int pulse= map(ang,0,80,SERVOMIN,SERVOMAX);
  Serial.print("Angle: "); Serial.print(ang);
  Serial.print(" pulse: "); Serial.println(pulse);
  return pulse;
}
int angleToPulse4(int ang){
  int pulse= map(ang,80,0,SERVOMAX,SERVOMIN);
  Serial.print("Angle: "); Serial.print(ang);
  Serial.print(" pulse: "); Serial.println(pulse);
  return pulse;
}
int angleToPulse5(int ang){
  int pulse= map(ang,0,160,SERVOMIN,SERVOMAX);
  Serial.print("Angle: "); Serial.print(ang);
  Serial.print(" pulse: "); Serial.println(pulse);
  return pulse;
}
int angleToPulse6(int ang){
  int pulse= map(ang,160,0,SERVOMAX,SERVOMIN);
  Serial.print("Angle: "); Serial.print(ang);
  Serial.print(" pulse: "); Serial.println(pulse);
  return pulse;
}
int angleToPulse7(int ang){
  int pulse= map(ang,0,100,SERVOMIN,SERVOMAX);
  Serial.print("Angle: "); Serial.print(ang);
  Serial.print(" pulse: "); Serial.println(pulse);
  return pulse;
}
int angleToPulse8(int ang){
  int pulse= map(ang,100,0,SERVOMAX,SERVOMIN);
  Serial.print("Angle: "); Serial.print(ang);
  Serial.print(" pulse: "); Serial.println(pulse);
  return pulse;
}
