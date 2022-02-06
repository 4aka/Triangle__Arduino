// http://developer.alexanderklimov.ru/arduino/ir.php
// https://arduino.stackexchange.com/questions/8549/two-arduinos-send-data-via-analog-pin
// https://stackoverflow.com/questions/54942041/send-a-analog-value-from-arduino-a-to-analog-pin-of-arduino-b

/*
  Arduino analogWrite(pin, value) only works on DIGITAL pins
  and then only on the subset of digital pins that have PWM capability.
  This is typically digital pins 3 5 6 9 10 11.
*/

#include "IRremote.h"
int OUT = 10;
int r = 11;
IRrecv ir(r);
decode_results rs;

int up = 11;
int down = 12;
int left = 13;
int right = 14;
int ok = 15;

void setup() {
  Serial.begin(9600);
  ir.enableIRIn();
  pinMode(OUT, OUTPUT);
}

void loop() {
  if (ir.decode(&rs)) {
    // Serial.println(rs.value, HEX);
    decodeIR();
    ir.resume();
  }
}

void decodeIR() {
  switch (rs.value) {
    case 0xFF18E7:
      analogWrite(OUT, up);
      // Serial.println(up);
      break;

    case 0xFF4AB5:
      analogWrite(OUT, down);
      // Serial.println(down);
      break;

    case 0xFF10EF:
      analogWrite(OUT, left);
      // Serial.println(left);
      break;

    case 0xFF5AA5:
      analogWrite(OUT, right);
      // Serial.println(right);
      break;
    case 0xFF38C7:
      analogWrite(OUT, ok);
      // Serial.println(ok);
      break;
  }
}
