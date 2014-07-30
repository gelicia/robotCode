#include <Servo.h>

int ENA=6;
int IN1=7;
int IN2=8;
int ENB=11;
int IN3=9;
int IN4=10;

int inputPin = A0;    // Define pin ultrasonic signal reception 
int outputPin = A1;    // Define pin ultrasonic signal transmitter 

String lastVal = "stop";

Servo myservo;

void setup(){
 Serial.begin(9600);
 pinMode(ENA,OUTPUT);//wheels
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 
 pinMode (inputPin, INPUT);      // Define ultrasound input pin 
 pinMode (outputPin, OUTPUT);    // Define ultrasonic output pin

  myservo.attach(3); 
 
 digitalWrite(ENA,LOW);
 digitalWrite(ENB,LOW);//stop driving
}

void loop() {
  analogWrite(ENA,255);//start driving motorA
  analogWrite(ENB,255);//start driving motorB
  
  if (lastVal == "left" || lastVal == "right"){
    pause(0);
    lastVal="stop";
  }
  
 // myservo.write(90);
  float thisReading = getUSReading(90);
  if (thisReading <= 12){
    back(15);
  }
  else{
    forward(15);
  }
  
  /*for(int pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    float thisReading = getUSReading(pos);
    if (thisReading <= 12){
      back(15);
    }
    else{
      forward(15);
    }
    delay(15);                       // waits 15ms for the servo to reach the position 
    
  } 
  for(int pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    float thisReading = getUSReading(pos);
    if (thisReading <= 12){
      back(15);
    }
    else{
      forward(15);
    }
    delay(15);                       // waits 15ms for the servo to reach the position 
  } */
  
 
 
}

 float getUSReading (int pos) { 
   myservo.write(pos); 
   delay(5);
   digitalWrite (outputPin, LOW);     // Let ultrasonic transmitter low voltage 2 μ s 
   delayMicroseconds (2); 
   digitalWrite (outputPin, HIGH);    // Let ultrasonic transmitter high voltage 10 μ s, where at least 10 μ s 
   delayMicroseconds (10); 
   digitalWrite (outputPin, LOW);      // Maintain low voltage ultrasonic transmitter 
   float usDistance = pulseIn (inputPin, HIGH);    // Read worse time difference 
   usDistance = usDistance/5.8/10;         // Time to turn to the distance (unit: cm) 
   Serial.print ("usDistance: ");        // Output distance (unit: cm) 
   Serial.println (usDistance);           // Display the distance 
   return usDistance;
 } 

void forward (int s) { 
 digitalWrite(IN1,HIGH); 
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
 delay (s);      
} 

void back (int s) { 
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH); 
  digitalWrite (IN3, HIGH); 
  digitalWrite (IN4, LOW);   
  delay (s);     
} 

void pause (int s) { 
 digitalWrite(IN1,LOW); 
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,LOW); 
 delay (s); 
} 

void right (int s) { 
  digitalWrite (IN1, LOW); 
  digitalWrite (IN2, HIGH);   
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH); 
  delay (s);   
} 

void left (int s) { 
  digitalWrite (IN1, HIGH); 
  digitalWrite (IN2, LOW);   
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW); 
  delay (s); 
}

void slowRight (int s) { 
  digitalWrite (IN1, LOW); 
  digitalWrite (IN2, HIGH); 
  digitalWrite (IN3, LOW); 
  digitalWrite (IN4, LOW); 
  delay (s); 
} 

void slowLeft (int s) { 
  digitalWrite (IN1, LOW); 
  digitalWrite (IN2, LOW); 
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH); 
  delay (s); 
} 
