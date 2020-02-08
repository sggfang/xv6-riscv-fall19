#include "user/user.h"

int main(int argc,char *argv[]){
	char buff[23][23];
	char temp[512];
	char *pass[23];

	for(int index=0;index<23;index++){
		pass[index]=buff[index];
	}
	int i;
	for(i=1;i<argc;i++){
		strcpy(buff[i-1],argv[i]);
	}
	int n;
	while((n=read(0,temp,sizeof(temp)))>0){
		int pos=argc-1;
		char *c=buff[pos];
		for(char *p=temp;*p;p++){
			if(*p==' '||*p=='\n'){
				*c='\0';
				pos++;
				c=buff[pos];
			}else{
				*c++=*p;
			}
		}
		*c='\0';
		pos++;
		pass[pos]=0;
		
		if(fork()){
			wait();
		}
		else{
			exec(pass[0],pass);
		}
	}
	if(n<0){
		printf("xargs: read error.\n");
		exit();
	}
	exit();
}
		
