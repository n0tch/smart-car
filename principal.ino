#include <Ultrasonic.h>
#include <Servo.h>

/* Pinos do sensor ultrassonico*/
#define TRIGGER_PIN  12
#define ECHO_PIN     13

int i;//contador para media de distancia
float media=0;//variavel para média de distancia
float direita, esquerda;//variaveis para melhor escola

/*PINOS DOS MOTORES*/
int IN1 = 4;//A
int IN2 = 5;//A
int IN3 = 6;//B
int IN4 = 7;//B

/*Pino do buzzer*/
int buzzer = 3;

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Servo servo;

void frente();
void tras();
void vira_direita();
void vira_esquerda();
void parar();

void setup(){
  Serial.begin(9600);
  servo.attach(9);//seto a porta 9 para o envio de dados para o servo
  servo.write(90);//seto o braço do servo no meio.
  /*PINOS DOS MOTORES*/
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  pinMode(buzzer, OUTPUT);
}

void loop(){
  float cmMsec;
  long microsec = ultrasonic.timing();
  servo.write(90);
  for(i=0; i<10; i++){
    microsec = ultrasonic.timing();
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
    media = media + cmMsec;
  }
  
  //frente();
  
  media = media/10;
  
  if(media <= 50){
    parar();
    servo.write(0);
    Serial.println("Direita");
    delay(1000);
    microsec = ultrasonic.timing();
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
    direita = cmMsec;
    
    //delay(1000);
    
    servo.write(180);
    Serial.println("Esquerda");
    delay(1000);
    microsec = ultrasonic.timing();
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);    
    esquerda = cmMsec;
    
  }
  
  if(direita > esquerda){
    Serial.print("Direita melhor com ");
    Serial.println(direita);
    vira_direita();
    frente();
    //delay(100);
  }else if(direita < esquerda){
    Serial.print("Esquerda melhor com ");
    Serial.println(esquerda);
    vira_esquerda();
    frente();
    //delay(100);
  }else if(direita ){
    
  }else{
    Serial.println("Obstaculo nao encontrado.");
    frente();
  }
  
  media = 0;
  esquerda = direita = 0;
  
}

void frente(){
  //Motor A horario
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //Motor B Horario
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void tras(){
  //Motor A Anti-horario
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //Motor B Anti-horario
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void parar(){
  //Motor A Anti-horario
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  //Motor B Anti-horario
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void vira_esquerda(){
  //Gira o Motor A no sentido horario
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(400);
}

void vira_direita(){
  //Gira o Motor A no sentido horario
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(400);
}


