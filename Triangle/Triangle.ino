#include "FastLED.h"
#include "IRremote.h"
#define LED_DT 13

int r = 11;
IRrecv ir(r);
decode_results rs;

struct CRGB leds[127]; // quantity of led lights
int ledsX[127][3];
int brightness = 200;
float tcount = 0.0;
int idex, ihue, ibright, isat, lcount, bouncedirection = 0;
volatile boolean changeFlag;
volatile unsigned long value = 0xF720DF;

void setup() {
  Serial.begin(9600);
  LEDS.setBrightness(brightness);
  ir.enableIRIn();
  LEDS.addLeds<WS2812B, LED_DT, GRB>(leds, 127);
  randomSeed(analogRead(0));
  attachInterrupt(0, decodeIR, FALLING);
}

void loop() {
  decodeIR();
  switch (value) {
    case 0xF720DF: new_rainbow_loop(); break;
    case 0xF7A05F: rainbowCycle(20); break;
    case 0xF7609F: random_burst(); break;
    case 0xF7E01F: rainbow_fade(); break;

    case 0xF710EF: pulse_one_color_all(); break;
    case 0xF7906F: pulse_one_color_all_rev(); break;
    // case 0xF750AF: break;
    case 0xF7D02F: quad_bright_curve(); break;

    case 0xF730CF: flame(); break;
    case 0xF7B04F: random_color_pop(); break;
    case 0xF7708F: colorWipe(0x00, 0xff, 0x00, 20); colorWipe(0x00, 0x00, 0x00, 20); break;
    case 0xF7F00F: Fire(55, 120, 20); break;

    case 0xF708F7: TwinkleRandom(20, 20, 1); break;
    case 0xF78877: RunningLights(0xff, 0xff, 0x00, 20); break;
    case 0xF748B7: Sparkle(0xff, 0xff, 0xff, 20); break;
    case 0xF7C837: SnowSparkle(0x10, 0x10, 0x10, 20, random(100, 1000)); break;

    case 0xF728D7: rgb_propeller(); break;
    case 0xF7A857: CylonBounce(0, 0, 0xff, 4, 10, 20); break;
    case 0xF76897: theaterChase(0, 0, 0xff, 150); break;
    case 0xF7E817: theaterChaseRainbow(150); break;

    case 0xF740BF: setAll(0, 0, 0); break;
  }

  bouncedirection = 0;
  one_color_all(0, 0, 0);
}

void decodeIR() {
  if (ir.decode(&rs)) {
    value = rs.value;
    changeFlag = true;
    ir.resume();
  }
}

void one_color_all(int cred, int cgrn, int cblu) {
  for (int i = 0 ; i < 127; i++ ) {
    leds[i].setRGB(cred, cgrn, cblu);
  }
}
