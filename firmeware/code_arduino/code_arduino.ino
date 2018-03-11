
/**
   Software: Projeto 01
   Description: Controlando Carrrinho Arduino com App Android via Bluetooth
   Author: RodriguesFAS[
   Email: <franciscosouzaacer@gmail.com>
   Site: <http://rodrihuesfas.com.br> | <http://clubedosgeeks.com.br>
   Github: <>
   Date: 17/02/2018
   Version: 0.0.1
   Atencion: Before transferring the code to the Arduino board, remove the Bluetooth TX or RX pins from the Arduino board, otherwise the transfer will fail.
*/

// Custom Util
#include <BUMBLEBEE.h>

/**
  Instantiate an object of class BUMBLEBEE, passing parameters the connecting pins
  where this on each pin of the H bridge L298N in Arduino doors.
*/
#define PIN1_MOTOR_LEFT           2
#define PIN2_MOTOR_LEFT           4
#define PIN_PWM_SPEED_MOTOR_LEFT  3

#define PIN1_MOTOR_RIGHT          6
#define PIN2_MOTOR_RIGHT          7
#define PIN_PWM_SPEED_MOTOR_RIGHT 5

BUMBLEBEE bee(PIN1_MOTOR_LEFT, PIN2_MOTOR_LEFT, PIN_PWM_SPEED_MOTOR_LEFT, PIN1_MOTOR_RIGHT, PIN2_MOTOR_RIGHT, PIN_PWM_SPEED_MOTOR_RIGHT);

#define SPEED 200
#define SPEED_AUX 55


#define BUZZER 13


/**
  ========================================================================================================================
  setup - configuration initial.
*/
void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
}

/**
  ========================================================================================================================
  loop -
*/
void loop() {

  if (Serial.available()) {
    char inByte = Serial.read();
    controlSerialBluethoot(inByte);
  }

}

/**
  ========================================================================================================================
  controlSerialBluethoot
*/
void controlSerialBluethoot(char option) {
  /**
     [S] STOP|NONE
     [F] UP
     [I] UP/RIGHT
     [R] RIGHT
     [J] DOWN/RIGHT
     [B] DOWN
     [H] DOWN/LEFT
     [L] LEFT
     [G] UP/LEFT
     [default] STOP|NONE
  */
  switch (option) {

    case 'S':
      bee.stop();
      break;

    case 'F':
      bee.move(SPEED, SPEED);
      break;

    case 'I':
      bee.move(SPEED + SPEED_AUX, SPEED);
      break;

    case 'R':
      bee.move(SPEED, -SPEED);
      break;

    case 'J':
      bee.move(-SPEED + SPEED_AUX, -SPEED);
      break;

    case 'B':
      bee.move(-SPEED, -SPEED);
      break;

    case 'H':
      bee.move(-SPEED, -SPEED + SPEED_AUX);
      break;

    case 'L':
      bee.move(-SPEED, SPEED);
      break;

    case 'G':
      bee.move(-SPEED, SPEED + SPEED_AUX);
      break;

    default :
      bee.stop();
      break;
  }

  // Buzzer
  if (option == 'V') {
    tone(BUZZER, 1000);
  } else if (option == 'v') {
    noTone(BUZZER);
  }

}
