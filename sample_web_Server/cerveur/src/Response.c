#include "E:\downloads_29_10_24\sample_web_Server\cerveur\include\Response.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * render_static_file(char * fileName) { //function to render HTML file
	FILE* file = fopen(fileName, "r"); //open the file name passed as parameter in read mode

	if (file == NULL) {
		return NULL;
	}else {
		printf("%s does exist \n", fileName);
	}

	//below 3 lines is to calc the file size
	fseek(file, 0, SEEK_END);//move pointer to the ned of the file
	long fsize = ftell(file);//assign current pointers value to fsize var
	fseek(file, 0, SEEK_SET);//reset pointer

	char* temp = malloc(sizeof(char) * (fsize+1)); //creating a buffer to store the contents of the file(recipe.txt)
	char ch; //var to store each character from the file
	int i = 0;
	while((ch = fgetc(file)) != EOF) {//traverse the loop until the end of file
		temp[i] = ch; //each character is stored in the temp buffer
		i++;
	}
	fclose(file);
	return temp;//return the buffer
}
