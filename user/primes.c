#include "user/user.h"

void flash(int first){
	int i;
	while(read(0,&i,sizeof(i))){
		if(i%first!=0){
			write(1,&i,sizeof(i));
		}
	}
}

void ini(){
	
	for(int index=2;index<=35;index++){
		write(1,&index,sizeof(index));
	}
}

void receive(){
	//printf("prime %d\n",arr[0]);
	int index;
	int p[2];
	
	//int temp[34];
	
	if(read(0,&index,sizeof(index))){
		printf("prime %d\n",index);
		pipe(p);
		if(fork()){
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			receive();
		//read(fd,temp,sizeof(int));
		}else{
			close(1);
			dup(p[1]);		
			close(p[0]);
			close(p[1]);
		//write(p[1],temp,sizeof(int));
			flash(index);
		//close(p[1]);
		}
	}

}

int main(int argc,char *argv[]){
	int p[2];
	pipe(p);

	
	if(fork()){
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		receive(p);
	}else{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		ini();
		//close(p[1]);
	}
	exit();

}
