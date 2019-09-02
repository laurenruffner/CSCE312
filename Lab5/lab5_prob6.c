//File named "lab5_prob6.c"
#include <stdio.h>
int very_fast_function(int i){
	if ( (i*64 +1) > 1024) return i++;
	else return 0;
	// int result;
	// __asm__(
		
	// 	"movl $40, %%ebx\n\t"
	// 	"movl $1, %%eax\n\t"
	// 	"movl $1, %%ecx\n\t"
	// 	"imull %%ecx, %%ebx\n\t"
	// 	"addl %%eax, %%ebx\n\t"
	// 	"movl %%ebx, %%edx\n\t"
	// 	"subl $1024, %%edx\n\t"
	// 	"jg .L0\n\t"
	// 	"movl $0 %%ebx\n\t"
	// 	"jmp DONE\n\t"
	// 	".L0: "
	// 	"addl %%eax %%ebx\n\t"
	// 	"DONE : addl $0, %%ebx" : "=g" (result) : "g" (i));
	// return result;
}

int main(int argc, char *argv[])
{
	int i;
	i=40;
printf("The function value of  i is %d\n", very_fast_function(i) );
	return 0;
}
