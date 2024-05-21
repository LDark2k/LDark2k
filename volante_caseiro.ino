#include <Joystick.h>

// Define os pinos dos potenciômetros
const int pinPotX = A0; // Pino analógico conectado ao potenciômetro do eixo X (volante)
const int pinPotY = A1; // Pino analógico conectado ao potenciômetro do acelerador
const int pinPotZ = A2; // Pino analógico conectado ao potenciômetro do freio
const int pinPotClutch = A3; // Pino analógico conectado ao potenciômetro do pedal da embreagem

// Define os pinos dos botões de troca de marchas
const int pinBtn1 = 2; // Pino digital conectado ao botão 1
const int pinBtn2 = 3; // Pino digital conectado ao botão 2
const int pinBtn3 = 4; // Pino digital conectado ao botão 3
const int pinBtn4 = 5; // Pino digital conectado ao botão 4
const int pinBtn5 = 6; // Pino digital conectado ao botão 5
const int pinBtn6 = 7; // Pino digital conectado ao botão 6

// Define os objetos Joystick
Joystick_ joystick;

// Define os estados anteriores dos botões
int prevBtnState1 = LOW;
int prevBtnState2 = LOW;
int prevBtnState3 = LOW;
int prevBtnState4 = LOW;
int prevBtnState5 = LOW;
int prevBtnState6 = LOW;

void setup() {
  // Inicialize o objeto Joystick
  joystick.begin();

  // Configura os pinos dos botões como entradas
  pinMode(pinBtn1, INPUT_PULLUP);
  pinMode(pinBtn2, INPUT_PULLUP);
  pinMode(pinBtn3, INPUT_PULLUP);
  pinMode(pinBtn4, INPUT_PULLUP);
  pinMode(pinBtn5, INPUT_PULLUP);
  pinMode(pinBtn6, INPUT_PULLUP);

  // Inicialize a comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Leitura dos potenciômetros
  int potValueX = analogRead(pinPotX); // Volante
  int potValueY = analogRead(pinPotY); // Acelerador
  int potValueZ = analogRead(pinPotZ); // Freio
  int potValueClutch = analogRead(pinPotClutch); // Pedal da embreagem
  
  // Mapeia os valores dos potenciômetros para o intervalo de 0 a 1023
  int potMappedX = map(potValueX, 0, 1023, 0, 1023); // Volante
  int potMappedY = map(potValueY, 0, 1023, 0, 1023); // Acelerador
  int potMappedZ = map(potValueZ, 0, 1023, 0, 1023); // Freio
  int potMappedClutch = map(potValueClutch, 0, 1023, 0, 1023); // Pedal da embreagem
  
  // Envia os valores mapeados dos potenciômetros como entrada do joystick
  joystick.setXAxis(potMappedX); // Volante
  joystick.setYAxis(potMappedY); // Acelerador
  joystick.setZAxis(potMappedZ); // Freio
  joystick.setThrottle(potMappedClutch); // Pedal da embreagem

  // Leitura dos botões de troca de marchas
  int btnState1 = digitalRead(pinBtn1);
  int btnState2 = digitalRead(pinBtn2);
  int btnState3 = digitalRead(pinBtn3);
  int btnState4 = digitalRead(pinBtn4);
  int btnState5 = digitalRead(pinBtn5);
  int btnState6 = digitalRead(pinBtn6);
  
  // Verifica se houve uma mudança de estado nos botões
  if (btnState1 != prevBtnState1) {
    joystick.setButton(0, !btnState1); // Botão 1
    prevBtnState1 = btnState1;
  }
  if (btnState2 != prevBtnState2) {
    joystick.setButton(1, !btnState2); // Botão 2
    prevBtnState2 = btnState2;
  }
  if (btnState3 != prevBtnState3) {
    joystick.setButton(2, !btnState3); // Botão 3
    prevBtnState3 = btnState3;
  }
  if (btnState4 != prevBtnState4) {
    joystick.setButton(3, !btnState4); // Botão 4
    prevBtnState4 = btnState4;
  }
  if (btnState5 != prevBtnState5) {
    joystick.setButton(4, !btnState5); // Botão 5
    prevBtnState5 = btnState5;
  }
  if (btnState6 != prevBtnState6) {
    joystick.setButton(5, !btnState6); // Botão 6
    prevBtnState6 = btnState6;
  }

  // Imprime os valores lidos no monitor serial
  Serial.print("Volante: ");
  Serial.print(potValueX);
  Serial.print("\tAcelerador: ");
  Serial.print(potValueY);
  Serial.print("\tFreio: ");
  Serial.print(potValueZ);
  Serial.print("\tEmbreagem: ");
  Serial.print(potValueClutch);
  Serial.print("\tBotão 1: ");
  Serial.print(btnState1);
  Serial.print("\tBotão 2: ");
  Serial.print(btnState2);
  Serial.print("\tBotão 3: ");
  Serial.print(btnState3);
  Serial.print("\tBotão 4: ");
  Serial.print(btnState4);
  Serial.print("\tBotão 5: ");
  Serial.print(btnState5);
  Serial.print("\tBotão 6: ");
  Serial.println(btnState6);
  
  // Aguarda um curto período de tempo para evitar que os dados sejam enviados muito rapidamente
  delay(10);
}
