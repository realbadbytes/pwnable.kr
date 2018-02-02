#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void callme(){
        system("/bin/sh");
}

void clear_newlines(){
        int c;
        do{
                c = getchar();
        }while (c != '\n' && c != EOF);
}

int g_canary;
int check_canary(int canary){
        int result = canary ^ g_canary;
        int canary_after = canary;
        int canary_before = g_canary;
        printf("canary before using buffer : %d\n", canary_before);
        printf("canary after using buffer : %d\n\n", canary_after);
        if(result != 0){
                printf("what the f...??? how did you fucked this buffer????\n");
        }
        else{
                printf("I told you so. its trivially easy to prevent BOF :)\n");
                printf("therefore as you can see, it is easy to make secure software\n");
        }
        return result;
}

int size;
char* buffer;
int main(){

        printf("- BOF(buffer overflow) is very easy to prevent. here is how to.\n\n");
        sleep(1);
        printf("   1. allocate the buffer size only as you need it\n");
        printf("   2. know your buffer size and limit the input length\n\n");

        printf("- simple right?. let me show you.\n\n");
        sleep(1);

        printf("- whats the maximum length of your buffer?(byte) : ");
        scanf("%d", &size); //looks ok
        clear_newlines(); //dunno what this does

        printf("- give me your random canary number to prove there is no BOF : ");
        scanf("%d", &g_canary); //looks ok
        clear_newlines(); //dunno what this does

        printf("- ok lets allocate a buffer of length %d\n\n", size);
        sleep(1);

	// 0xffb2ba3c
        buffer = alloca( size + 4 );    // 4 is for canary
	// does this return a pointer?
	// alloca
	// void *alloca(size_t size);
	// allocates size bytes of space on the stack frame of the caller
	// space is automatically freed when the function that called alloca() returns
	// alloca returns a pointer to the beginning of allocated space.
	// IF THE ALLOCATION CAUSES STACK OVERFLOW, UNDEFINED BEHAVIOR
	// huehue, alloca can stack overflow given large values, it just moves ESP ...
	// lets try to write into the heap?? maybe a function pointer??
	// 
	
        printf("- now, lets put canary at the end of the buffer and get your data\n");
        printf("- don't worry! fgets() securely limits your input after %d bytes :)\n", size);
        printf("- if canary is not changed, we can prove there is no BOF :)\n");
        printf("$ ");

	// this looks ok
        memcpy(buffer+size, &g_canary, 4);      // canary will detect overflow.
	// this looks ok
        fgets(buffer, size, stdin);             // there is no way you can exploit this.

        printf("\n");
        printf("- now lets check canary to see if there was overflow\n\n");

	// passing dereferenced cast int ptr to buffer+size aka copied g_canary
        check_canary( *((int*)(buffer+size)) );
        return 0;
}



















