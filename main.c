#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

//global variables
bool blinkLed = false;

// config

//led
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_NUM 3  

#define LED2_DDR DDRB
#define LED2_PORT PORTB
#define LED2_NUM 2

#define BUZZ_DDR DDRE
#define BUZZ_PORT PORTE
#define BUZZ_NUM 5

//motor_l
#define MOTOR_L_DDR DDRE
#define MOTOR_L_PORT PORTE
#define MOTOR_L_NUM 3

//motor_r
#define MOTOR_R_DDR DDRH
#define MOTOR_R_PORT PORTH
#define MOTOR_R_NUM 3

//button_up
#define BUTTON_UP_DDR DDRC
#define BUTTON_UP_PORT PORTC
#define BUTTON_UP_PIN PINC
#define BUTTON_UP_NUM 6
//button_down
#define BUTTON_DOWN_DDR DDRC
#define BUTTON_DOWN_PORT PORTC
#define BUTTON_DOWN_PIN PINC
#define BUTTON_DOWN_NUM 7

//endstop_min
#define ENDSTOP_MIN_DDR DDRB
#define ENDSTOP_MIN_PORT PORTL
#define ENDSTOP_MIN_PIN PINL
#define ENDSTOP_MIN_NUM 0
//endstop_max
#define ENDSTOP_MAX_DDR DDRL
#define ENDSTOP_MAX_PORT PORTL
#define ENDSTOP_MAX_PIN PINL
#define ENDSTOP_MAX_NUM 1

//function declarations
void initMotor();
void moveMotor(bool direction);
void stopMotor();
void initButtons();
bool upPressed();
bool downPressed();
bool minPressed();
bool maxPressed();
void initLed(void);
void ledOn(void);
void ledOff(void);

int main(void) {

	initMotor();
	initButtons();
	initLed();

    while(1) {
		// while up pressed and not up endstop move: up and blink
		while (upPressed() && !maxPressed()) {
            if (!blinkLed) {
                ledOn();
            }
            moveMotor(true);
        }

        while (downPressed() && !minPressed()) {
            if (!blinkLed) {
                ledOn();
            }
            moveMotor(false);
        }

        stopMotor();
        ledOff();
	}
}

void initMotor() {
    // set motor pins as outputs
    MOTOR_L_DDR |= (1 << MOTOR_L_NUM);
    MOTOR_R_DDR |= (1 << MOTOR_R_NUM);

    //turn off outputs
    MOTOR_L_PORT &= ~(1 << MOTOR_L_NUM);
    MOTOR_R_PORT &= ~(1 << MOTOR_R_NUM);
}

void moveMotor(bool direction) {
    switch (direction)
    {
		case true:
			MOTOR_L_PORT |= (1 << MOTOR_L_NUM);
			MOTOR_R_PORT &= ~(1 << MOTOR_R_NUM);
			break;
		case false:
			MOTOR_L_PORT &= ~(1 << MOTOR_L_NUM);
			MOTOR_R_PORT |= (1 << MOTOR_R_NUM);
			break;
		default:
			stopMotor();
			break;
    }
}

void stopMotor() {
    MOTOR_L_PORT |= (1 << MOTOR_L_NUM);
    MOTOR_R_PORT |= (1 << MOTOR_R_NUM);
}

void initButtons() {
    //button up
    BUTTON_UP_DDR &= ~(1 << BUTTON_UP_NUM);
    BUTTON_UP_PORT |= (1 << BUTTON_UP_NUM);

    //button down
    BUTTON_DOWN_DDR &= ~(1 << BUTTON_DOWN_NUM);
    BUTTON_DOWN_PORT |= (1 << BUTTON_DOWN_NUM);

	//endstop min
    ENDSTOP_MIN_DDR &= ~(1 << ENDSTOP_MIN_NUM);
    ENDSTOP_MIN_PORT |= (1 << ENDSTOP_MIN_NUM);

    //endstop max
    ENDSTOP_MAX_DDR &= ~(1 << ENDSTOP_MAX_NUM);
    ENDSTOP_MAX_PORT |= (1 << ENDSTOP_MAX_NUM);
}

bool upPressed() {
    return !(BUTTON_UP_PIN & (1 << BUTTON_UP_NUM));
}

bool downPressed() {
    return !(BUTTON_DOWN_PIN & (1 << BUTTON_DOWN_NUM));
}

bool minPressed() {
    return !(ENDSTOP_MIN_PIN & (1 << ENDSTOP_MIN_NUM));
}

bool maxPressed() {
    return !(ENDSTOP_MAX_PIN & (1 << ENDSTOP_MAX_NUM));
}

void initLed(void) {
    LED_DDR |= (1 << LED_NUM);
    LED2_DDR |= (1 << LED2_NUM);  
    BUZZ_DDR |= (1 << BUZZ_NUM);  

    BUZZ_PORT &= ~(1 << BUZZ_NUM);

    TCCR4A = 0;// set entire TCCR1A register to 0
    TCCR4B = 0;// same for TCCR1B
    TCNT4  = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    OCR4A = 7500;// = (16*10^6) / (1*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR4B |= (1 << WGM12);
    // Set CS12 and CS10 bits for 1024 prescaler
    TCCR4B |= (1 << CS12) | (1 << CS10);  
    // enable timer compare interrupt
    TIMSK4 |= (1 << OCIE4A);

    sei();//allow interrupts
}

void ledOn(void) {
    blinkLed = true;
    LED2_PORT |= (1 << LED2_NUM);
}

void ledOff(void) {
    blinkLed = false;
    LED_PORT &= ~(1 << LED_NUM);
    LED2_PORT &= ~(1 << LED2_NUM);
    BUZZ_PORT |= (1 << BUZZ_NUM);
}

ISR(TIMER4_COMPA_vect){
    // LED_PORT |= (1 << LED_NUM);
    if (blinkLed) {
        LED_PORT ^= (1 << LED_NUM);
        LED2_PORT ^= (1 << LED2_NUM);
        BUZZ_PORT ^= (1 << BUZZ_NUM);
    }
}
