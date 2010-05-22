#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char** life_field;
char** life_field2;


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

int main(){
	init_life();
	while(1){
		show_life();
		recount_life(life_field,life_field2);
		char** chng;
		chng=life_field;
		life_field=life_field2;
		life_field2=chng;
		sleep(1);
	}
	return 0;
}
