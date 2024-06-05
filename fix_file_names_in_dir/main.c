#include "Includes/preprocessor.h"
#define TMP_FILE_PATH="./tmp",
		*findcmd[]={"find",".",NULL},
		*removecmd[]={"rm","-rf",TMP_FILE_PATH,NULL},
		*mvcmd[]={"mv",NULL,NULL,NULL};
int fd=-1;
void executeFileCmdToTmpFile(void){
	if((fd=open(tmpFilePath,O_CREAT|O_RDWR|O_TRUNC,0777))<0){

		perror("ficheiro n criado!!!!\n");
		exit(-1);
	}
	int pid= fork();
	switch(pid){
	case -1:
		perror("ERROR FORK!!!!\n");
		close(fd);
		exit(-1);
	case 0:
		dup2(fd,1);
		execvp(findcmd[0],findcmd);
		perror("ERRO EXECVP\n");
		exit(-1);
	default:
		wait(NULL);
		close(fd);
		break;
	}

}
void fixFileString(char* string){

	for(int i=0;string[i];i++){

		if(isspace(string[i])){
			string[i]='_';
		}
	}


}
void mvFiles(void){
	FILE* fp=NULL;
	if(!(fp= fopen(tmpFilePath,"r"))){

		perror("filepath invalid in file moving!!!\n");
		exit(-1);
	}
	char buffsrc[1024]={0};
	char buffdst[1024]={0};
	while(fgets(buffsrc,1024,fp)){
		buffsrc[strlen(buffsrc)]=0;
		strcpy(buffdst,buffsrc);
	int pid=fork();	
	switch(pid){
	case -1:
		perror("ERROR FORK!!!!\n");
		exit(-1);
	case 0:
		mvcmd[1]=buffsrc;
		fixFileString(buffdst);
		mvcmd[2]=buffdst;
		execvp(mvcmd[0],mvcmd);
		perror("ERRO EXECVP\n");
		exit(-1);
	default:
		wait(NULL);
		break;
	}
		
		memset(buffsrc,0,1024);
		memset(buffdst,0,1024);
	
	}
	fclose(fp);


}
void removeTmpFile(void){

	int pid= fork();
	switch(pid){
	case -1:
		perror("ERROR FORK!!!!\n");
		exit(-1);
	case 0:
		execvp(removecmd[0],removecmd);
		perror("ERRO EXECVP\n");
		exit(-1);
	default:
		wait(NULL);
		break;
	}


}
int main(int argc, char ** argv){
	
	executeFileCmdToTmpFile();

	

	return 0;
}
