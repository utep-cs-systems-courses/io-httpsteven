// main.c

#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

// Define states
enum States {
    IDLE,
    SOUND_1,
    SOUND_2,
    SOUND_3,
    SOUND_4,
    // Add more states as needed
};

// Global variables
enum States currentState = IDLE;

// Function to handle button press
void buttonPressHandler(int button) {
    // Transition to a new state based on the pressed button
    switch (button) {
        case 0:
            currentState = IDLE;
            break;
        case 1:
            currentState = SOUND_1;
            break;
        case 2:
            currentState = SOUND_2;
            break;
        case 3:
            currentState = SOUND_3;
            break;
        case 4:
            currentState = SOUND_4;
            break;
        // Add more cases as needed
    }
}

// Function to handle button release
void buttonReleaseHandler() {
    // Transition back to the original state
    currentState = IDLE;
}

// Function to update the state machine
void updateStateMachine() {
    // Implement logic based on the current state
    switch (currentState) {
        case IDLE:
            // Perform actions for the IDLE state
            P1OUT &= ~LED_RED; // Turn off red LED
            P1OUT &= ~LED_GREEN; // Turn off green LED
            buzzer_set_period(0); // Turn off the buzzer
            break;
        case SOUND_1:
            // Perform actions for the SOUND_1 state
            P1OUT |= LED_RED; // Turn on red LED
            P1OUT &= ~LED_GREEN; // Turn off green LED
            buzzer_set_period(1000); // Set buzzer frequency for sound 1
            break;
        case SOUND_2:
            // Perform actions for the SOUND_2 state
            P1OUT &= ~LED_RED; // Turn off red LED
            P1OUT |= LED_GREEN; // Turn on green LED
            buzzer_set_period(2000); // Set buzzer frequency for sound 2
            break;
        case SOUND_3:
            // Perform actions for SOUND_3
            P1OUT ^= LED_RED; // Toggle red LED
            P1OUT ^= LED_GREEN; // Toggle green LED
            buzzer_set_period(1500); // Set buzzer frequency for sound 3
            break;

        case SOUND_4:
            // Perform actions for SOUND_4
            P1OUT |= LED_RED; // Turn on red LED
            P1OUT |= LED_GREEN; // Turn on green LED
            buzzer_set_period(2500); // Set buzzer frequency for sound 4
            break;

        // Add more cases for other states
    }
}

int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // Configure clocks and ports
    configureClocks();
    P1DIR |= LED_RED | LED_GREEN;
    P1OUT &= ~(LED_RED | LED_GREEN);

    // Initialize buzzer
    buzzer_init();

    // Main loop
    while (1) {
        // Update the state machine
        updateStateMachine();

        // Check for button press and release
        for (int button = 0; button < 4; button++) {
            if (!(P2IN & (BIT0 << button))) {
                buttonPressHandler(button);
                __delay_cycles(100000); // Debounce delay
            }
        }

        // Check for button release (assuming only one button can be pressed at a time)
        if (P2IN & (BIT0 | BIT1 | BIT2 | BIT3)) {
            buttonReleaseHandler();
        }

        // Add a delay or use timers to control the timing of the state machine
        __delay_cycles(100000); // Adjust this delay as needed
    }

    return 0;
}
