#include "FastLED.h"
#define LED_DT 13 // DIN
int IN = A1; // Remote
int val = 0; // IRremote up - 11, down - 12, left - 13, right - 14, ok - 15.

byte fav_modes[] = {2, 37, 3, 4, 23, 30, 43, 5, 6, 10, 11, 12, 13, 14, 16, 17, 19, 20, 21, 22, 24, 25, 27, 28, 29, 33, 34, 35, 38, 39, 40, 41, 42, 45};
byte num_modes = sizeof(fav_modes);
volatile byte ledMode = 3;

struct CRGB leds[127];
int ledsX[127][3];
int brightness = 150;

int thisdelay = 20;
int thisstep = 10;
int thishue = 0;

int idex = 0;
int ihue = 0;
int ibright = 0;
int isat = 0;
int bouncedirection = 0;
float tcount = 0.0;
int lcount = 0;

volatile uint32_t btnTimer;
volatile byte modeCounter;
volatile boolean changeFlag;

void setup() {
  Serial.begin(9600);
  LEDS.setBrightness(brightness); // MAX bright
  pinMode(IN, INPUT);

  LEDS.addLeds<WS2812B, LED_DT, GRB>(leds, 127);
  one_color_all(0, 0, 0);
  LEDS.show();

  randomSeed(analogRead(0));
  pinMode(2, INPUT_PULLUP); // USE INPUT_PULLUP for button without 10k resistor
  attachInterrupt(0, btnISR, FALLING);
}

void one_color_all(int cred, int cgrn, int cblu) {
  for (int i = 0 ; i < 127; i++ ) {
    leds[i].setRGB(cred, cgrn, cblu);
  }
}

void loop() {

  /*
    if (Serial.available() > 0) {
      ledMode = Serial.parseInt();
      change_mode(ledMode);
    }
  */

  switch (ledMode) {
    case  2: rainbow_fade(); break;                                                 // плавная смена цветов всей ленты
    case  3: rainbow_loop(); break;                                                 // крутящаяся радуга
    case  4: random_burst(); break;                                                 // случайная смена цветов
    case  5: color_bounce(); break;                                                 // бегающий светодиод
    case  6: color_bounceFADE(); break;                                             // бегающий паровозик светодиодов
    case 10: pulse_one_color_all(); break;                                          // пульсация одним цветом
    case 11: pulse_one_color_all_rev(); break;                                      // пульсация со сменой цветов
    case 12: fade_vertical(); break;                                                // плавная смена яркости по вертикали (для кольца)
    case 13: rule30(); break;                                                       // безумие красных светодиодов
    case 14: random_march(); break;                                                 // безумие случайных цветов
    case 16: radiation(); break;                                                    // пульсирует значок радиации
    case 17: color_loop_vardelay(); break;                                          // красный светодиод бегает по кругу
    case 19: sin_bright_wave(); break;                                              // тоже хрень какая то
    case 20: pop_horizontal(); break;                                               // красные вспышки спускаются вниз
    case 21: quad_bright_curve(); break;                                            // полумесяц
    case 22: flame(); break;                                                        // эффект пламени
    case 23: rainbow_vertical(); break;                                             // радуга в вертикаьной плоскости (кольцо)
    case 24: pacman(); break;                                                       // пакман
    case 25: random_color_pop(); break;                                             // безумие случайных вспышек
    case 27: rgb_propeller(); break;                                                // RGB пропеллер
    case 28: kitt(); break;                                                         // случайные вспышки красного в вертикаьной плоскости
    case 29: matrix(); break;                                                       // зелёненькие бегают по кругу случайно
    case 30: new_rainbow_loop(); break;                                             // крутая плавная вращающаяся радуга
    case 33: colorWipe(0x00, 0xff, 0x00, thisdelay);
      colorWipe(0x00, 0x00, 0x00, thisdelay); break;                                // плавное заполнение цветом
    case 34: CylonBounce(0xff, 0, 0, 4, 10, thisdelay); break;                      // бегающие светодиоды
    case 35: Fire(55, 120, thisdelay); break;                                       // линейный огонь
    case 37: rainbowCycle(20); break;                                               // очень плавная вращающаяся радуга
    case 38: TwinkleRandom(20, thisdelay, 1); break;                                // случайные разноцветные включения (1 - танцуют все, 0 - случайный 1 диод)
    case 39: RunningLights(0xff, 0xff, 0x00, thisdelay); break;                     // бегущие огни
    case 40: Sparkle(0xff, 0xff, 0xff, thisdelay); break;                           // случайные вспышки белого цвета
    case 41: SnowSparkle(0x10, 0x10, 0x10, thisdelay, random(100, 1000)); break;    // случайные вспышки белого цвета на белом фоне
    case 42: theaterChase(0xff, 0, 0, thisdelay); break;                            // бегущие каждые 3 (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3)
    case 43: theaterChaseRainbow(thisdelay); break;                                 // бегущие каждые 3 радуга (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3)
    case 45: BouncingBalls(0xff, 0, 0, 3); break;                                   // прыгающие мячики
  }
}

