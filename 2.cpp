#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//string format: p1 > p2 > p3

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
		}
		else{
			printf("Wrong format. Right is: p1 > p2 > p3\n");
		}

	}	
	return 0;
}
