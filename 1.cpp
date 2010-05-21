#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void signal_check(int num){
	signal(15, signal_check);
	printf("Signal recieved in process %d in group %d\n", getpid(), getpgrp());
}

int main() {
	signal(15, signal_check);
	if(!fork()&&!fork()&&!fork()){
		setpgrp();
	}	
	printf("%d \n", getpgrp());
	while(1);
	return 0;
}
