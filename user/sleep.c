
#include "user/user.h"

void sleep1(char *t){
	int time=atoi(t);
	if(sleep(time)<0){
		printf("slee time error.\n");
		exit();
	}	
	exit();
}

int main(int argc,char *argv[]){
	//int index;
	if(argc!=2){
		printf("argument fault!\n");
		exit();
	}
	sleep1(argv[1]);
	exit();
}

