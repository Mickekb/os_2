#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//string format: p1 > p2 > p3
int pipes[2][2];
int proc1, proc2, proc3;

void close_pipe(int num){
	close(pipes[num][0]);
        close(pipes[num][1]);
}

int main(){
	char* my_input = new char[255];
	char* p1;
	char* p2;
	char* p3;
	while(1){
		fgets(my_input, 255, stdin);
		if(my_input[0]=='e'&&my_input[1]=='x'&&my_input[2]=='i'&&my_input[3]=='t'){
			return 0;
		}
		int str_len=strlen(my_input);
		bool err=false;
		int i=0;

		while(my_input[i]==' '&&i<str_len){
			++i;
		}
		if(i==str_len){
			err=true;
		}
		else{
			p1=my_input+i;
		}

		if(!err){
			while(my_input[i]!=' '&&i<str_len){
				++i;
			}
			if(i==str_len){
				err=true;
			}
			else{
				my_input[i]=0;
				++i;
			}
		}
		if(!err){
			while(my_input[i]==' '&&i<str_len){
				++i;
			}
			if(i==str_len){
				err=true;
			}
			else{
				if(my_input[i]!='>'){
					err=true;
				}
				else{
					++i;
				}
			}
		}

		if(!err){
			while(my_input[i]==' '&&i<str_len){
				++i;
			}
			if(i==str_len){
				err=true;
			}
			else{
				p2 = my_input + i;
			}
		}

		if(!err){
			while(my_input[i]!=' '&&i<str_len){
				++i;
			}
			if(i==str_len){
				err=true;
			}
			else{
				my_input[i]=0;
				++i;
			}
		}

		if(!err){
			while(my_input[i]==' '&&i<str_len){
				++i;
			}
			if(i==str_len){
				err=true;
			}
			else{
				if(my_input[i]!='>'){
					err=true;
				}
				else{
					++i;
				}
			}
		}
		
		if(!err){
			while(my_input[i]==' '&&i<str_len){
				++i;
			}
			if(i==str_len){
				err=true;
			}
			else{
				p3=my_input+i;
			}
		}
		
		if(!err){
			while(my_input[i]!=' '&&i<str_len){
				++i;
			}
			my_input[i]=0;
			++i;			
		}
		
		if(!err){
			while(my_input[i]==' '&&i<str_len){
				++i;
			}
			if(i<str_len){
				err=true;
			}
		}
		
		if(!err){
			printf("Correct input; p1: %s, p2: %s, p3: %s \n", p1, p2, p3);
			//set pipes
			if (pipe(pipes[0])) {
			    printf("Cant open first pipe");
			    continue;
			}

			if (pipe(pipes[1])) {
			    printf("Cant open second pipe");
			    close_pipe(0);
			    continue;
			}
			proc1 = fork();
			if(proc1==0){
				if (dup2(pipes[0][1], STDOUT_FILENO)==-1){
					printf("Cant dup p1");
					return 0;
				}
				if (dup2(pipes[1][1], STDERR_FILENO)==-1){
					printf("Cant dup p1");
					return 0;
				}
				close_pipe(1);
				execlp(p1,p1,NULL);
				exit(0);
			}
			else if(proc1==-1){
				printf("Cant fork");
				close_pipe(0);
				close_pipe(1);
				continue;
			}	

			proc2 = fork();
			if(!proc2){
				if (dup2(pipes[1][0], STDIN_FILENO)==-1){
					printf("Cant dup p2");
					return 0;
				}
				close_pipe(1);
				execlp(p2,p2,NULL);
				return 0;
			}
			else if(proc2==-1){
				printf("Cant fork 2");
				close_pipe(0);
				close_pipe(1);
				continue;
			}

			proc3 = fork();
			if(!proc3){
				if (dup2(pipes[0][0], STDIN_FILENO)==-1){
					printf("Cant dup p3");
					return 0;
				}
				close_pipe(1);
				execlp(p3,p3,NULL);
				return 0;
			}
			else if(proc3==-1){
				printf("Cant fork 3");
				close_pipe(0);
				close_pipe(1);
				continue;
			}	
		}
		else{
			printf("Wrong format. Right is: p1 > p2 > p3\n");
		}
		int status;
		wait(&status);
		wait(&status);
		wait(&status);
		printf("Success!\n");
	}	
	return 0;
}
