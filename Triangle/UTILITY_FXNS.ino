//------------------------------------- UTILITY FXNS --------------------------------------
//---SET THE COLOR OF A SINGLE RGB LED
void set_color_led(int adex, int cred, int cgrn, int cblu) {
  leds[adex].setRGB( cred, cgrn, cblu);
}

//---FIND INDEX OF HORIZONAL OPPOSITE LED
int horizontal_index(int i) {
int EVENODD = 127 % 2;
  if (i == 0) {
    return 0;
  }
  if (i == 127/2 && EVENODD == 1) {
    return 127/2 + 1;
  }
  if (i == 127/2 && EVENODD == 0) {
    return 127/2;
  }
  return 127 - i;
}

//---FIND INDEX OF ANTIPODAL OPPOSITE LED
int antipodal_index(int i) {
  int iN = i + 127/2;
  if (i >= 127/2) {
    iN = ( i + 127/2 ) % 127;
  }
  return iN;
}

//---FIND ADJACENT INDEX CLOCKWISE
int adjacent_cw(int i) {
  int r;
  if (i < 127 - 1) {
    r = i + 1;
  }
  else {
    r = 0;
  }
  return r;
}

//---FIND ADJACENT INDEX COUNTER-CLOCKWISE
int adjacent_ccw(int i) {
  int r;
  if (i > 0) {
    r = i - 1;
  }
  else {
    r = 127 - 1;
  }
  return r;
}

void copy_led_array() {
  for (int i = 0; i < 127; i++ ) {
    ledsX[i][0] = leds[i].r;
    ledsX[i][1] = leds[i].g;
    ledsX[i][2] = leds[i].b;
  }
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < 127; i++ ) {
    setPixel(i, red, green, blue);
  }
  FastLED.show();
}
