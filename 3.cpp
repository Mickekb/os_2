#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sched.h>

char** life_field;
char** life_field2;
char* life_state = new char[101];
int S, client;

void str2_to_str(){
	int k=0;
	for(int i=0; i<10; ++i){
		for(int j=0;j<10;++j){
			life_state[k]=life_field[i][j];
			++k;
		}
	}
	life_state[100]=0;
}

void recount_life(char** from, char** to){
	for(int i=0;i<10;++i){
		for(int j=0;j<10;++j){
			int count_neight=0;
			if(i!=0){
				if(j!=0 && from[i-1][j-1]=='1') ++count_neight;
				if(j!=9 && from[i-1][j+1]=='1') ++count_neight;
				if(from[i-1][j]=='1') ++count_neight;
			}
			if(i!=9){
				if(j!=0 && from[i+1][j-1]=='1') ++count_neight;
				if(j!=9 && from[i+1][j+1]=='1') ++count_neight;
				if(from[i+1][j]=='1') ++count_neight;
			}
			if(j!=0 && from[i][j-1]=='1') ++count_neight;
			if(j!=9 && from[i][j+1]=='1') ++count_neight;
			
			if(from[i][j]=='0'&&count_neight==3){
				to[i][j]='1';
			}
			else if(from[i][j]=='1'&&(count_neight==2||count_neight==3)){
				to[i][j]='1';
			}
			else{
				to[i][j]='0';
			}
			//printf("%d ", count_neight);
		}
		//printf("\n");
	}
	str2_to_str();
}

void init_life(){
	life_field = new char*[10];
	life_field2 = new char*[10];
	for(int i=0;i<10;++i){
		life_field[i]=new char[11];
		life_field2[i]=new char[11];
	}
	strcpy(life_field[0], "0001000000");
	strcpy(life_field[1], "0001000000");
	strcpy(life_field[2], "0001000000");
	strcpy(life_field[3], "0000000000");
	strcpy(life_field[4], "0000100000");
	strcpy(life_field[5], "0000010000");
	strcpy(life_field[6], "0001110000");
	strcpy(life_field[7], "0000000000");
	strcpy(life_field[8], "0000000000");
	strcpy(life_field[9], "0000000000");
	str2_to_str();
}

void show_life(){
	printf("LIFE:\n");
	for(int i=0; i<10; ++i){
		for(int j=0;j<10;++j){
			printf("%c ",life_field[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}



int life_do(void* arg){
	while(1){
		//show_life();
		recount_life(life_field,life_field2);
		//printf("%s \n",life_state);
		//fflush(stdout);
		char** chng;
		chng=life_field;
		life_field=life_field2;
		life_field2=chng;
		sleep(1);
	}
	return 0;
}

int client_do(void* arg){
	int my_client=client;
	while(1){
		int request;
		if(!read(my_client, &request, sizeof(int))) {
			close(my_client);
			perror("Cant read socket");
			return -1;
		}
		printf("%d\n", request);
		int pid=fork();
		//if(request!=1)
	    	//	continue;
		if(pid==0){
			if (!write(my_client, life_state, 101*sizeof(char))){
				close(my_client);
				perror("Cant write socket");
		    		return -1;
			}
			close(S);
			close(client);
			return 0;
		}
	}
	return 0;
}

int main(){
	init_life();
	
	void* child_stack = (void*) malloc(65536);
   	if(clone(life_do, child_stack + 65535, CLONE_VM, NULL) == -1) {
       		perror("Cant clone life_do");
        	return -1;
	}	

	S = socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in SA;
	SA.sin_family=AF_INET;
	SA.sin_port=htons(3136);
	SA.sin_addr.s_addr=htonl(INADDR_ANY);

	sockaddr_in SA_client;

	if(S < 0){
		perror("Cant create socket");
		return -1;
	}
	if(bind(S, (sockaddr*)&SA, sizeof(SA)) < 0) {
		perror("Cant bind socket");
		return -1;
	}
	if (listen(S, 1) < 0) {
		perror("Cant listen socket");
		return -1;
	}

	int length=sizeof(SA_client);
	while(1){
		client = accept(S, (sockaddr*)&SA_client,(socklen_t*)&length);
		if(client < 0) {
			perror("Cant get client");
			return -1;
		}
		
		void* child_stack = (void*) malloc(65536);
		if(clone(client_do, child_stack + 65535, CLONE_VM, NULL) == -1) {
	       		perror("Cant clone client");
			return -1;
		}
	}
	close(S);
	return 0;
}
