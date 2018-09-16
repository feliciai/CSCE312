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

// SENSORS
unsigned int DOS, DSBF, ER, DC, KIC, DLC, BP, CM;

// ACTUATORS
unsigned int BELL, DLA, BA;


void read_inputs_from_ip_if() {
    // takes formatted .txt file:
    // boolean (1/0) value sensor states in order listed on lab assignment:
    // DOS, DSBF, ER, DC, KIC, DLC, BP, CM
    
    //place your input code here
    //to read the current state of the available sensors
    
    FILE *input_file;
    input_file = fopen("lab1_prob3_input.txt", "r");
    fscanf(input_file, "%u %u %u %u %u %u %u %u", &DOS, &DSBF, &ER, &DC, &KIC, &DLC, &BP, &CM);
    fclose(input_file);
    
    return;
}

void write_output_to_op_if() {
    
    //place your output code here
    //to display/print the state of the 3 actuators (DLA/BELL/BA)
    
    FILE *output_file;
    if ( (output_file = fopen("lab1_prob3_output.txt", "w")) == NULL)
    {
        printf("Error opening the file, so exiting\n");
        exit(1);
    }
    fprintf(output_file, "%u %u %u", BELL, DLA, BA);
    
    exit(0);
}


//The code segment which implements the decision logic
void control_action() {
    
    /*
     The code given here sounds the bell when driver is on seat
     AND hasn't closed the doors. (Requirement-2)
     Replace this code segment with your own code to do problems 3 and 4.
     */
    
    if (DOS && !DC)
        BELL = 1;
    else BELL = 0;
    
    /* REQUIREMENTS 1, 2, & 3:
     1) Sounds the bell when driver starts the engine without seatbelt on
     
     2) Sounds the bell when driver starts the engine with open door(s)
     
     3) Stops bell when conditions return to normal
     */
    
    if (ER && (!DSBF || !DC)) { // && is a logical operator for boolean operands
        BELL = 1;
    }
    else {
        BELL = 0;
    }
    
    /* REQUIREMENT 4:
     Doors should not lock if driver is not in the car and keys are in car
     */
    
    if (DLC && !DOS && KIC) {
        DLA = 0;
    }
    else if (DLC) {
        DLA = 1;
    }
    
    /* REQUIREMENT 5:
     Brakes when brake pedal is pressed and car is moving
     Releases brakes when brake pedal is no longer pressed
     */
    
    if (BP && CM) {
        BA = 1;
    }
    else {
        BA = 0;
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

