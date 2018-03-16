//2014037756 컴퓨터공학과 구수연

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

int count=0;
char pathbuf[255];

void printDir(struct dirent* dir,char* path){
	DIR* dirptr;
	struct dirent* dir2;
	struct stat buf;
	char newpath[255];

	
	if(count>0){
		sprintf(newpath,"%s/%s",path,dir->d_name);
		if((dirptr = opendir(newpath))==NULL)
			return;
	}

	if(!strcmp(dir->d_name,".") || !strcmp(dir->d_name,"..")){
		closedir(dirptr);
		return;
	}
	
	
	while(dir2 = readdir(dirptr)){
		getcwd(pathbuf,255);
		chdir(newpath);
		stat(dir2->d_name,&buf);
		chdir(pathbuf);
		
		if (S_ISDIR(buf.st_mode)){
			count++;
			printDir(dir2,newpath);
		}
		
	
		if((dir2->d_ino !=0)&&!(!strcmp(dir2->d_name,".") || !strcmp(dir2->d_name,".."))){
			printf("0%o\t%s/%s\n", buf.st_mode&0777, newpath, dir2->d_name);
		}
	}
	
	closedir(dirptr);
}

int main(int argc, char* argv[])
{
	DIR* dirptr;
	struct dirent* dir;
	struct stat buf;
	
	if((dirptr=opendir(argv[1]))==NULL){
			perror("No such a directory\n");
			exit(-1);
	}	
	
		
	while(dir = readdir(dirptr)){
		stat(dir->d_name,&buf);
		
		if (S_ISDIR(buf.st_mode)){
			count++;
			printDir(dir,argv[1]);
		}
		
		if((dir->d_ino !=0)&&!(!strcmp(dir->d_name,".") || !strcmp(dir->d_name,".."))){
			printf("0%o\t%s\n", buf.st_mode&0777, dir->d_name);
		}
	}
		
	closedir(dirptr);
	
	return 0;
}
