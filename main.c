#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>


#include "stepper.h"

int main(void) {

    initSteppers();

    while(1) {
		stepperLStep();
        //_delay_ms(4);
	}
}