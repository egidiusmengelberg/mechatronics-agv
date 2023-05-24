#include "stepper.h"

void initSteppers() 
{
    //set as output
    STEPPER_L_1_DDR |= (1 << STEPPER_L_1_NUM);
    STEPPER_L_2_DDR |= (1 << STEPPER_L_2_NUM);
    STEPPER_L_3_DDR |= (1 << STEPPER_L_3_NUM);
    STEPPER_L_4_DDR |= (1 << STEPPER_L_4_NUM);
    //turn off
    STEPPER_L_1_PORT &= ~(1 << STEPPER_L_1_NUM);
    STEPPER_L_2_PORT &= ~(1 << STEPPER_L_2_NUM);
    STEPPER_L_3_PORT &= ~(1 << STEPPER_L_3_NUM);
    STEPPER_L_4_PORT &= ~(1 << STEPPER_L_4_NUM);
    //set as output
    // STEPPER_R_1_DDR |= (1 << STEPPER_R_1_NUM);
    // STEPPER_R_2_DDR |= (1 << STEPPER_R_2_NUM);
    // STEPPER_R_3_DDR |= (1 << STEPPER_R_3_NUM);
    // STEPPER_R_4_DDR |= (1 << STEPPER_R_4_NUM);
    // //turn off
    // STEPPER_R_1_PORT &= ~(1 << STEPPER_R_1_NUM);
    // STEPPER_R_2_PORT &= ~(1 << STEPPER_R_2_NUM);
    // STEPPER_R_3_PORT &= ~(1 << STEPPER_R_3_NUM);
    // STEPPER_R_4_PORT &= ~(1 << STEPPER_R_4_NUM);
}

void stepperLStep()
{
    STEPPER_L_1_PORT |= (1 << STEPPER_L_1_NUM);
    STEPPER_L_2_PORT &= ~(1 << STEPPER_L_2_NUM);
    STEPPER_L_3_PORT &= ~(1 << STEPPER_L_3_NUM);
    STEPPER_L_4_PORT &= ~(1 << STEPPER_L_4_NUM);
    _delay_ms(6);
    STEPPER_L_1_PORT |= (1 << STEPPER_L_1_NUM);
    STEPPER_L_2_PORT |= (1 << STEPPER_L_2_NUM);
    STEPPER_L_3_PORT &= ~(1 << STEPPER_L_3_NUM);
    STEPPER_L_4_PORT &= ~(1 << STEPPER_L_4_NUM);
    _delay_ms(6);
    STEPPER_L_1_PORT &= ~(1 << STEPPER_L_1_NUM);
    STEPPER_L_2_PORT |= (1 << STEPPER_L_2_NUM);
    STEPPER_L_3_PORT &= ~(1 << STEPPER_L_3_NUM);
    STEPPER_L_4_PORT &= ~(1 << STEPPER_L_4_NUM);
    _delay_ms(6);
    STEPPER_L_1_PORT &= ~(1 << STEPPER_L_1_NUM);
    STEPPER_L_2_PORT |= (1 << STEPPER_L_2_NUM);
    STEPPER_L_3_PORT |= (1 << STEPPER_L_3_NUM);
    STEPPER_L_4_PORT &= ~(1 << STEPPER_L_4_NUM);
    _delay_ms(6);
    STEPPER_L_1_PORT &= ~(1 << STEPPER_L_1_NUM);
    STEPPER_L_2_PORT &= ~(1 << STEPPER_L_2_NUM);
    STEPPER_L_3_PORT |= (1 << STEPPER_L_3_NUM);
    STEPPER_L_4_PORT &= ~(1 << STEPPER_L_4_NUM);
    _delay_ms(6);
    STEPPER_L_1_PORT &= ~(1 << STEPPER_L_1_NUM);
    STEPPER_L_2_PORT &= ~(1 << STEPPER_L_2_NUM);
    STEPPER_L_3_PORT |= (1 << STEPPER_L_3_NUM);
    STEPPER_L_4_PORT |= (1 << STEPPER_L_4_NUM);
    _delay_ms(6);
    STEPPER_L_1_PORT &= ~(1 << STEPPER_L_1_NUM);
    STEPPER_L_2_PORT &= ~(1 << STEPPER_L_2_NUM);
    STEPPER_L_3_PORT &= ~(1 << STEPPER_L_3_NUM);
    STEPPER_L_4_PORT |= (1 << STEPPER_L_4_NUM);
    _delay_ms(6);
}

void stepperRStep()
{
    // STEPPER_L_1_PORT |= (1 << STEPPER_L_1_NUM);
    // STEPPER_L_2_PORT &= ~(1 << STEPPER_L_2_NUM);
    // STEPPER_L_3_PORT &= ~(1 << STEPPER_L_3_NUM);
    // STEPPER_L_4_PORT &= ~(1 << STEPPER_L_4_NUM);
    // _delay_ms(1);
    // STEPPER_L_1_PORT &= ~(1 << STEPPER_L_1_NUM);
    // STEPPER_L_2_PORT |= (1 << STEPPER_L_2_NUM);
    // STEPPER_L_3_PORT &= ~(1 << STEPPER_L_3_NUM);
    // STEPPER_L_4_PORT &= ~(1 << STEPPER_L_4_NUM);
    // _delay_ms(1);
    // STEPPER_L_1_PORT &= ~(1 << STEPPER_L_1_NUM);
    // STEPPER_L_2_PORT &= ~(1 << STEPPER_L_2_NUM);
    // STEPPER_L_3_PORT |= (1 << STEPPER_L_3_NUM);
    // STEPPER_L_4_PORT &= ~(1 << STEPPER_L_4_NUM);
    // _delay_ms(1);
    // STEPPER_L_1_PORT &= ~(1 << STEPPER_L_1_NUM);
    // STEPPER_L_2_PORT &= ~(1 << STEPPER_L_2_NUM);
    // STEPPER_L_3_PORT &= ~(1 << STEPPER_L_3_NUM);
    // STEPPER_L_4_PORT |= (1 << STEPPER_L_4_NUM);
    // _delay_ms(1);
    // STEPPER_L_4_PORT &= ~(1 << STEPPER_L_4_NUM);
}