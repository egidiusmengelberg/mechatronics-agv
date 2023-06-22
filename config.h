#define CORNER_SIZE 2.5
#define CORNER_LENGTH 2500
#define CORNER_TOF_ERROR_COUNT 5

#define FLOWERPOT_WAIT_TIME 3000
#define FLOWERPOT_AFTER_LENGTH 512

#define NORMAL_STEPS 128

//stepper left
#define STEPPER_L_1_PIN 2
#define STEPPER_L_2_PIN 3
#define STEPPER_L_3_PIN 4
#define STEPPER_L_4_PIN 5

//stepper right
#define STEPPER_R_1_PIN 6
#define STEPPER_R_2_PIN 7
#define STEPPER_R_3_PIN 8
#define STEPPER_R_4_PIN 9

#define STEPPER_MAX_V 350.0
#define STEPPER_MAX_A 2048.0

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define LOX4_ADDRESS 0x33
#define LOX5_ADDRESS 0x34

// set the pins to shutdown
#define SHT_LOX1 A0
#define SHT_LOX2 A1
#define SHT_LOX3 A2
#define SHT_LOX4 A6
#define SHT_LOX5 A3 
