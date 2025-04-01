#include "ButtonAssembly.h"

// Define button and2; LED configurations.
const uint8_t PIN_BUTTON = 2;                     // Button connected to pin 2.
const uint8_t NUM_LEDS = 10;                      // Controlling ten LEDs.
const uint8_t LED_PINS[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12};  // LEDs connected to pins 3–12.

// Instantiate the ButtonAssembly object.
ButtonAssembly buttonAssembly(1, &PIN_BUTTON);

// Track the current LED pattern.
enum PatternType {
    ALL_OFF,
    FIRST_ON,
    ALTERNATING,
    ALL_ON,
    CUSTOM_PATTERN,
    MAX_PATTERNS
};
PatternType currentPattern = ALL_OFF;

// Function prototypes for LED patterns.
void allLedsOff();
void firstLedOn();
void alternatingLeds();
void allLedsOn();
void customPattern();

void setup() {
    // Initialize serial communication for debugging (optional).
    Serial.begin(115200);

    // Set LED pins as outputs.
    for (uint8_t i = 0; i < NUM_LEDS; ++i) {
        pinMode(LED_PINS[i], OUTPUT);
    }

    // Begin monitoring the button.
    buttonAssembly.begin();
}

void loop() {
    // Poll the button state.
    buttonAssembly.updateButtonStates();

    // Detect button press and cycle through LED patterns.
    if (buttonAssembly.getButtonState(1)) {
        // Manually increment the currentPattern and wrap around if necessary.
        currentPattern = static_cast<PatternType>((static_cast<int>(currentPattern) + 1) % MAX_PATTERNS);

        switch (currentPattern) {
            case ALL_OFF:
                allLedsOff();
                break;
            case FIRST_ON:
                firstLedOn();
                break;
            case ALTERNATING:
                alternatingLeds();
                break;
            case ALL_ON:
                allLedsOn();
                break;
            case CUSTOM_PATTERN:
                customPattern();
                break;
        }
    }
}

// LED Pattern Functions:
void allLedsOff() {
    for (uint8_t i = 0; i < NUM_LEDS; ++i) {
        digitalWrite(LED_PINS[i], LOW);
    }
}

void firstLedOn() {
    digitalWrite(LED_PINS[0], HIGH);
    for (uint8_t i = 1; i < NUM_LEDS; ++i) {
        digitalWrite(LED_PINS[i], LOW);
    }
}

void alternatingLeds() {
    for (uint8_t i = 0; i < NUM_LEDS; ++i) {
        digitalWrite(LED_PINS[i], i % 2 ? HIGH : LOW);
    }
}

void allLedsOn() {
    for (uint8_t i = 0; i < NUM_LEDS; ++i) {
        digitalWrite(LED_PINS[i], HIGH);
    }
}

void customPattern() {
    // Example custom pattern: flash every other LED.
    for (uint8_t i = 0; i < NUM_LEDS; ++i) {
        digitalWrite(LED_PINS[i], i % 2 ? HIGH : LOW);
        delay(100);
        digitalWrite(LED_PINS[i], LOW);
    }
}
