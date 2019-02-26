#include <IRremote.h>
//telecomanada
const int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;

//led
int LED1=13;

#define relay1 2
#define relay2 3
#define relay3 4
#define relay4 5
#define trigPin1 6
#define echoPin1 7
#define trigPin2 8
#define echoPin2 9
#define trigPin3 10
#define echoPin3 11
 
long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;
 
void setup()
{
  //telecomanada
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);


  //LED
  pinMode(LED1,OUTPUT);

  //ULTRASONIC
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}
 
void play() 
{
SonarSensor(trigPin1, echoPin1);
RightSensor = distance;
Serial.print("RightSensor  ");
Serial.print(RightSensor);
SonarSensor(trigPin2, echoPin2);
LeftSensor = distance;
Serial.print("LeftSensor  ");
Serial.print(LeftSensor);
SonarSensor(trigPin3, echoPin3);
FrontSensor = distance;
Serial.print("FrontSensor  ");
Serial.print(FrontSensor);


if(FrontSensor<=20 && LeftSensor<=20)
{
  Serial.println("Turn right");
  
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,LOW);
  digitalWrite(relay3,HIGH);
  digitalWrite(relay4,LOW);
}
else if(FrontSensor<=20 && RightSensor<=20)
{
  Serial.println("Turn left");
  
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,LOW);
  digitalWrite(relay4,HIGH);
}
else 
{
  Serial.println("Forward");
  
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
  digitalWrite(relay4,LOW);
}
delay(5);
}

 
void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration/58.2; 
}

void translate(){

  Serial.println(results.value, HEX);
  switch(results.value){
      case 0xFFA25D:
      {
        play();
        digitalWrite(LED1,HIGH);
        break;
      }
      case 0xE318261B:
      {
         play();
        digitalWrite(LED1,HIGH);
        break;
      }
      case 0xFFE21D:
      {
        oprire();
        digitalWrite(LED1,LOW);
        break;
      }
      default:
      {
        oprire();
        digitalWrite(LED1,LOW);
      }
    
  }
  //delay(50);
}
void loop(){
  if (irrecv.decode( & results)) 
  {
    translate();
    irrecv.resume();
  }
  translate();
}

void oprire(){
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
}
