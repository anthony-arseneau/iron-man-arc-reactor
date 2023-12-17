#include <FastLED.h>

#define CENTER_LED_PIN 3
#define RING_LED_PIN 4
#define CENTER_NUM_LEDS 9
#define RING_NUM_LEDS 15
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0

CRGB ringLeds[RING_NUM_LEDS];
CRGB centerLeds[CENTER_NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, CENTER_LED_PIN, RGB>(centerLeds, CENTER_NUM_LEDS);
  FastLED.addLeds<WS2812B, RING_LED_PIN, RGB>(ringLeds, RING_NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.setBrightness(255);
  //startupAnimation();
  for(int i = 0; i < CENTER_NUM_LEDS; i++){
    centerLeds[i] = CHSV(210, 255, 255);
  }
}

void loop() {
  static uint8_t hue = 0;
  static int pos = 0;

  fadeToBlackBy(ringLeds, RING_NUM_LEDS, 10); // Adjust the fade value (0-255) for the speed of fading
  
  // Place a bright pixel at 'pos'
  ringLeds[pos] = CHSV(210, 255, 255);
  
  // Show the LED array
  FastLED.show();
  
  // Increment the position
  pos = (pos + 1) % RING_NUM_LEDS;
  
  // Add a delay to control the speed of the trail
  delay(50); // Adjust this for the desired speed
}

// "Booting" animation startup
void startupAnimation(){
  // Ring slowly fills
  for(int i = 0; i < RING_NUM_LEDS; i++){
    ringLeds[i] = CRGB(0, 0, 255);
    FastLED.show();
    delay(100);
  }
  // Suspenseful wait
  delay(1000);

  // Suspensful fade of the led ring all at the same time
  int currentBrightness = MAX_BRIGHTNESS;
  for(int i = 0; i < 256; i++){
    for(int j = 0; j < RING_NUM_LEDS; j++){
      ringLeds[j].nscale8(2);
    }
    FastLED.show();
    delay(1000);
  }

  
}