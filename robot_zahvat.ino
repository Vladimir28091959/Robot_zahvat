#include <Servo.h>           //подключение к библиотеке Servo
Servo myservo;               //название
int pos=0, n=1;                 
int ledPin1=7;               //подключение Светодиода1 на порт 7
int ledPin2=6;               //подключение Светодиода2 на порт 6
int ledPin3=5;               //подключение Светодиода3 на порт 5
int buttonPin=10;            //подключение Кнопки1 на порт 10 
int buttonPin2=4;            //подключение Кнопки2 на порт 4
const int POT=1; 
int valpot = 0; 
int angleServo = 0;          //начальный угол отклонения сервопривода 
long duration, sm; 
#define PIN_TRIG 12 
#define PIN_ECHO 11 
boolean buttonState=HIGH;    //начальное положение Кнопки1
boolean buttonState2=HIGH;   //начальное положение Кнопки2

void setup() {               //начало цикла
Serial.begin (9600);         //открываем последовательное соединение
myservo.attach(9);
pinMode(PIN_TRIG, OUTPUT);   //устанавливается режим порта-выход
pinMode(PIN_ECHO, INPUT);    //устанавливается режим порта-вход
pinMode(ledPin1, OUTPUT);    //устанавливается режим порта-выход
pinMode(ledPin2, OUTPUT);    //устанавливается режим порта-выход
pinMode(ledPin3, OUTPUT);    //устанавливается режим порта-выход
pinMode(buttonPin, INPUT);   //устанавливается режим порта-вход
pinMode(buttonPin2, INPUT);  //устанавливается режим порта-вход
}                                          //конец цикла

int echo() { digitalWrite(PIN_TRIG, LOW);   //функция
delayMicroseconds(2);     //количество микросекунд на которое останавливается программа
digitalWrite(PIN_TRIG, HIGH);     //включаем дальномер
delayMicroseconds(10);   //количество микросекунд на которое останавливается программа  
digitalWrite(PIN_TRIG, LOW);     //выключаем дальномер
duration = pulseIn(PIN_ECHO, HIGH);  //длительность высокого сигнала на пине Echo
sm = duration /58;            //расстояние в см
Serial.print("distance: ");   //вывод значения в Serial Monitor
Serial.print(sm);              //вывод значений в см
Serial.println("sm");
delay(50);    //остановка программы на заданное время
}     //конец цикла

int mode1(){   //режим работы №1
valpot = analogRead(POT);   //считаем направление с потенциометра 
angleServo=map(valpot,0,1023,0,110);   //значение угла сервопривода 
myservo.write(angleServo);   //установление сервопривода в заданное положение
delay(15);
}    //конец цикла

int mode2(){     //режим работы №2
echo();
buttonState=digitalRead(buttonPin);
if (buttonState==HIGH) {      //если Кнопка1 в рабочем состоянии
if (sm < 10) {
pos+=8;   //запись арифметических действий над переменной
myservo.write(pos);
digitalWrite(ledPin3, HIGH);   //включает Светодиод3
} else if (sm < 20) {
pos+=4;   //запись арифметических действий над переменной 
myservo.write(pos);
digitalWrite(ledPin3, HIGH);  //включает Светодиод3
} else if (sm < 40) {
pos+=2;   //запись арифметических действий над переменной
myservo.write(pos);
digitalWrite(ledPin3, HIGH);    //включает Светодиод3
} else {
pos-=10;  //запись арифметических действий над переменной
myservo.write(pos);
digitalWrite(ledPin3, HIGH);   //включает Светодиод3
}
if (pos>=110)  {
pos=110;   
digitalWrite(ledPin1, HIGH);   //включает Светодиод1
digitalWrite(ledPin3, LOW);   //выключает Светодиод3
}
if (pos<=0) {
pos=0;
digitalWrite(ledPin2, HIGH);  //включает Светодиод2
digitalWrite(ledPin3, LOW);  //выключает Светодиод3
}
if (pos<110 & pos>0) {
digitalWrite(ledPin1, LOW);   //выключает Светодиод1
digitalWrite(ledPin2, LOW);   //выключает Светодиод2
delay(10);
}    //конец цикла
} else { pos=0;
myservo.write(pos);
digitalWrite(ledPin1, LOW);   //выключает Светодиод1
digitalWrite(ledPin2, LOW);   //выключает Светодиод2
digitalWrite(ledPin3, LOW);  //включает Светодиод3
delay(1000);
}}   //конец цикла

void loop() {                               //начало цикла
buttonState2=digitalRead(buttonPin2);
if (buttonState2==LOW) {    //если Кнопка2 выключена 
n=n+1;
delay(200);
if (n>2) {
n=1;
}}                                     //конец цикла
switch(n) {                //начало цикла
case 1: mode1(); digitalWrite(ledPin1, LOW);           //выключает Светодиод1
digitalWrite(ledPin2, LOW); digitalWrite(ledPin3, LOW); break; //выключает Светодиод3
case 2: mode2(); break;
} }          //конец цикла
