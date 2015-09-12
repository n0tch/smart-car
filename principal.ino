#include <Ultrasonic.h>
#include <Servo.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     13

int i;//contador para media de distancia
float media=0;
float direita, esquerda;

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Servo servo;

void setup(){
  Serial.begin(9600);
  servo.attach(9);//seto a porta 9 para o envio de dados para o servo
  servo.write(90);//seto o braço do servo no meio.
}

void loop(){
  float cmMsec;
  long microsec = ultrasonic.timing();
  
  for(i=0; i<10; i++){
    microsec = ultrasonic.timing();
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
    media = media + cmMsec;
  }
  
  media = media/10;
  
  if(media <= 30){
    servo.write(0);
    Serial.println("Direita");
    delay(1000);
    microsec = ultrasonic.timing();
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
    direita = cmMsec;
    
    delay(1000);
    
    servo.write(180);
    Serial.println("Esquerda");
    delay(1000);
    microsec = ultrasonic.timing();
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);    
    esquerda = cmMsec;
    
  }
  
  Serial.print("Direita: ");
  Serial.println(direita);
  Serial.print("Esquerda: ");
  Serial.println(esquerda);
  
  media = 0;
  esquerda = direita = 0;
  
  delay(1000);
}
