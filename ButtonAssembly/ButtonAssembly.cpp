#include "ButtonAssembly.h"

// Constructor initializes button configuration.
ButtonAssembly::ButtonAssembly(uint8_t numButtons, const uint8_t* buttonPins) {
    _numButtons = numButtons;
    _buttonPins = buttonPins;

    // Allocate memory for button states.
    _rawButtonStates = new bool[numButtons];
    _previousRawButtonStates = new bool[numButtons];
    _debouncedButtonStates = new bool[numButtons];
    _debounceTimers = new unsigned long[numButtons];

    // Initialize all button states.
    for (uint8_t i = 0; i < numButtons; ++i) {
        _rawButtonStates[i] = false;
        _previousRawButtonStates[i] = false;
        _debouncedButtonStates[i] = false;
        _debounceTimers[i] = 0;
    }
}

// Begin initializes the button pins.
void ButtonAssembly::begin() {
    for (uint8_t i = 0; i < _numButtons; ++i) {
        pinMode(_buttonPins[i], INPUT_PULLUP);
    }
}

// Update button states using debouncing logic.
void ButtonAssembly::updateButtonStates() {
    unsigned long currentTime = millis();

    for (uint8_t i = 0; i < _numButtons; ++i) {
        // Read raw button state.
        _rawButtonStates[i] = !digitalRead(_buttonPins[i]);  // Pullup resistor means LOW = pressed.

        // Debounce logic.
        if (_rawButtonStates[i] != _previousRawButtonStates[i]) {
            // Reset debounce timer when the state changes.
            _debounceTimers[i] = currentTime;
        } else if ((currentTime - _debounceTimers[i]) > DEBOUNCE_INTERVAL) {
            // Apply debounced state if stable over the interval.
            _debouncedButtonStates[i] = _rawButtonStates[i];
        }

        // Save the previous raw state for next iteration.
        _previousRawButtonStates[i] = _rawButtonStates[i];
    }
}

// Retrieve the debounced state of a specific button.
bool ButtonAssembly::getButtonState(uint8_t buttonNumber) {
    if (buttonNumber <= _numButtons && buttonNumber > 0) {
        return _debouncedButtonStates[buttonNumber - 1];
    }
    return false;  // Invalid button number.
}

// Check if any button is pressed.
bool ButtonAssembly::anyButtonPressed() {
    for (uint8_t i = 0; i < _numButtons; ++i) {
        if (_debouncedButtonStates[i]) {
            return true;
        }
    }
    return false;
}

// Execute a callback when a button is pressed.
void ButtonAssembly::selectMode(uint8_t buttonNumber, void (*modeSelectCallback)(void)) {
    if (getButtonState(buttonNumber)) {
        modeSelectCallback();  // Call the user's callback function.
    }
}