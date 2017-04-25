#include "cvs_student.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

int main(int argn, char* argv[]){
	
	if(argn <= 1){
		perror("input parameter less than 1\n");
		return 1;
	}
	
	std::cout << argv[1] << std::endl;
	int stat;
	int num = 8;
	int filenum = 4;
	int chd[2][filenum];
	
	for (int i = 0; i < filenum;i++) {
		pipe(chd[i]);
	}
	
	for (int i = 1; i <= filenum;i++) {
		int pid = fork();
		// filenum son threads
		if(pid == 0) {
			cvs_student* student_list = new cvs_student[50];
			std::cout << i << std::endl;
			char singlebuff[1];
			int inline_count = 0;
			int count = 0;
			char buf[1024];
			while(1){
				read(chd[i-1][0],singlebuff,sizeof(char));
				buf[inline_count] = singlebuff[0];
				inline_count ++;
				if(singlebuff[0] == '\n') {
					buf[inline_count] = '\0';
					if(strcmp(buf,"all finish\n")==0){
						break;
					}
					student_list[count].get_student_from_string(buf);
					//student_list[count].show_student_to_stout();
					count ++;
					inline_count = 0;
				}
			}
			char tmp[2]; tmp[0] = (i+'0');tmp[1]='\0';
			std::string finame= "./bin_line" + std::string(tmp);
			//std::cout << finame << std::endl;
			int fd_mm = open(finame.c_str(),O_WRONLY|O_CREAT|O_TRUNC, 0600);
			write(fd_mm, student_list, sizeof(cvs_student)*count );
			close(fd_mm);
			exit(0);
		}
		// father thread
		if(i == filenum){
			i++;
			std::cout << i << std::endl;
		/* 	for (int ind = 0; ind< filenum;ind++){
				close(chd[ind][0]);
			} */
			std::string line;
			int count = 0;
			int inline_count = 0;
			char singlebuff[1];
			char buf[1024];
			int input_file;			
			input_file = open(argv[1],O_RDONLY);
			while(read(input_file,singlebuff,sizeof(char))){
				buf[inline_count] = singlebuff[0];
				inline_count ++;
				if(singlebuff[0] == '\n') {
					//std::cout << "f "<< buf;
					write(chd[(count)%4][1],buf,inline_count);
					count ++;
					inline_count = 0;
				}
			}
			for (int ind = 0; ind < filenum;ind++){
				write(chd[ind][1],"all finish\n",12);
			}
			sleep(3);
			int fd_mm[4];
			cvs_student* student_list[4];
			cvs_student* student_list_all = new cvs_student[50];
			for(int ind = 0; ind < filenum;ind++){
				char tmp[2]; tmp[0] = (ind+'1');tmp[1]='\0';
				std::string finame= "./bin_line" + std::string(tmp);
				//std::cout << finame << std::endl;
				fd_mm[ind] = open(finame.c_str(), O_RDONLY);
				student_list[ind] = (cvs_student*)mmap(NULL,sizeof(cvs_student)*100,PROT_READ,MAP_SHARED,fd_mm[ind],0);
				
			}
			for (int ind = 0; ind < count;ind++){
				student_list_all[ind] = student_list[ind%4][ind/4];
				//student_list_all[ind].show_student_to_stout();
			}
			
			for(int ind = 0; ind < filenum;ind++){
				close(fd_mm[ind]);		
			}
			int fd_out = open("../outbin.bin",O_WRONLY|O_CREAT|O_TRUNC, 0600);
			write(fd_out, student_list_all, sizeof(cvs_student)*count );
			close(fd_out);
		}
		
		
	}
	
	
	return 0;
}