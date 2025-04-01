#ifndef BUTTON_ASSEMBLY_H
#define BUTTON_ASSEMBLY_H

#include <Arduino.h>

/**
 * @brief A ButtonAssembly class to manage multiple buttons.
 */
class ButtonAssembly {
public:
    /**
     * @brief Constructor to set up button pins.
     *
     * @param numButtons The total number of buttons.
     * @param buttonPins An array of pin numbers assigned to the buttons.
     */
    ButtonAssembly(uint8_t numButtons, const uint8_t* buttonPins);

    /**
     * @brief Initializes the button pins as inputs with pullups.
     */
    void begin();

    /**
     * @brief Updates the state of all buttons.
     *
     * Reads raw states, applies debouncing, and updates the debounced states.
     */
    void updateButtonStates();

    /**
     * @brief Retrieves the debounced state of a specific button.
     *
     * @param buttonNumber The button number (starting from 1).
     * @return True if the button is pressed, False otherwise.
     */
    bool getButtonState(uint8_t buttonNumber);

    /**
     * @brief Determines if any button has been pressed since the last update.
     *
     * @return True if any button is pressed, False otherwise.
     */
    bool anyButtonPressed();

    /**
     * @brief Executes a callback function when a button is pressed.
     *
     * @param buttonNumber The button number.
     * @param modeSelectCallback A callback function to execute.
     */
    void selectMode(uint8_t buttonNumber, void (*modeSelectCallback)(void));

private:
    uint8_t _numButtons;                   // Number of buttons in the assembly.
    const uint8_t* _buttonPins;            // Array of button pins.
    bool* _rawButtonStates;                // Raw unfiltered button states.
    bool* _previousRawButtonStates;        // Previous raw button states.
    bool* _debouncedButtonStates;          // Debounced button states.
    unsigned long* _debounceTimers;        // Timers for debouncing.
    static const int DEBOUNCE_INTERVAL = 20;  // Debounce time in milliseconds.
};

#endif /* BUTTON_ASSEMBLY_H */