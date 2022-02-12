#include "FastLED.h"
//#include "IRremote.h"
#define LED_DT 13

byte fav_modes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
byte num_modes = sizeof(fav_modes);

//int r = 11;
//IRrecv ir(r);
//decode_results rs;

struct CRGB leds[127]; // quantity of led lights
int ledsX[127][3];
int brightness = 150;  // MAX bright
float tcount = 0.0;
int idex, ihue, ibright, isat, lcount, bouncedirection = 0;

volatile byte ledMode = 1;
volatile uint32_t btnTimer;
volatile byte modeCounter;
volatile boolean changeFlag;

void setup() {
  Serial.begin(9600);
  LEDS.setBrightness(brightness);
//  ir.enableIRIn();

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

//  if (ir.decode(&rs)) {
//    // Serial.println(rs.value, HEX);
//    decodeIR();
//    ir.resume();
//  }

  switch (ledMode) {
    case  1: rainbow_fade(); break;                                                 // плавная смена цветов всей ленты
    case  2: rainbowCycle(20); break;                                               // очень плавная вращающаяся радуга
    case  3: rainbow_loop(); break;                                                 // крутящаяся радуга
    case  4: random_burst(); break;                                                 // случайная смена цветов
    case  5: rainbow_vertical(); break;                                             // радуга в вертикаьной плоскости (кольцо)
    case  6: new_rainbow_loop(); break;                                             // крутая плавная вращающаяся радуга
    case  7: color_bounce(); break;                                                 // бегающий светодиод
    case  8: color_bounceFADE(); break;                                             // бегающий паровозик светодиодов
    case  9: pulse_one_color_all(); break;                                          // пульсация одним цветом
    case 10: pulse_one_color_all_rev(); break;                                      // пульсация со сменой цветов
    case 11: fade_vertical(); break;                                                // плавная смена яркости по вертикали (для кольца)
    case 12: rule30(); break;                                                       // безумие красных светодиодов
    case 13: random_march(); break;                                                 // безумие случайных цветов
    case 14: color_loop_vardelay(); break;                                          // красный светодиод бегает по кругу
    case 15: sin_bright_wave(); break;                                              // тоже хрень какая то
    case 16: pop_horizontal(); break;                                               // красные вспышки спускаются вниз
    case 17: quad_bright_curve(); break;                                            // полумесяц
    case 18: flame(); break;                                                        // эффект пламени
    case 19: random_color_pop(); break;                                             // безумие случайных вспышек
    case 20: rgb_propeller(); break;                                                // RGB пропеллер
    case 21: kitt(); break;                                                         // случайные вспышки красного в вертикаьной плоскости
    case 22: matrix(); break;                                                       // зелёненькие бегают по кругу случайно
    case 23: colorWipe(0x00, 0xff, 0x00, 20);
      colorWipe(0x00, 0x00, 0x00, 20); break;                                       // плавное заполнение цветом
    case 24: CylonBounce(0xff, 0, 0, 4, 10, 20); break;                             // бегающие светодиоды
    case 25: Fire(55, 120, 20); break;                                              // линейный огонь
    case 26: TwinkleRandom(20, 20, 1); break;                                       // случайные разноцветные включения (1 - танцуют все, 0 - случайный 1 диод)
    case 27: RunningLights(0xff, 0xff, 0x00, 20); break;                            // бегущие огни
    case 28: Sparkle(0xff, 0xff, 0xff, 20); break;                                  // случайные вспышки белого цвета
    case 29: SnowSparkle(0x10, 0x10, 0x10, 20, random(100, 1000)); break;           // случайные вспышки белого цвета на белом фоне
    case 30: theaterChase(0xff, 0, 0, 20); break;                                   // бегущие каждые 3 (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3)
    case 31: theaterChaseRainbow(20); break;                                        // бегущие каждые 3 радуга (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3)
  }
  
  bouncedirection = 0;
  one_color_all(0, 0, 0);
}

void btnISR() {
  if (millis() - btnTimer > 250) {
    btnTimer = millis();
    if (++modeCounter >= num_modes) modeCounter = 0;
    ledMode = fav_modes[modeCounter];
    changeFlag = true;
  }
}

//void decodeIR() {
//  switch (rs.value) {
//    case 0xFF18E7: // up
//      if (++modeCounter >= 34) modeCounter = 0;
//      ledMode = fav_modes[modeCounter];
//      change_mode(ledMode);
//      changeFlag = true;
//      // Serial.println("Up");
//      break;
//
//    case 0xFF4AB5: // down
//      if (--modeCounter >= 34) modeCounter = 34;
//      ledMode = fav_modes[modeCounter];
//      change_mode(ledMode);
//      changeFlag = true;
//      // Serial.println("Down");
//      break;
//
//    case 0xFF10EF: // left
//      LEDS.setBrightness(brightness + 10);
//      break;
//
//    case 0xFF5AA5: // right
//      LEDS.setBrightness(brightness - 10);
//      break;
//
//    case 0xFF38C7: // ok
//      TODO fix!!!
//      if (mode) one_color_all(0, 0, 0); LEDS.show(); break; //---ALL OFF
//      else one_color_all(255, 255, 255); LEDS.show(); break; //---ALL ON  
//      break;
//  }
//}
