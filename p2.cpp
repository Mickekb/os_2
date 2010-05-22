#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv){
    char* in = new char[255];
    while(1)
    {
        fgets(in, 255, stdin);
	if(strlen(in))
	        printf("P2 get: %s", in);
    }
    return 0;
}
