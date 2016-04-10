/*	Program Title: 	PUTOK Programming Language Lexical Analyzer
 *					Group Project
 *	Group members:	Calvadores, Angelica
                    Enrique, Mariella
                    Loto, Ramzel Renz L.
                    Roman, Rose Anne L.
 *	Course/Sec/Sch:	BSCS 2-1N Polytechnic University of the Philippines - Mabini Campus
 *	Date Written: 	February 1, 2016
 *	Prepared for: 	Prof. Elias Austria
 *					COSC 3053 - Principles of Programming Languages
 *======================================================================================================
 *
 * This program is a Lexical Analyzer based on our proposed programming language "PUTOK".
 *
 */

#include<stdio.h>
#include<string.h>
#include<conio.h>
#define FILENAME_OPERATORS "operators.txt"
#define FILENAME_KEYWORDS "keywords.txt"
#define FILENAME_RESERVEDWORDS "reserved_words.txt"
#define COUNT_OPERATORS 5
#define COUNT_KEYWORDS 5
#define COUNT_RESERVEDWORDS 5
#define MAX_OPERATOR_SIZE 2
#define MAX_KEYWORD_SIZE 8
#define MAX_RESERVEDWORD_SIZE 8

//Tokens
char operators[COUNT_OPERATORS][MAX_OPERATOR_SIZE];
char keywords[COUNT_KEYWORDS][MAX_KEYWORD_SIZE];
char reserved_words[COUNT_RESERVEDWORDS][MAX_RESERVEDWORD_SIZE];
int ctr = 0;

void loadTokens(){
		
		char token[MAX_KEYWORD_SIZE];
		ctr = 0;
		
		FILE *fOperator;
		FILE *fKeyword;
		FILE *fRsrvdWrd;
		
		fOperator = fopen(FILENAME_OPERATORS, "r");
		if(fOperator != NULL){
			ctr = 0;
			while(fgets(token, MAX_OPERATOR_SIZE, fOperator)){
				strcpy(operators[ctr], token);
				ctr++;
			}
		}
		else{
			printf("\nError loading tokens! Operators file not found.\n");
		}
		
		fKeyword = fopen(FILENAME_KEYWORDS, "r");
		if(fKeyword != NULL){
			ctr = 0;
			while(fgets(token, MAX_KEYWORD_SIZE, fKeyword)){
				strcpy(keywords[ctr], token);
				ctr++;
			}
		}
		else{
			printf("\nError loading tokens! Keywords file not found.\n");
		}
		
		/*fRsrvdWrd = fopen(FILENAME_RESERVEDWORDS, "r");
		if(fRsrvdWrd != NULL){
			ctr = 0;
			while(fgets(token, MAX_RESERVEDWORD_SIZE, fRsrvdWrd)){
				strcpy(reserved_words[ctr], token);
				ctr++;
			}
		}
		else{
			printf("\nError loading tokens! Reserved words file not found.\n");
		}*/
		
		fclose(fRsrvdWrd);
		fclose(fKeyword);
		fclose(fOperator);
		
		return;
}

FILE *input_file;
FILE *output_file;
char filename[100];
int getFile(){
		
	//Get file name
	printf("Enter filename: ");
	scanf("%s", filename);

	//Open input and output files
	input_file = fopen(filename, "r");
	output_file = fopen("output.txt", "w");
	fprintf(output_file,"TOKEN\t\tLEXEME\t\tDESCRIPTION\n\n");

	//Terminate if file not found
	int fileFound = 1;
	if(input_file){
		fileFound = 0;
	}
	else{
		printf("\nFile not found!\n");
		fileFound = 1;
	}
	
	fclose(input_file);
	fclose(output_file);
	
	return fileFound;
}

void isIden(char ch[]){
	
	return;
}

void isOp(char ch[]){
	
	for(ctr = 0; ctr < 10; ctr++){
		if((strncmp(ch, operators[ctr], 1) == 0) && (strncmp(ch, "\n", 1) != 0)){
			output_file = fopen("output.txt", "a");
			fprintf(output_file,"Operator\t%c\t\tOperator\n", ch[0]);
			fclose(output_file);
        }
	}
	
	return;
}

void isKeyword(char ch[]){
	
	for(ctr = 0; ctr < COUNT_KEYWORDS; ctr++){
		
	}
	
	return;
}

void isRsrvdWrd(char ch[]){
	
	for(ctr = 0; ctr < COUNT_RESERVEDWORDS; ctr++){
		
	}
	
	return;
}

void scanner(){
	
	char ch[1];
	input_file = fopen(filename, "r");
	while ((ch[0] = fgetc(input_file)) != EOF){
		isIden(ch);
		isOp(ch);
		isKeyword(ch);
		isRsrvdWrd(ch);
	}
	
	return;
}

/*===========MAIN FUNCTION==========*/
int main(void){

	loadTokens();
	int fileFound = getFile();
	if(fileFound == 0){
		scanner();	
	}
	
	return 0;
}
