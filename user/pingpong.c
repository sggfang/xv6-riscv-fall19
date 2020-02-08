#include "user/user.h"

int main(int argc,char *argv[]){
	int parent_fd[2];
	int child_fd[2];
	pipe(parent_fd);
	pipe(child_fd);
	char buffer[100];

	if(fork()!=0){
		write(parent_fd[1],"ping",4);
		read(child_fd[0],buffer,4);
		printf("%d: received %s\n",getpid(),buffer);
	}else{
		read(parent_fd[0],buffer,4);
		printf("%d: received %s\n",getpid(),buffer);
		write(child_fd[1],"pong",4);
	}
	exit();
}
