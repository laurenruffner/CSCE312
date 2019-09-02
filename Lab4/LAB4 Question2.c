/*
The microprocessor will orchestrate the reading, writing from the digital and analog I/O system and the memory. 
These reading and writing operations are the tasks that have to be executed in the system. Write down the 
sequence of operations/tasks in- (see tip #13)
	(I) Pseudo-code. 
	(II) Task timing diagram for the following tasks:
		a) Reading from ROM
		b) Reading from RAM
		c) Writing into RAM
		d) Reading from digital input line
		e) Writing to a digital output line

Example “C” code fragment for the 8 bit system (code for IO permission are not shown) 
–(This reads in a value i through port 0xFF and prints out i+1 through 0x0A.)
unsigned int i, j;
#define INPORT 0xFF
#define OUTPORT 0x0A
….
for(; ; ) {
i = inb(INPORT);
j = i +1;
outb(j, OUTPORT);
}
Task 1: Read from an in port which is addressable with address “FF”
Task 2: Write the value to memory address corresponding to “i”
Task 3: Read from memory location “i”
Task 4: Read from memory location “j”
Task 5: Add the values received from location “i” to the value got from “j”
Task 6: Write the added value to location “j”
Task 7: Read from memory location “j”
Task 8: Write the value got from “j” to an out port which is addressable with 0x0A

In the C code we mimic the behavior of the hardware that we are designing in logisim. 
As long as you are able to show the following tasks in your code that is good enough. 
The code should be setup to run in an infinite loop to repeatedly execute these tasks.
a)Reading from ROM
b)Reading from RAM
c)Writing into RAM
d)Reading from digital input line
e)Writing to a digital output line
Coming back to your question, you don't need to implement the "address bus" and "I/O" 
system in detail in c-code. You can read/write from/to a file in both the cases. 
You basically have to write a code to mimic a very high level functional model of ROM 
(read from any address), RAM (read/write from/to any address), and the I/O system 
(user input and output to the user). 
*/

#define INPORT 0xFF
#define OUTPORT 0x0A

int main(int argc, char *argv[]){
	unsigned int i, j;
	int ROM_data, RAM_data_i, RAM_data_j, j, RAM_out;
	int i;	
	// THE USER NEEDS TO IDENTIFY WHAT I IS SPECIFICALLY (ITS THE ADDRESS IN ROM)
	for(;;){
		/*
		User input to select the memory location of i to be used
		*/
		// 0 1 2 3 4 5 6 7
		ROM_data = read_ROM(INPORT);
		write_RAM(i,ROM_data);
		RAM_data_i = read_RAM(i);
		j = i+1;
		RAM_data_j = read_RAM(j);
		RAM_out = RAM_data_i + RAM_data_j;
		write_RAM(j, RAM_out);
		OUTPORT = read_RAM(j);
	}
}

int read_ROM(int* mem_add){
	int val = *mem_add;
	return val;
}
int read_RAM(int* mem_add){
	int val = *mem_add;
	return val;
}
void write_RAM(int* mem_add, int input){
	*mem_add = input;
}