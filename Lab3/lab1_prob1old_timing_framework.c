#include <stdio.h>
#include <time.h>
// Macro definitions to ensure portablity between both sun.cs and linux.cs

#if defined(sun)
    #define CLOCKNAME CLOCK_HIGHRES
        
#else
    #define CLOCKNAME CLOCK_PROCESS_CPUTIME_ID
#endif
    
int in;  

int out;  

inline void read_inputs_from_ip_if(){

    in = 0;
	out = 0;

	char temp[1];
    printf("Driver Seat Belt Fastened: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        in=in+1;}
    
    printf("Engine Running: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        in=in+2;}
    
    printf("Door Closed: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        in=in+4;}
    
    printf("Key in Car: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        in=in+8;}
    
    printf("Driver on Seat: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        in=in+16;}

    printf("Car Moving: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        in=in+32;}
    
    printf("Door Lock Lever: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        in=in+64;}
    
    printf("Break Pedal: (1 or 0) \n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        in=in+128;}

}

inline void write_output_to_op_if(){

    if((out & 0x1)== 1){
        printf("BELL - Ding\n");}
	else{printf("BELL - Silence\n");}

	if((out & 0x2) == 2){
		printf("DOOR LOCK - Locked\n");}
	else{printf("DOOR LOCK - Unlocked\n");}

	if ((out & 0x4) == 4){
		printf("BREAK - On\n");}
	else{printf("BREAK - Off\n");}

}


//The code segment which implements the decision logic
inline void control_action(){

    //0000 00-10 || 0000 0-01-0
    if ((((in & 0x2)==2) && ((((in & 0x1)==0)? 0:1) == 0)) || (((in & 0x2)==2) && ((((in & 0x4)==0)? 0:1) == 0))){
        out = out + 1;
        printf("%d\n", out);
        printf("1st\n");
    }

    //0101 0000
    if((in & 0x50)==80){
        out = out + 2;
        printf("%d\n", out);
        printf("2nd\n");
    }

    //1010 0000
    if((in & 0xA0)==160){
        out = out + 4;
        printf("%d\n", out);
        printf("3rd\n");
    }

}


/* ---     You should not have to modify anything below this line ---------*/

/*timespec diff from
http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
*/
struct timespec diff(struct timespec start, struct timespec end)
 {
    struct timespec temp;
    //the if condition handles time stamp end being smaller than than 
    //time stamp start which could lead to negative time.

     if ((end.tv_nsec-start.tv_nsec)<0) {
          temp.tv_sec = end.tv_sec-start.tv_sec-1;
          temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
      } else {
          temp.tv_sec = end.tv_sec-start.tv_sec;
          temp.tv_nsec = end.tv_nsec-start.tv_nsec;
      }
  return temp;
 }

int main(int argc, char *argv[])
{
	unsigned int cpu_mhz;
	unsigned long long int begin_time, end_time;
	struct timespec timeDiff,timeres;
	struct timespec time1, time2, calibrationTime;
	
    clock_gettime(CLOCKNAME, &time1);
	clock_gettime(CLOCKNAME, &time2);
	calibrationTime = diff(time1,time2); //calibration for overhead of the function calls
    clock_getres(CLOCKNAME, &timeres);  // get the clock resolution data
	
    read_inputs_from_ip_if(); // get the sensor inputs
	
	clock_gettime(CLOCKNAME, &time1); // get current time
	control_action();       // process the sensors
	clock_gettime(CLOCKNAME, &time2);   // get current time

	write_output_to_op_if();    // output the values of the actuators
	
	timeDiff = diff(time1,time2); // compute the time difference

	printf("Timer Resolution = %u nanoseconds \n ",timeres.tv_nsec);
	printf("Calibrartion time = %u seconds and %u nanoseconds \n ", calibrationTime.tv_sec, calibrationTime.tv_nsec);
    printf("The measured code took %u seconds and ", timeDiff.tv_sec - calibrationTime.tv_sec);
	printf(" %u nano seconds to run \n", timeDiff.tv_nsec - calibrationTime.tv_nsec);
	
	return 0;
}
