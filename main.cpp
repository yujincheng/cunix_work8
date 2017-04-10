#include "cvs_student.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

int main(int argn, char* argv[]){
	int stat;
	int num = 8;
	int filenum = 5;
	// 初始化数组
	cvs_student* student_list, *student_list_out;
	student_list = new cvs_student[num*filenum];
	student_list_out = new cvs_student[num*filenum];
	
	
	for (int i = 1; i <= filenum;i++) {
		int pid = fork();
		if(pid == 0) {
			FILE* fp;
			std::string file_name = std::string("../test")+char('0'+i)+std::string(".txt");
			std::cout << file_name << std::endl;
			fp = fopen( file_name.c_str(),"r");
			for(int stu_i = 0; stu_i <  num; stu_i ++){
				student_list[stu_i].get_student_from_file(fp);		
			}
			fclose(fp);
			// 写入文件
			std::string file_name_out = std::string("../test")+char('0'+i)+std::string(".bin");
			int outf = open(file_name_out.c_str(),O_WRONLY|O_CREAT|O_TRUNC, 0600);
			write(outf, student_list, sizeof(cvs_student)*num*filenum);
			close(outf);
			exit(0);		
		}
	}
	
	sleep(3);
	wait();
	
	// 读取文件
	
	for(int ifile = 1; ifile <= filenum;ifile++) {
		std::string file_name = std::string("../test")+char('0'+ifile)+std::string(".bin");
		std::cout << file_name << std::endl;
		int inf = open(file_name.c_str(), O_RDONLY, 0);
		read(inf, ((void*)student_list)+sizeof(cvs_student)*num*(ifile-1), sizeof(cvs_student)*num);
		close(inf);		
	}
	
	// 转化成小端并输出
	for(int stu_i = 0; stu_i <  num*filenum; stu_i ++){
		student_list[stu_i].show_student_to_stout();
	}
	
	return 0;
}