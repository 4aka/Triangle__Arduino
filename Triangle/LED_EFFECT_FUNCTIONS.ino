//------------------------LED EFFECT FUNCTIONS------------------------
void one_color_allHSV(int ahue) {
  for (int i = 0 ; i < 127; i++ ) {
    leds[i] = CHSV(ahue, 255, 255);
  }
}

void rainbow_fade() {
  ihue++;
  if (ihue > 255) {
    ihue = 0;
  }
  for (int idex = 0 ; idex < 127; idex++ ) {
    leds[idex] = CHSV(ihue, 255, 255);
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void rainbow_loop() {
  idex++;
  ihue = ihue + thisstep;
  if (idex >= 127) {
    idex = 0;
  }
  if (ihue > 255) {
    ihue = 0;
  }
  leds[idex] = CHSV(ihue, 255, 255);
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void random_burst() {
  idex = random(0, 127);
  ihue = random(0, 255);
  leds[idex] = CHSV(ihue, 255, 255);
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void color_bounce() {
  if (bouncedirection == 0) {
    idex = idex + 1;
    if (idex == 127) {
      bouncedirection = 1;
      idex = idex - 1;
    }
  }
  if (bouncedirection == 1) {
    idex = idex - 1;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
  for (int i = 0; i < 127; i++ ) {
    if (i == idex) {
      leds[i] = CHSV(0, 255, 255);
    }
    else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
  if (safeDelay(20)) return;
}

void color_bounceFADE() {
  if (bouncedirection == 0) {
    idex = idex + 1;
    if (idex == 127) {
      bouncedirection = 1;
      idex = idex - 1;
    }
  }
  if (bouncedirection == 1) {
    idex = idex - 1;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
  int iL1 = adjacent_cw(idex);
  int iL2 = adjacent_cw(iL1);
  int iL3 = adjacent_cw(iL2);
  int iR1 = adjacent_ccw(idex);
  int iR2 = adjacent_ccw(iR1);
  int iR3 = adjacent_ccw(iR2);
  for (int i = 0; i < 127; i++ ) {
    if (i == idex) {
      leds[i] = CHSV(thishue, 255, 255);
    }
    else if (i == iL1) {
      leds[i] = CHSV(thishue, 255, 150);
    }
    else if (i == iL2) {
      leds[i] = CHSV(thishue, 255, 80);
    }
    else if (i == iL3) {
      leds[i] = CHSV(thishue, 255, 20);
    }
    else if (i == iR1) {
      leds[i] = CHSV(thishue, 255, 150);
    }
    else if (i == iR2) {
      leds[i] = CHSV(thishue, 255, 80);
    }
    else if (i == iR3) {
      leds[i] = CHSV(thishue, 255, 20);
    }
    else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
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
  for (int idex = 0 ; idex < 127; idex++ ) {
    leds[idex] = CHSV(thishue, 255, ibright);
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
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
  for (int idex = 0 ; idex < 127; idex++ ) {
    leds[idex] = CHSV(thishue, isat, 255);
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void fade_vertical() {
  idex++;
  if (idex > 127/2) {
    idex = 0;
  }
  int idexA = idex;
  int idexB = horizontal_index(idexA);
  ibright = ibright + 10;
  if (ibright > 255) {
    ibright = 0;
  }
  leds[idexA] = CHSV(thishue, 255, ibright);
  leds[idexB] = CHSV(thishue, 255, ibright);
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void random_red() {
  int temprand;
  for (int i = 0; i < 127; i++ ) {
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

void rule30() {
  if (bouncedirection == 0) {
    random_red();
    bouncedirection = 1;
  }
  copy_led_array();
  int iCW;
  int iCCW;
  int y = 100;
  for (int i = 0; i < 127; i++ ) {
    iCW = adjacent_cw(i);
    iCCW = adjacent_ccw(i);
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] > y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] > y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {
      leds[i].r = 0;
    }
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void random_march() {
  copy_led_array();
  int iCCW;
  leds[0] = CHSV(random(0, 255), 255, 255);
  for (int idex = 1; idex < 127 ; idex++ ) {
    iCCW = adjacent_ccw(idex);
    leds[idex].r = ledsX[iCCW][0];
    leds[idex].g = ledsX[iCCW][1];
    leds[idex].b = ledsX[iCCW][2];
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void radiation() {
  int N3  = int(127 / 3);
  int N6  = int(127 / 6);
  int N12 = int(127 / 12);
  for (int i = 0; i < N6; i++ ) {                                   //-HACKY, I KNOW...
    tcount = tcount + .02;
    if (tcount > 3.14) {
      tcount = 0.0;
    }
    ibright = int(sin(tcount) * 255);
    int j0 = (i + 127 - N12) % 127;
    int j1 = (j0 + N3) % 127;
    int j2 = (j1 + N3) % 127;
    leds[j0] = CHSV(thishue, 255, ibright);
    leds[j1] = CHSV(thishue, 255, ibright);
    leds[j2] = CHSV(thishue, 255, ibright);
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void color_loop_vardelay() {
  idex++;
  if (idex > 127) {
    idex = 0;
  }
  int di = abs(127/2 - idex);
  int t = constrain((10 / di) * 10, 10, 500);
  for (int i = 0; i < 127; i++ ) {
    if (i == idex) {
      leds[i] = CHSV(0, 255, 255);
    }
    else {
      leds[i].r = 0; leds[i].g = 0; leds[i].b = 0;
    }
  }
  LEDS.show();
  if (safeDelay(t)) return;
}

void sin_bright_wave() {
  for (int i = 0; i < 127; i++ ) {
    tcount = tcount + .1;
    if (tcount > 3.14) {
      tcount = 0.0;
    }
    ibright = int(sin(tcount) * 255);
    leds[i] = CHSV(thishue, 255, ibright);
    LEDS.show();
    if (safeDelay(thisdelay)) return;
  }
}

void pop_horizontal() {
  int ix;
  if (bouncedirection == 0) {
    bouncedirection = 1;
    ix = idex;
  }
  else if (bouncedirection == 1) {
    bouncedirection = 0;
    ix = horizontal_index(idex);
    idex++;
    if (idex > 127/2) {
      idex = 0;
    }
  }
  for (int i = 0; i < 127; i++ ) {
    if (i == ix) {
      leds[i] = CHSV(thishue, 255, 255);
    }
    else {
      leds[i].r = 0; leds[i].g = 0; leds[i].b = 0;
    }
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void quad_bright_curve() {
  int ax;
  for (int x = 0; x < 127; x++ ) {
    if (x <= 127/2) {
      ax = x;
    }
    else if (x > 127/2) {
      ax = 127 - x;
    }
    int a = 1; int b = 1; int c = 0;
    int iquad = -(ax * ax * a) + (ax * b) + c; //-ax2+bx+c
    int hquad = -(127/2 * 127/2 * a) + (127/2 * b) + c;
    ibright = int((float(iquad) / float(hquad)) * 255);
    leds[x] = CHSV(thishue, 255, ibright);
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void flame() {
  int idelay = random(0, 35);
  float hmin = 0.1; float hmax = 45.0;
  float hdif = hmax - hmin;
  int randtemp = random(0, 3);
  float hinc = (hdif / float(127/2)) + randtemp;
  int ihue = hmin;
  for (int i = 0; i <= 127/2; i++ ) {
    ihue = ihue + hinc;
    leds[i] = CHSV(ihue, 255, 255);
    int ih = horizontal_index(i);
    leds[ih] = CHSV(ihue, 255, 255);
    leds[127/2].r = 255; leds[127/2].g = 255; leds[127/2].b = 255;
    LEDS.show();
    if (safeDelay(idelay)) return;
  }
}

void rainbow_vertical() {
  idex++;
  if (idex > 127/2) {
    idex = 0;
  }
  ihue = ihue + thisstep;
  if (ihue > 255) {
    ihue = 0;
  }
  int idexA = idex;
  int idexB = horizontal_index(idexA);
  leds[idexA] = CHSV(ihue, 255, 255);
  leds[idexB] = CHSV(ihue, 255, 255);
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void pacman() {
  int s = int(127 / 4);
  lcount++;
  if (lcount > 5) {
    lcount = 0;
  }
  if (lcount == 0) {
    for (int i = 0 ; i < 127; i++ ) {
      set_color_led(i, 255, 255, 0);
    }
  }
  if (lcount == 1 || lcount == 5) {
    for (int i = 0 ; i < 127; i++ ) {
      set_color_led(i, 255, 255, 0);
    }
    leds[s].r = 0; leds[s].g = 0; leds[s].b = 0;
  }
  if (lcount == 2 || lcount == 4) {
    for (int i = 0 ; i < 127; i++ ) {
      set_color_led(i, 255, 255, 0);
    }
    leds[s - 1].r = 0; leds[s - 1].g = 0; leds[s - 1].b = 0;
    leds[s].r = 0; leds[s].g = 0; leds[s].b = 0;
    leds[s + 1].r = 0; leds[s + 1].g = 0; leds[s + 1].b = 0;
  }
  if (lcount == 3) {
    for (int i = 0 ; i < 127; i++ ) {
      set_color_led(i, 255, 255, 0);
    }
    leds[s - 2].r = 0; leds[s - 2].g = 0; leds[s - 2].b = 0;
    leds[s - 1].r = 0; leds[s - 1].g = 0; leds[s - 1].b = 0;
    leds[s].r = 0; leds[s].g = 0; leds[s].b = 0;
    leds[s + 1].r = 0; leds[s + 1].g = 0; leds[s + 1].b = 0;
    leds[s + 2].r = 0; leds[s + 2].g = 0; leds[s + 2].b = 0;
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void random_color_pop() {
  idex = random(0, 127);
  ihue = random(0, 255);
  one_color_all(0, 0, 0);
  leds[idex] = CHSV(ihue, 255, 255);
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void rgb_propeller() {
  idex++;
  int ghue = (thishue + 80) % 255;
  int bhue = (thishue + 160) % 255;
  int N3  = int(127 / 3);
  int N6  = int(127 / 6);
  int N12 = int(127 / 12);
  for (int i = 0; i < N3; i++ ) {
    int j0 = (idex + i + 127 - N12) % 127;
    int j1 = (j0 + N3) % 127;
    int j2 = (j1 + N3) % 127;
    leds[j0] = CHSV(thishue, 255, 255);
    leds[j1] = CHSV(ghue, 255, 255);
    leds[j2] = CHSV(bhue, 255, 255);
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void kitt() {
  int rand = random(0, 127/2);
  for (int i = 0; i < rand; i++ ) {
    leds[127/2 + i] = CHSV(thishue, 255, 255);
    leds[127/2 - i] = CHSV(thishue, 255, 255);
    LEDS.show();
    if (safeDelay(thisdelay / rand)) return;
  }
  for (int i = rand; i > 0; i-- ) {
    leds[127/2 + i] = CHSV(thishue, 255, 0);
    leds[127/2 - i] = CHSV(thishue, 255, 0);
    LEDS.show();
    if (safeDelay(thisdelay / rand)) return;
  }
}

void matrix() {
  int rand = random(0, 100);
  if (rand > 90) {
    leds[0] = CHSV(thishue, 255, 255);
  }
  else {
    leds[0] = CHSV(thishue, 255, 0);
  }
  copy_led_array();
  for (int i = 1; i < 127; i++ ) {
    leds[i].r = ledsX[i - 1][0];
    leds[i].g = ledsX[i - 1][1];
    leds[i].b = ledsX[i - 1][2];
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void new_rainbow_loop() {
  ihue -= 1;
  fill_rainbow( leds, 127, ihue );
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for (uint16_t i = 0; i < 127; i++) {
    setPixel(i, red, green, blue);
    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
  }
}

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {

  for (int i = 0; i < 127 - EyeSize - 2; i++) {
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

  for (int i = 127 - EyeSize - 2; i > 0; i--) {
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
  static byte heat[127];
  int cooldown;

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < 127; i++) {
    cooldown = random(0, ((Cooling * 10) / 127) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  for ( int k = 127 - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  if ( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
  }

  for ( int j = 0; j < 127; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  FastLED.show();
  if (safeDelay(SpeedDelay)) return;
}

void setPixelHeatColor (int Pixel, byte temperature) {
  byte t192 = round((temperature / 255.0) * 191);

  byte heatramp = t192 & 0x3F;
  heatramp <<= 2;

  if ( t192 > 0x80) {
    setPixel(Pixel, 255, 255, heatramp);
  } else if ( t192 > 0x40 ) {
    setPixel(Pixel, 255, heatramp, 0);
  } else {
    setPixel(Pixel, heatramp, 0, 0);
  }
}

void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = ((127 - EyeSize) / 2); i >= 0; i--) {
    setAll(0, 0, 0);

    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

    setPixel(127 - i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(127 - i - j, red, green, blue);
    }
    setPixel(127 - i - EyeSize - 1, red / 10, green / 10, blue / 10);

    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
  }
  if (safeDelay(ReturnDelay)) return;
}

void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = 0; i <= ((127 - EyeSize) / 2); i++) {
    setAll(0, 0, 0);

    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

    setPixel(127 - i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(127 - i - j, red, green, blue);
    }
    setPixel(127 - i - EyeSize - 1, red / 10, green / 10, blue / 10);

    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
  }
  if (safeDelay(ReturnDelay)) return;
}

void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = 0; i < 127 - EyeSize - 2; i++) {
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

void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = 127 - EyeSize - 2; i > 0; i--) {
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

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < 127; i++) {
      c = Wheel(((i * 256 / 127) + j) & 255);
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

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0, 0, 0);

  for (int i = 0; i < Count; i++) {
    setPixel(random(127), random(0, 255), random(0, 255), random(0, 255));
    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
    if (OnlyOne) {
      setAll(0, 0, 0);
    }
  }

  if (safeDelay(SpeedDelay)) return;
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position = 0;

  for (int i = 0; i < 127 * 2; i++)
  {
    Position++; // = 0; //Position + Rate;
    for (int i = 0; i < 127; i++) {
      // sine wave, 3 offset waves make a rainbow!
      //float level = sin(i+Position) * 127 + 128;
      //setPixel(i,level,0,0);
      //float level = sin(i+Position) * 127 + 128;
      setPixel(i, ((sin(i + Position) * 127 + 128) / 255)*red,
               ((sin(i + Position) * 127 + 128) / 255)*green,
               ((sin(i + Position) * 127 + 128) / 255)*blue);
    }

    FastLED.show();
    if (safeDelay(WaveDelay)) return;
  }
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(127);
  setPixel(Pixel, red, green, blue);
  FastLED.show();
  if (safeDelay(SpeedDelay)) return;
  setPixel(Pixel, 0, 0, 0);
}

void SnowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay) {
  setAll(red, green, blue);

  int Pixel = random(127);
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
      for (int i = 0; i < 127; i = i + 3) {
        setPixel(i + q, red, green, blue);  //turn every third pixel on
      }
      FastLED.show();
      if (safeDelay(SpeedDelay)) return;
      for (int i = 0; i < 127; i = i + 3) {
        setPixel(i + q, 0, 0, 0);    //turn every third pixel off
      }
    }
  }
}

void theaterChaseRainbow(int SpeedDelay) {
  byte *c;

  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < 127; i = i + 3) {
        c = Wheel( (i + j) % 255);
        setPixel(i + q, *c, *(c + 1), *(c + 2)); //turn every third pixel on
      }
      FastLED.show();
      if (safeDelay(SpeedDelay)) return;
      for (int i = 0; i < 127; i = i + 3) {
        setPixel(i + q, 0, 0, 0);    //turn every third pixel off
      }
    }
  }
}

void BouncingBalls(byte red, byte green, byte blue, int BallCount) {
  float Gravity = -9.81;
  int StartHeight = 1;

  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];

  for (int i = 0 ; i < BallCount ; i++) {
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
  }

  while (true) {
    if (changeFlag) {
      changeFlag = false;
      return;
    }
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i] / 1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

      if ( Height[i] < 0 ) {
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();

        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (127 - 1) / StartHeight);
    }

    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(Position[i], red, green, blue);
    }
    FastLED.show();
    setAll(0, 0, 0);
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
