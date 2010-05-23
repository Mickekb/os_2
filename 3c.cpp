#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(){
	char* my_input = new char[255];
	char* life_state = new char[100];

	int S = socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in SA;
	SA.sin_family=AF_INET;
	SA.sin_port=htons(3136);
	SA.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	
	if(connect(S,(sockaddr*)&SA,sizeof(SA))<0){
		perror("Cant connect server");
		return -1;
	}

	while(1){
		fgets(my_input, 255, stdin);
		if(my_input[0]=='e'&&my_input[1]=='x'&&my_input[2]=='i'&&my_input[3]=='t'){
			return 0;
		}
		else if(my_input[0]=='g'&&my_input[1]=='e'&&my_input[2]=='t'){
			printf("Get started...\n");
			int request=1;
			if(!send(S, &request, sizeof(int), 0)){
				perror("Cant send server");
				return -1;
			}
			if(!recv(S, life_state, 101*sizeof(char), 0)){
				perror("Cant recive from server");
				return -1;
			}
			int counter=0;
			for(int i=0; i<10; ++i){
				for(int j=0;j<10;++j){
					printf("%c ",life_state[counter]);
					++counter;
				}
				printf("\n");
			}
			printf("\n");
			fflush(stdout);
		}
		else{	
			printf("Wrong command. Right is: get or exit\n");
		}
	}
	return 0;
}
