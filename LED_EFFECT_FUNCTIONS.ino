void rainbow_fade() {
  ihue++;
  if (ihue > 255) {
    ihue = 0;
  }
  for (int idex = 0 ; idex < ledsQy; idex++ ) {
    leds[idex] = CHSV(ihue, 255, 255);
  }
  LEDS.show();
  if (safeDelay(60)) return;
}

void random_burst() {
  idex = random(0, ledsQy);
  ihue = random(0, 255);
  leds[idex] = CHSV(ihue, 255, 255);
  LEDS.show();
  if (safeDelay(20)) return;
}

void pulse_one_color_all() {
  if (bouncedirection == 0) {
    ibright++;
    if (ibright >= 255) {
      bouncedirection = 1;
    }
  }
  if (bouncedirection == 1) {
    ibright = ibright - 1;
    if (ibright <= 1) {
      bouncedirection = 0;
    }
  }
  for (int idex = 0 ; idex < ledsQy; idex++ ) {
    leds[idex] = CHSV(0, 255, ibright);
  }
  LEDS.show();
  if (safeDelay(25)) return;
}

void pulse_one_color_all_rev() {
  if (bouncedirection == 0) {
    isat++;
    if (isat >= 255) {
      bouncedirection = 1;
    }
  }
  if (bouncedirection == 1) {
    isat = isat - 1;
    if (isat <= 1) {
      bouncedirection = 0;
    }
  }
  for (int idex = 0 ; idex < ledsQy; idex++ ) {
    leds[idex] = CHSV(0, isat, 255);
  }
  LEDS.show();
  if (safeDelay(20)) return;
}

void random_red() {
  int temprand;
  for (int i = 0; i < ledsQy; i++ ) {
    temprand = random(0, 100);
    if (temprand > 50) {
      leds[i].r = 255;
    }
    if (temprand <= 50) {
      leds[i].r = 0;
    }
    leds[i].b = 0; leds[i].g = 0;
  }
  LEDS.show();
}

void quad_bright_curve() {
  int ax;
  for (int x = 0; x < ledsQy; x++ ) {
    if (x <= ledsQy / 2) {
      ax = x;
    }
    else if (x > ledsQy / 2) {
      ax = ledsQy - x;
    }
    int a = 1; int b = 1; int c = 0;
    int iquad = -(ax * ax * a) + (ax * b) + c; //-ax2+bx+c
    int hquad = -(ledsQy / 2 * ledsQy / 2 * a) + (ledsQy / 2 * b) + c;
    ibright = int((float(iquad) / float(hquad)) * 255);
    leds[x] = CHSV(180, 255, ibright);
  }
  LEDS.show();
  if (safeDelay(100)) return;
}

void flame() {
  int idelay = random(0, 35);
  float hmin = 0.1; float hmax = 45.0;
  float hdif = hmax - hmin;
  int randtemp = random(0, 3);
  float hinc = (hdif / float(ledsQy / 2)) + randtemp;
  int ihue = hmin;
  for (int i = 0; i <= ledsQy / 2; i++ ) {
    ihue = ihue + hinc;
    leds[i] = CHSV(ihue, 255, 255);
    int ih = horizontal_index(i);
    leds[ih] = CHSV(ihue, 255, 255);
    leds[ledsQy / 2].r = 255; leds[ledsQy / 2].g = 255; leds[ledsQy / 2].b = 255;
    LEDS.show();
    if (safeDelay(idelay)) return;
  }
}

void random_color_pop() {
  idex = random(0, ledsQy);
  ihue = random(0, 255);
  one_color_all(0, 0, 0);
  leds[idex] = CHSV(ihue, 255, 255);
  LEDS.show();
  if (safeDelay(35)) return;
}

void rgb_propeller() { // change colour
  idex++;
  int ghue = (0 + 80) % 255;
  int bhue = (0 + 160) % 255;
  int N3  = int(ledsQy / 3);
  int N6  = int(ledsQy / 6);
  int N12 = int(ledsQy / 12);
  for (int i = 0; i < N3; i++ ) {
    int j0 = (idex + i + ledsQy - N12) % ledsQy;
    int j1 = (j0 + N3) % ledsQy;
    int j2 = (j1 + N3) % ledsQy;
    leds[j0] = CHSV(0, 255, 255);
    leds[j1] = CHSV(ghue, 255, 255);
    leds[j2] = CHSV(bhue, 255, 255);
  }
  LEDS.show();
  if (safeDelay(40)) return;
}

