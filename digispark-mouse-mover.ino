#include "DigiMouse.h"

// Constants for smooth square movement
const char PIXEL_STEP = 2;             // Move 2 pixels per step
const unsigned int STEPS_PER_SIDE = 2; // 2 steps per side

// Base delay for square cycle (1 minute = 60,000 ms)
const unsigned long BASE_DELAY = (1UL * 60UL * 1000UL);
// Variation: ± 10 seconds (10,000 ms)
const unsigned long DELAY_VARIATION = 10000UL;

void setup() {
  DigiMouse.begin();
  pinMode(1, OUTPUT);
  // Initialize random seed (if available, using an unconnected analog pin)
  randomSeed(analogRead(0));
}

void loop() {
  // Draw the square:
  // Top side: move right
  for (unsigned int i = 0; i < STEPS_PER_SIDE; i++) {
    moveMouse(PIXEL_STEP, 0);
  }
  // Right side: move down
  for (unsigned int i = 0; i < STEPS_PER_SIDE; i++) {
    moveMouse(0, PIXEL_STEP);
  }
  // Bottom side: move left
  for (unsigned int i = 0; i < STEPS_PER_SIDE; i++) {
    moveMouse(-PIXEL_STEP, 0);
  }
  // Left side: move up
  for (unsigned int i = 0; i < STEPS_PER_SIDE; i++) {
    moveMouse(0, -PIXEL_STEP);
  }

  // Compute a random delay between BASE_DELAY - DELAY_VARIATION and BASE_DELAY + DELAY_VARIATION
  unsigned long randomDelay = random(BASE_DELAY - DELAY_VARIATION, BASE_DELAY + DELAY_VARIATION);
  longDelay(randomDelay);
}

// Function to perform a single mouse movement with LED blink feedback.
void moveMouse(int x, int y) {
  // Send combined X and Y movement as one report.
  DigiMouse.move(x, y, 0);
  
  // Blink LED on pin 1 for feedback.
  digitalWrite(1, HIGH);
  DigiMouse.delay(10);
  digitalWrite(1, LOW);
  
  // Delay between moves.
  DigiMouse.delay(200);
}

// Custom long delay function that breaks a long delay into 100 ms chunks
void longDelay(unsigned long ms) {
  const unsigned long chunk = 100; // Delay in 100 ms chunks.
  unsigned long elapsed = 0;
  while (elapsed < ms) {
    DigiMouse.delay(chunk);
    elapsed += chunk;
  }
}
