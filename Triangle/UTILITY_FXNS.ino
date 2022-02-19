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
