#include "ButtonAssembly.h"
#include <LiquidCrystal.h>  // Include the LiquidCrystal library

// Define button and LCD configurations.
const uint8_t NUM_BUTTONS = 4;
const uint8_t BUTTON_PINS[] = {2, 3, 4, 5};

// Define the LCD pins.
const uint8_t RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Instantiate the ButtonAssembly object.
ButtonAssembly buttonAssembly(NUM_BUTTONS, BUTTON_PINS);

// Predefined characters to display based on button presses.
char characters[] = {'A', 'B', 'C', 'D'};

void setup() {
    // Initialize serial communication for debugging (optional).
    Serial.begin(115200);

    // Initialize the LCD.
    lcd.begin(16, 2);  // 16 columns x 2 rows
    lcd.clear();        // Clear the LCD screen
    lcd.print("Press a button");  // Initial message
}

void loop() {
    // Poll the button states continuously.
    buttonAssembly.updateButtonStates();

    // Display the character corresponding to the pressed button.
    for (uint8_t i = 1; i <= NUM_BUTTONS; ++i) {
        if (buttonAssembly.getButtonState(i)) {
            lcd.setCursor(0, 1);               // Move cursor to the second row
            lcd.print(characters[i - 1]);      // Display the selected character
        }
    }
}