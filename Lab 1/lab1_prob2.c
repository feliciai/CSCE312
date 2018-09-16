#include <stdio.h> //For input/output
#include <sys/time.h> //For gettimeofday() function

int main()
{
    unsigned int uint_var;
    double double_var;
    long long_var;
    long long long_long_var;
    char char_var;
    float float_var;
    struct timeval this_instant;
    long int time_stamp;
    
    
    FILE *my_file_pointer;
    if ( (my_file_pointer = fopen("lab1_prob2_out.txt", "w")) == NULL)
    {
        printf("Error opening the file, so exiting\n");
        //exit(1);
    }
    
    gettimeofday(&this_instant,0);
    time_stamp = this_instant.tv_sec;
    
    //Code segment for file I/O
    fprintf(my_file_pointer, "This program was executed at time : %d secs\n", time_stamp);
    
    
    fprintf(my_file_pointer, "The sizes of different data type for this machine and compiler are -\n");
    fprintf(my_file_pointer, "unsigned int data type is %d bytes or %d bits long\n",sizeof(uint_var), sizeof(uint_var)*8 );
    fprintf(my_file_pointer, "double data type is %d bytes or %d bits long\n",sizeof(double_var), sizeof(double_var)*8 );
    fprintf(my_file_pointer, "long data type is %d bytes or %d bits long\n",sizeof(long_var), sizeof(long_var)*8 );
    fprintf(my_file_pointer, "long long data type is %d bytes or %d bits long\n",sizeof(long_long_var), sizeof(long_long_var)*8 );
    fprintf(my_file_pointer, "char data type is %d bytes or %d bits long\n",sizeof(char_var), sizeof(char_var)*8 );
    fprintf(my_file_pointer, "float data type is %d bytes or %d bits long\n",sizeof(float_var), sizeof(float_var)*8 );
    fprintf(my_file_pointer, "timeval data type is a %d with %d bytes or %d bits long\n",sizeof(this_instant), sizeof(this_instant)*8 );
            
    //Code segment for console I/O, this can be used instead of the file I/O
    printf("This program was executed at time : %d secs\n", time_stamp);
    
    
    printf("The sizes of different data type for this machine and compiler are -\n");
    printf("unsigned int data type is %d bytes or %d bits long\n",sizeof(uint_var), sizeof(uint_var)*8 );
    printf("double data type is %d bytes or %d bits long\n",sizeof(double_var), sizeof(double_var)*8 );
    printf("long data type is %d bytes or %d bits long\n",sizeof(long_var), sizeof(long_var)*8 );
    printf("long long data type is %d bytes or %d bits long\n",sizeof(long_long_var), sizeof(long_long_var)*8 );
    printf("char data type is %d bytes or %d bits long\n",sizeof(char_var), sizeof(char_var)*8 );
    printf("float data type is %d bytes or %d bits long\n",sizeof(float_var), sizeof(float_var)*8 );
    printf("timeval data type is %d bytes or %d bits long\n", sizeof(this_instant), sizeof(this_instant)*8 );
    
    fclose(my_file_pointer); //To close the output file, mandatory to actually get an output !
    
    return 0;
}
    
    

            
