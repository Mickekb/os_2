#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv){
    char* in = new char[255];
    while(1)
    {
        fgets(in, 255, stderr);
	if(strlen(in))
	        printf("P3 get: %s", in);
    }
    return 0;
}