void new_rainbow_loop() {
  ihue -= 1;
  fill_rainbow( leds, ledsQy, ihue );
  LEDS.show();
  if (safeDelay(15)) return;
}

void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for (uint16_t i = 0; i < ledsQy; i++) {
    setPixel(i, red, green, blue);
    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
  }
}

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {

  for (int i = 0; i < ledsQy - EyeSize - 2; i++) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
  }

  if (safeDelay(ReturnDelay)) return;

  for (int i = ledsQy - EyeSize - 2; i > 0; i--) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
  }

  if (safeDelay(ReturnDelay)) return;
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[ledsQy];
  int cooldown;

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < ledsQy; i++) {
    cooldown = random(0, ((Cooling * 10) / ledsQy) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  for ( int k = ledsQy - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  if ( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
  }

  for ( int j = 0; j < ledsQy; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  FastLED.show();
  if (safeDelay(SpeedDelay)) return;
}

void setPixelHeatColor (int Pixel, byte temperature) { // dont touch
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);

  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252

  // figure out which third of the spectrum we're in:
  if ( t192 > 0x80) {                    // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if ( t192 > 0x40 ) {            // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < ledsQy; i++) {
      c = Wheel(((i * 256 / ledsQy) + j) & 255);
      setPixel(i, *c, *(c + 1), *(c + 2));
    }
    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];

  if (WheelPos < 85) {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}

void TwinkleRandom(int Count, int SpeedDelay) {
  setAll(0, 0, 0);

  for (int i = 0; i < Count; i++) {
    setPixel(random(ledsQy), random(0, 255), random(0, 255), random(0, 255));
    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
  }
  if (safeDelay(SpeedDelay)) return;
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position = 0;

  for (int i = 0; i < ledsQy * 2; i++)
  {
    Position++; // = 0; //Position + Rate;
    for (int i = 0; i < ledsQy; i++) {
      // sine wave, 3 offset waves make a rainbow!
      //float level = sin(i+Position) * ledsQy + 128;
      //setPixel(i,level,0,0);
      //float level = sin(i+Position) * ledsQy + 128;
      setPixel(i, ((sin(i + Position) * ledsQy + 128) / 255)*red,
               ((sin(i + Position) * ledsQy + 128) / 255)*green,
               ((sin(i + Position) * ledsQy + 128) / 255)*blue);
    }

    FastLED.show();
    if (safeDelay(WaveDelay)) return;
  }
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(ledsQy);
  setPixel(Pixel, red, green, blue);
  FastLED.show();
  if (safeDelay(SpeedDelay)) return;
  setPixel(Pixel, 0, 0, 0);
}

void SnowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay) {
  setAll(red, green, blue);
  int Pixel = random(ledsQy);
  setPixel(Pixel, 0xff, 0xff, 0xff);
  FastLED.show();
  if (safeDelay(SparkleDelay)) return;
  setPixel(Pixel, red, green, blue);
  FastLED.show();
  if (safeDelay(SpeedDelay)) return;
}

void theaterChase(byte red, byte green, byte blue, int SpeedDelay) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < ledsQy; i = i + 3) {
        setPixel(i + q, red, green, blue);  //turn every third pixel on
      }
      FastLED.show();
      if (safeDelay(SpeedDelay)) return;
      for (int i = 0; i < ledsQy; i = i + 3) {
        setPixel(i + q, 0, 0, 0);    //turn every third pixel off
      }
    }
  }
}

void theaterChaseRainbow(int SpeedDelay) {
  byte *c;

  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < ledsQy; i = i + 3) {
        c = Wheel( (i + j) % 255);
        setPixel(i + q, *c, *(c + 1), *(c + 2)); //turn every third pixel on
      }
      FastLED.show();
      if (safeDelay(SpeedDelay)) return;
      for (int i = 0; i < ledsQy; i = i + 3) {
        setPixel(i + q, 0, 0, 0);    //turn every third pixel off
      }
    }
  }
}

boolean safeDelay(int delTime) {
  uint32_t thisTime = millis();
  while (millis() - thisTime <= delTime) {
    if (changeFlag) {
      changeFlag = false;
      return true;
    }
  }
  return false;
}

void one_color_all(int cred, int cgrn, int cblu) {
  for (int i = 0 ; i < ledsQy; i++ ) {
    leds[i].setRGB(cred, cgrn, cblu);
  }
}
