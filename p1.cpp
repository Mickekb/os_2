#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    while(1){
	fputs("P1 -> stdout \n", stdout);
	fputs("P1 -> stderr \n", stderr);
	fflush(stdout);
	fflush(stderr);
	sleep(1);
    }
    return 0;
}
