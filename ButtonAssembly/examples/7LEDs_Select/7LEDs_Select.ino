#include "ButtonAssembly.h"

// Define button and LED configurations.
const uint8_t NUM_BUTTONS = 4;
const uint8_t BUTTON_PINS[] = {2, 3, 4, 5};
const uint8_t LED_PINS[] = {6, 7, 8, 9, 10, 11, 12};

// Instantiate the ButtonAssembly object.
ButtonAssembly buttonAssembly(NUM_BUTTONS, BUTTON_PINS);

// Define a callback function for button presses.
void ledToggleExample() {
    // Toggle LEDs based on button presses.
    for (uint8_t i = 0; i < NUM_BUTTONS; ++i) {
        if (buttonAssembly.getButtonState(i + 1)) {
            digitalWrite(LED_PINS[i], !digitalRead(LED_PINS[i]));
        }
    }
}

void setup() {
    // Initialize serial communication for debugging (optional).
    Serial.begin(115200);

    // Set LED pins as outputs.
    for (uint8_t i = 0; i < sizeof(LED_PINS) / sizeof(LED_PINS[0]); ++i) {
        pinMode(LED_PINS[i], OUTPUT);
    }

    // Begin monitoring the buttons.
    buttonAssembly.begin();
}

void loop() {
    // Poll the button states continuously.
    buttonAssembly.updateButtonStates();

    // Register a callback for button presses.
    for (uint8_t i = 1; i <= NUM_BUTTONS; ++i) {
        buttonAssembly.selectMode(i, ledToggleExample);
    }
}