#include "cvs_student.h"
#include <string>
#include <cstring>
#include <stdio.h>

void le2be(void* input,void* output,int size){
	char* temp_i,*temp_o;
	for(int i = 0; i < size; i++){
		temp_i = (char*)input+i;
		temp_o =  (char*)(output + size - 1 - i);
		*temp_o = *temp_i;
	}	
}


void cvs_student::set_student(
	uint64_t ID_i,
	char* Name_i,
	char* Department_i,
	uint8_t Age_i){
		
	ID = ID_i;
	memcpy(Name,Name_i,128);
	memcpy(Department,Department_i,32);
	Age = Age_i;
	
}

int cvs_student::get_student_from_stdin(){
	scanf("%d,%[^,],%[^,],%d",&ID,Name,Department,&Age);
	return 0;
}

int cvs_student::get_student_from_file(FILE* fp){
	fscanf(fp,"%d,%[^,],%[^,],%d",&ID,Name,Department,&Age);
	return 0;
}

void cvs_student::show_student_to_stout(){
	std::cout << ID << '\t' << Name << '\t' << Department << '\t'  << (Age+0) << std::endl; 
}

void  cvs_student::convert_le_be(cvs_student& big_stu){
	le2be(&ID,&(big_stu.ID),sizeof(uint64_t));
	memcpy(big_stu.Name,Name,128);
	memcpy(big_stu.Department, Department,32);
	big_stu.Age = Age;
}