void btnISR() {
  if (millis() - btnTimer > 250) {
    btnTimer = millis();
    if (++modeCounter >= num_modes) modeCounter = 0;
    ledMode = fav_modes[modeCounter];
    change_mode(ledMode);
    changeFlag = true;
  }
}

void IRremote() {
  val = analogRead(IN);
  Serial.println(val);

  switch (val) {
    case 11:
      if (++modeCounter >= num_modes) modeCounter = 0;
      ledMode = fav_modes[modeCounter];
      change_mode(ledMode);
      changeFlag = true;
      break;

    case 12:
      if (--modeCounter >= num_modes) modeCounter = 0;
      ledMode = fav_modes[modeCounter];
      change_mode(ledMode);
      changeFlag = true;
      break;

    case 13:
      LEDS.setBrightness(brightness + thisstep);
      break;

    case 14:
      LEDS.setBrightness(brightness - thisstep);
      break;

    case 15:
      // TODO
      break;
  }
}

void change_mode(int newmode) {
  int thissat = 255;
  switch (newmode) {

    case 0: one_color_all(0, 0, 0); LEDS.show(); break; //---ALL OFF
    case 1: one_color_all(255, 255, 255); LEDS.show(); break; //---ALL ON
    case 2: thisdelay = 60; break;                      //---STRIP RAINBOW FADE
    case 3: thisdelay = 20; thisstep = 10; break;       //---RAINBOW LOOP
    case 4: thisdelay = 20; break;                      //---RANDOM BURST
    case 6: thisdelay = 80; thishue = 0; break;         //---CYLON v2
    case 10: thisdelay = 15; thishue = 0; break;        //---PULSE COLOR BRIGHTNESS
    case 11: thisdelay = 30; thishue = 0; break;        //---PULSE COLOR SATURATION
    case 12: thisdelay = 60; thishue = 180; break;      //---VERTICAL SOMETHING
    case 13: thisdelay = 100; break;                    //---CELL AUTO - RULE 30 (RED)
    case 14: thisdelay = 80; break;                     //---MARCH RANDOM COLORS
    case 16: thisdelay = 60; thishue = 95; break;       //---RADIATION SYMBOL
    case 19: thisdelay = 35; thishue = 180; break;      //---SIN WAVE BRIGHTNESS
    case 20: thisdelay = 100; thishue = 0; break;       //---POP LEFT/RIGHT
    case 21: thisdelay = 100; thishue = 180; break;     //---QUADRATIC BRIGHTNESS CURVE
    case 23: thisdelay = 50; thisstep = 15; break;      //---VERITCAL RAINBOW
    case 24: thisdelay = 50; break;                     //---PACMAN
    case 25: thisdelay = 35; break;                     //---RANDOM COLOR POP
    case 27: thisdelay = 100; thishue = 0; break;       //---RGB PROPELLER
    case 28: thisdelay = 100; thishue = 0; break;       //---KITT
    case 29: thisdelay = 100; thishue = 95; break;      //---MATRIX RAIN
    case 30: thisdelay = 15; break;                     //---NEW RAINBOW LOOP
    case 33: thisdelay = 50; break;                     // colorWipe
    case 34: thisdelay = 50; break;                     // CylonBounce
    case 35: thisdelay = 15; break;                     // Fire
    case 37: thisdelay = 20; break;                     // rainbowCycle
    case 38: thisdelay = 10; break;                     // rainbowTwinkle
    case 39: thisdelay = 50; break;                     // RunningLights
    case 40: thisdelay = 0; break;                      // Sparkle
    case 41: thisdelay = 30; break;                     // SnowSparkle
    case 42: thisdelay = 50; break;                     // theaterChase
    case 43: thisdelay = 50; break;                     // theaterChaseRainbow

    case 101: one_color_all(255, 0, 0); LEDS.show(); break;   //---ALL RED
    case 102: one_color_all(0, 255, 0); LEDS.show(); break;   //---ALL GREEN
    case 103: one_color_all(0, 0, 255); LEDS.show(); break;   //---ALL BLUE
    case 104: one_color_all(255, 255, 0); LEDS.show(); break; //---ALL COLOR X
    case 105: one_color_all(0, 255, 255); LEDS.show(); break; //---ALL COLOR Y
    case 106: one_color_all(255, 0, 255); LEDS.show(); break; //---ALL COLOR Z
  }
  bouncedirection = 0;
  one_color_all(0, 0, 0);
  ledMode = newmode;
}
