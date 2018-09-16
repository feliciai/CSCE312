// CSCE312: Lab-1 Problem-3 framework

/* ***   README   **** */

/*
 This example program sounds the bell when driver is on seat
 AND haven't closed the doors. Use the general framework and the function
 shells, replace the code inside  the control_action() function with your
 own code to do problems 3 and 4.
 
 Note: This code is designed to run in an infinite loop to mimic a real control system.
 If you prefer to read the inputs from a file, modify the code appropriately to terminate the
 loop when all the inputs have been processed.
 
 Turning in this file without your code will result in zero points being awarded for this problem.
 
 run this file as : gcc filename.c -o executableName
 
 */

#include <stdio.h> //This is useful to do i/o to test the code
#include <stdlib.h>
#include <stdbool.h>

// SENSORS
// 0 = DOS; 1 = DSBF; 2 = ER; 3 = DC; 4 = KIC; 5 = DLC; 6 = BP; 7 = CM
unsigned int sensor_inputs;

// ACTUATORS
// 0 = BELL; 1 = DLA; 2 = BA
unsigned int actuator_outputs = 0x00;

bool shift_read_sensors(int feature_index) {
    unsigned int feature_val = (sensor_inputs & (0x01 << feature_index));
    return ((feature_val == 0) ?  0 : 1) ;
}

bool shift_read_actuators(int index) {
    unsigned int actuator_val = (actuator_outputs & (0x01 << index));
    return ((actuator_val == 0) ?  0 : 1) ;
}

unsigned int set_actuator(unsigned int actuator_index, bool end_state) { // ex. 0 (BELL)
    unsigned int output;
    if (end_state) { // want to turn actuator on
        actuator_outputs = actuator_outputs | (1 << actuator_index);
        output = actuator_outputs;
    }
    else { // want to turn actuator off
        actuator_outputs = actuator_outputs & ~(1 << actuator_index);
        output = actuator_outputs;
    }
    return output;
}

void read_inputs_from_ip_if() {
    //place your input code here
    //to read the current state of the available sensors

    sensor_inputs = 0xa3;
    printf("sensor inputs: %u %u %u %u %u %u %u %u", shift_read_sensors(0), shift_read_sensors(1), shift_read_sensors(2), shift_read_sensors(3), shift_read_sensors(4), shift_read_sensors(5), shift_read_sensors(6), shift_read_sensors(7));

    return;
}

void write_output_to_op_if() {
    
    //place your output code here
    //to display/print the state of the 3 actuators (DLA/BELL/BA)
    FILE *output_file;
    if ( (output_file = fopen("lab1_prob4_output.txt", "w")) == NULL)
    {
        printf("Error opening the file, so exiting\n");
        exit(1);
    }
    fprintf(output_file, "given sensor inputs: %u %u %u %u %u %u %u %u", shift_read_sensors(0), shift_read_sensors(1), shift_read_sensors(2), shift_read_sensors(3), shift_read_sensors(4), shift_read_sensors(5), shift_read_sensors(6), shift_read_sensors(7));
    fprintf(output_file, "%u %u %u", shift_read_actuators(0), shift_read_actuators(1), shift_read_actuators(2));
    printf("\nactuator outputs: %u %u %u", shift_read_actuators(0), shift_read_actuators(1), shift_read_actuators(2));
    
    exit(0);
}

//The code segment which implements the decision logic
void control_action() {

    /*
     The code given here sounds the bell when driver is on seat
     AND hasn't closed the doors.
     */

    if (shift_read_sensors(0) & !shift_read_sensors(3)) {
        printf("\ndriver is on seat and doors are open ");
        set_actuator(0, 1);
    }
    else {
        set_actuator(0, 0);
    }
    
    /* REQUIREMENTS 1, 2, & 3:
     1) Sounds the bell when driver starts the engine without seatbelt on
     
     2) Sounds the bell when driver starts the engine with open door(s)
     
     3) Stops bell when conditions return to normal
     */
    
    if (shift_read_sensors(2) && (!shift_read_sensors(1) || !shift_read_sensors(3))) { // && is a logical operator for boolean operands
        printf("\ndriver starts engine, but seatbelt is off or doors are open ");
        set_actuator(0, 1);
    }
    else {
        set_actuator(0, 0);
    }

    /* REQUIREMENT 4:
     Doors should not lock if driver is not in the car and keys are in car
     */
    
    if (shift_read_sensors(5) && !shift_read_sensors(0) && shift_read_sensors(4)) {
        printf("\nattempted to lock doors, but driver is out of car and keys are in car ");
        set_actuator(1, 0);
    }
    else if (shift_read_sensors(5)) {
        set_actuator(1, 1);
    }
    
    /* REQUIREMENT 5:
     Brakes when brake pedal is pressed and car is moving
     Releases brakes when brake pedal is no longer pressed
     */
    
    if (shift_read_sensors(6) && shift_read_sensors(7)) {
        printf("\nbrakes should be on ");
        set_actuator(2, 1);
    }
    else {
        set_actuator(2, 0);
    }
}

    /* ---     You should not have to modify anything below this line ---------*/
        
        int main(int argc, char *argv[])
    {
        
        /*The main control loop which keeps the system alive and responsive for ever,
         until the system is powered off */
        for (; ; )
        {
            read_inputs_from_ip_if();
            control_action();
            write_output_to_op_if();
            
        }
        
        return 0;
    }

