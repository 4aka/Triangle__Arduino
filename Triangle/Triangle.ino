#include "FastLED.h"
#include "IRremote.h"
#define LED_DT 13
/* Set quantity of led lights*/
#define ledsQy 127

/******************** VARIABLES ***************************/

/* Choose brightness level */
int brightness = 150;
/* Choose your favorite effect */
volatile unsigned long value = 0xF720DF;

static int r = 2;
IRrecv ir(r);
decode_results rs;

int idex, ihue, ibright, isat, lcount, bouncedirection = 0;
/* Use digital 2 or 3 for Interrupt (Nano) */
static struct CRGB leds[ledsQy];
volatile boolean changeFlag;
static int ledsX[ledsQy][3];
float tcount = 0.0;

/******************** SETUP ********************************/

void setup() {
  Serial.begin(9600);
  LEDS.addLeds<WS2812B, LED_DT, GRB>(leds, ledsQy);
  LEDS.setBrightness(brightness);
  ir.enableIRIn();

  attachInterrupt(0, decodeIR, CHANGE);
  randomSeed(analogRead(0));
}

/******************** LOOP *********************************/

void loop() {
  switch (value) {
    /*The first row of RC*/
    case 0xF720DF: new_rainbow_loop(); break;
    case 0xF7A05F: rainbowCycle(20); break;
    case 0xF7609F: rainbow_fade(); break;
    case 0xF7E01F: pulse_one_color_all(); break; // Fade?

    /*The second row of RC*/
    case 0xF710EF: pulse_one_color_all_rev(); break;
    case 0xF7906F: quad_bright_curve(); break;
    case 0xF750AF: flame();  break;
    case 0xF7D02F: random_color_pop(); break;

    /*The third row of RC*/
    case 0xF730CF: colorWipe(0x00, 0xff, 0x00, 20); colorWipe(0x00, 0x00, 0x00, 20); break;
    case 0xF7B04F: Fire(55, 120, 20); break;
    case 0xF7708F: TwinkleRandom(20, 20); break;
    case 0xF7F00F: RunningLights(0xff, 0xff, 0x00, 20); break;

    /*The fourth row of RC*/
    case 0xF708F7: Sparkle(0xff, 0xff, 0xff, 20); break;
    case 0xF78877: SnowSparkle(0x10, 0x10, 0x10, 20, random(100, 1000)); break;
    case 0xF748B7: rgb_propeller(); break;
    case 0xF7C837: CylonBounce(0, 0, 0xff, 4, 10, 20); break;

    /*The fifth row of RC*/
    case 0xF728D7: theaterChase(0, 0, 0xff, 150); break;
    case 0xF7A857: theaterChaseRainbow(200); break;
    // case 0xF76897:
    // case 0xF7E817:

    /*Off button*/
    case 0xF740BF: setAll(0, 0, 0); break; // Disable strip

    /*Increase | decrease brightness buttons*/
    case 0xF700FF: brightness += 10;
      if (brightness <= 250) LEDS.setBrightness(brightness); break;
    case 0xF7807F: brightness -= 10;
      if (brightness >= 10) LEDS.setBrightness(brightness); break;
  }

  bouncedirection = 0;
  one_color_all(0, 0, 0);
}

/******************** METHODS ******************************/

void decodeIR() {
  if (ir.decode(&rs)) {
    /* Print HEX button's value */
    // Serial.println(rs.value, HEX);
    value = rs.value;
    changeFlag = true;
    ir.resume();
  }
}
