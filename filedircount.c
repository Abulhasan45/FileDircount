#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int dircount,filecount;

void filedircount(char *directory){
	DIR *directory_ptr = NULL;
	struct dirent *direntp;
	char *newdir;

	if(!directory){
	printf("No directory specified ");
	exit(0);
	}
	if( (directory_ptr = opendir(directory)) == NULL){
	printf("Invalid directory ");
	exit(0);
	}
	
	while((direntp =readdir(directory_ptr)))
	{	
		if(strcmp(direntp->d_name,".")== 0 || strcmp(direntp->d_name, "..")==0)
		continue;	
		switch (direntp->d_type)
		{
			case DT_REG:
				filecount++;
				break;

			case DT_DIR:
				newdir=malloc(strlen(directory)+strlen(direntp->d_name)+2);
				if(newdir == NULL){
				printf("The memory is not allocated so exiting");
				exit(0);}
				sprintf(newdir,"%s/%s",directory,direntp->d_name);
				filedircount(newdir);
				free(newdir);
				dircount++;
				break;
		}	

	}
	closedir(directory_ptr);
}
int main(int argc,char *argv[]){
	printf("Directory path : %s\n",argv[1]);
	filedircount(argv[1]);
	printf("Filecount : %d\nDirectorycount : %d\n",filecount,dircount);
	return 0;	
}

