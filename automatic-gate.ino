#include <Servo.h> 

int distancia = 0; 

int ledAcesso = 0;

const int portaSensor1 = 12; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int portaSensor2 = 13; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)

////int posicaoInicial = 0;

long readUltrasonicDistance(int PortaSensor1, int PortaSensor2) 
{
pinMode(PortaSensor1, OUTPUT); // Clear the trigger 
digitalWrite(PortaSensor1, LOW); 
delayMicroseconds(2);
// Sets the trigger pin to HIGH state for 10 microseconds 
digitalWrite(PortaSensor1, HIGH); 
delayMicroseconds(10);
digitalWrite(PortaSensor1, LOW);
pinMode(PortaSensor2, INPUT);
// Reads the echo pin, and returns the sound wave travel time in microseconds
return pulseIn(PortaSensor2, HIGH);
}

Servo servo_2;

//definindo uma posição inicial fora do loop para controle de algo se aproximou
// a posição inicial é definida como a distância medida na hora em que liga o sensor.
// foi colocado -2, porque a leitura do sensor varia 1cm e o motor girava sem mexer no sensor.
int posicaoInicial = 0.01723 * readUltrasonicDistance(13, 12) -2;

void setup() 
{
pinMode(6, INPUT); 
pinMode(8, OUTPUT); 
pinMode(9, OUTPUT); 
servo_2.attach(2); 
Serial.begin(9600);
}

void loop() 
{
int valbotao = digitalRead(6);

if (valbotao == 0) {
if (ledAcesso == 0) {
digitalWrite(8, HIGH); 
digitalWrite(9, LOW); 
delay(50);
} else {
digitalWrite(8, LOW); 
digitalWrite(9, HIGH); 
delay(100); 
ledAcesso = 0;

} 
}

distancia = 0.01723 * readUltrasonicDistance(13, 12); 
Serial.println(distancia);
if (distancia < posicaoInicial) {
// se a distancia medida for menor que a inicial, significa que algo se aproximou
// então o motor gira em 90 graus. 
servo_2.write(90);
digitalWrite(8, LOW);
digitalWrite(9, HIGH);

} else if (valbotao == 0) {
// se não for menor nada se aproximou, então o motor fica em 0 graus 
// se ja estiver em 90 graus volta para 0.
delay(10);
servo_2.write(0);
digitalWrite(8, HIGH);
digitalWrite(9, LOW);
}
delay(10); // Delay a little bit to improve simulation performance 
}
