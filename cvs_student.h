#include <stdint.h>
#include <iostream>

class cvs_student{
public:	
	uint64_t ID;
	char Name[128];
	char Department[32];
	uint8_t Age;
	void set_student(uint64_t,char*,char*,uint8_t);
	int get_student_from_stdin();
	int get_student_from_string(char* line);
	int get_student_from_file(FILE* file_name);
	void show_student_to_stout();
	void convert_le_be(cvs_student&);
};

void le2be(void* input,void* output,int size);
