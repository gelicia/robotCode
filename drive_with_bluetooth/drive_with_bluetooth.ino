#include <SoftwareSerial.h>

int ENA=6;
int IN1=7;
int IN2=8;
int ENB=11;
int IN3=9;
int IN4=10;
SoftwareSerial mySerial(3,2); //rx, tx

String lastVal = "stop";

void setup(){
 mySerial.begin(115200);  
 pinMode(ENA,OUTPUT);//output
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 
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
  
  char thisVal = ' ';
  
  if (mySerial.available()){
    thisVal = mySerial.read();
    mySerial.println(thisVal);
  } 
    
  if (thisVal == 'w' || thisVal == 'W'){
    forward(1);
    lastVal= "forward";
  }
  else if (thisVal == 'd' || thisVal == 'D'){
    left(1);
    lastVal = "left";
  }
  else if (thisVal == 'a' || thisVal == 'A'){
    right(1);
    lastVal = "right";
  }
  else if (thisVal == 's' || thisVal == 'S'){
    back(1);
    lastVal = "back";
  }
  else if (thisVal == 'z' || thisVal == 'Z'){
    pause(1);
    lastVal = "stop";
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
