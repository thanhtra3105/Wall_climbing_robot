#include <Servo.h>

Servo ESC;
int ena = 6;
int in1 = 10;
int in2 = 9;
int in3 = 8;
int in4 = 7;
int enb = 5;
int tocdo = 100;
int tocdo_quat = 1100;
char status;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  ESC.attach(3);
  ESC.writeMicroseconds(1100);
  delay(3000);



}

void loop() {
  // put your main code here, to run repeatedly:
  //tien();
  //lui();

  if (Serial.available()) {
    status = Serial.read();
    Serial.println(int(status));
  }
  if (status == 'U') {
    tien();
    Serial.println("Xe dang tien");
  } else if (status == 'D') {
    lui();
    Serial.println("Xe dang lui");
  } else if (status == 'L') {
    trai();
    Serial.println("Xe dang re trai");
  } else if (status == 'R') {
    phai();
    Serial.println("Xe dang re phai");
  } 
  else if (status == '+') {
    delay(50);
    if (tocdo >= 0 && tocdo < 255)
      tocdo += 5;
    Serial.println(tocdo);
  }
  else if (status == '-') {
    delay(50);
    if (tocdo > 0 && tocdo <= 255)
      tocdo -= 5;
    Serial.println(tocdo);
  }
  else if (status == 'S') {
    dung();
    Serial.println("Xe dang dung");
  }
  else if(int(status) <= 50)
  {
    tocdo_quat = map(int(status),0,50,1100,1900);
    Serial.println(tocdo_quat);
    ESC.writeMicroseconds(tocdo_quat);
  }
  
}

void tien() {
  analogWrite(ena, tocdo+10);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  analogWrite(enb, tocdo);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}
void lui() {
  analogWrite(ena, tocdo+10);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  analogWrite(enb, tocdo);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}
void phai() {
  analogWrite(ena, tocdo+10);  // banh ben trai chay tien
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  analogWrite(enb, 15); // phai lui
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}

void trai() {
  analogWrite(ena, 15); // trai lui
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  analogWrite(enb, tocdo);  // phai
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}
void dung() {
  analogWrite(ena, 30);
  analogWrite(enb, 30);
}