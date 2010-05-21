#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void signal_check(int num){
	signal(SIGINT, signal_check);
	printf("Signal recieved\n");
}

int main() {
	signal(SIGINT, signal_check);
	if (fork()) {
		while(1);
	} 
	else{
		setpgid (getpid(), 0);
		while(1);
	}
	return 0;
}
