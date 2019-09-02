/*
Sample Solution-1 for Lab-1, Problem-4
Add your own INPUT/OUTPUT code to test it.
*/

unsigned int input = 0;  

unsigned int output = 0;  



//For input interface implementation
inline void read_inputs_from_ip_if(){

	char temp[1];

	printf("Driver on Seat: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        input=input+1;}
    
	printf("Driver Seat Belt Fastened: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        input=input+2;}
    
	printf("Engine Running: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        input=input+4;}
    
	
    printf("Door Closed: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        input=input+8;}
    
	
    printf("Key in Car: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        input=input+16;}


    printf("Door Lock Lever: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        input=input+32;}
    
    printf("Break Pedal: (1 or 0) \n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        input=input+64;}
    
	printf("Car Moving: (1 or 0)\n");
    scanf("%s", temp);
    if (strcmp(temp , "1") == 0){
        input=input+128;}
    //printf("%d \n", in);
}

//For output interface implementation
inline void write_output_to_op_if(){

	if((output & 0x1)== 1){
        printf("BELL - Ding\n");}
	else{printf("BELL - Silence\n");}

	if((output & 0x2) == 2){
		printf("DOOR LOCK - Locked\n");}
	else{printf("DOOR LOCK - Unlocked\n");}

	if ((output & 0x4) == 4){
		printf("BREAK - On\n");}
	else{printf("BREAK - Off\n");}

}


//The code segment which implements the decision logic
inline void control_action(){

	//Reset output
	output = 0;
	
	//Requirement 1, 2, 3
	switch (input & 0xf)
	{
		case 5:
		case 7:
		case 13:
			output =  0x1;
	}

	//Requirement 4
	switch (input & 0x31)
	{
		case 32:
		case 49:
			output = output | 0x2;
	}

	//Requirement 5
	if ((input & 0xc0) == 0xc0)
			output = output | 0x4;

}


//The main program
int main(int argc, char *argv[])
{
	
	read_inputs_from_ip_if();
	control_action();
	write_output_to_op_if();
	
	return 0;
}
