#include <IRremote.h>

int ENA=6;
int IN1=7;
int IN2=8;
int ENB=11;
int IN3=9;
int IN4=10;

int IRPin = 5;
IRrecv irrecv(IRPin);
decode_results results;
String lastVal = "stop";

void setup(){
 Serial.begin(9600);
 pinMode(ENA,OUTPUT);//output
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 
 digitalWrite(ENA,LOW);
 digitalWrite(ENB,LOW);//stop driving
 
 irrecv.enableIRIn();
}

void loop() {
  analogWrite(ENA,255);//start driving motorA
  analogWrite(ENB,255);//start driving motorB
  
  if (lastVal == "left" || lastVal == "right"){
    pause(0);
    lastVal="stop";
  }
  
  if (irrecv.decode(&results)) {
    //we only care about good results, bad results don't have the decode type correct
    if (results.decode_type == NEC) {
       String thisVal = String(results.value, HEX);
       Serial.println(thisVal);
    
      if (thisVal == "ff629d"){
        forward(1);
        lastVal= "forward";
      }
      else if (thisVal == "ffc23d"){
        left(1);
        lastVal = "left";
      }
      else if (thisVal == "ff22dd"){
        right(1);
        lastVal = "right";
      }
      else if (thisVal == "ffa857"){
        back(1);
        lastVal = "back";
      }
      else {
        pause(1);
        lastVal = "stop";
      }
    }
    irrecv.resume(); // Receive the next value
  }
}

void forward (int s) { 
 digitalWrite(IN1,HIGH); 
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
 delay (s * 100);      
} 

void back (int s) { 
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH); 
  digitalWrite (IN3, HIGH); 
  digitalWrite (IN4, LOW);   
  delay (s * 100);     
} 

void pause (int s) { 
 digitalWrite(IN1,LOW); 
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,LOW); 
 delay (s * 100); 
} 

void right (int s) { 
  digitalWrite (IN1, LOW); 
  digitalWrite (IN2, HIGH);   
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH); 
  delay (s * 100);   
} 

void left (int s) { 
  digitalWrite (IN1, HIGH); 
  digitalWrite (IN2, LOW);   
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW); 
  delay (s * 100); 
}

void slowRight (int s) { 
  digitalWrite (IN1, LOW); 
  digitalWrite (IN2, HIGH); 
  digitalWrite (IN3, LOW); 
  digitalWrite (IN4, LOW); 
  delay (s * 100); 
} 

void slowLeft (int s) { 
  digitalWrite (IN1, LOW); 
  digitalWrite (IN2, LOW); 
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH); 
  delay (s * 100); 
} 
