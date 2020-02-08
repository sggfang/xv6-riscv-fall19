#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "kernel/fs.h"
int matchstar(int,char *re,char *text);
int matchhere(char *re, char *text)
{
  if(re[0] == '\0')
    return 1;
  if(re[1] == '*')
    return matchstar(re[0], re+2, text);
  if(re[0] == '$' && re[1] == '\0')
    return *text == '\0';
  if(*text!='\0' && (re[0]=='.' || re[0]==*text))
    return matchhere(re+1, text+1);
  return 0;
}

// matchstar: search for c*re at beginning of text
int matchstar(int c, char *re, char *text)
{
  do{  // a * matches zero or more instances
    if(matchhere(re, text))
      return 1;
  }while(*text!='\0' && (*text++==c || c=='.'));
  return 0;
}
char* fmt(char *addr){
	char *p;
	//char *temp;
	//temp=name;
	static char buff[DIRSIZ+1];
	//char *temp;
	

	p=addr+strlen(addr);
	for(;(*p)!='/'&&p>=addr;p--){
	}
	p++;
	if(strlen(p)>=DIRSIZ){
		//printf("%s\n",p);
		return p;
	}
	memmove(buff,p,strlen(p));
	memset(buff+strlen(p),' ',DIRSIZ-strlen(p));
	//printf("%s\n",buff);
	return buff;
	//temp=buff;
}
int match(char addr[],char name[]){
	printf("-----%s\n",addr);
	if(name[0]=='^'){
		return matchhere(name+1,addr);
	}
	//do{
		if(matchhere(name,addr)){
			return 1;
		}
	//}while(*addr++ !='\0');
	return 0;
}

void find(char addr[],char name[]){
	int fd;
	char buff[512];
	char *p;
	struct dirent de;
	struct stat st;

	if((fd=open(addr,0))<0){
		fprintf(2,"find:cannot find %s\n",addr);
		return;	
	}
	if(fstat(fd,&st)<0){
		fprintf(2,"ls:cannot stat $s\n",addr);
		close(fd);
		return;
	}
	switch(st.type){
		case T_FILE:
			if(match(fmt(addr),name)){
				printf("%s\n",addr);
			}
			break;
		case T_DIR:
			if(strlen(addr)+DIRSIZ+2>sizeof(buff)){
				printf("find:path too long.\n");
		 		break;
			}
			strcpy(buff,addr);
			p=buff+strlen(buff);
			*p++='/';
			//p++;
			while(read(fd,&de,sizeof(de))==sizeof(de)){
				if(de.inum==0){
					continue;
				}
				memmove(p,de.name,DIRSIZ);
				p[DIRSIZ]=0;
				if(stat(buff,&st)<0){
					printf("find: cannot stat %s\n",buff);
					continue;
				}
				if(strlen(de.name)==1&&de.name[0]=='.'){
					continue;
				}
				if(strlen(de.name)==2&&de.name[0]=='.'&&de.name[1]=='.'){
					continue;
				}
				find(buff,name);
			}
			break;
	}
	close(fd);
}

int main(int argc,char *argv[]){
	
	if(argc<3){
		printf("Need two parameters.\n");
		exit();
	}
	find(argv[1],argv[2]);
	exit();
}
