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
#include<ctype.h>
#include<conio.h>
#define FILENAME_OUTPUT "output.putok"
#define FILENAME_OPERATORS "operators.txt"
#define FILENAME_KEYWORDS "keywords.txt"
#define FILENAME_RESERVEDWORDS "reserved_words.txt"
#define COUNT_OPERATORS 16
#define COUNT_KEYWORDS 5
#define COUNT_RESERVEDWORDS 6
#define MAX_OPERATOR_SIZE 4
#define MAX_KEYWORD_SIZE 8
#define MAX_RESERVEDWORD_SIZE 8

//Functions
void loadTokens(void);
int getFile(void);
void scanner(void);
void isRsrvdWrd(char []);
void isKeyword(char []);
void isOp(char []);
void isIden(char []);

//Tokens
char operators[COUNT_OPERATORS][MAX_OPERATOR_SIZE];
char keywords[COUNT_KEYWORDS][MAX_KEYWORD_SIZE];
char reserved_words[COUNT_RESERVEDWORDS][MAX_RESERVEDWORD_SIZE];

int ctr, ctr1;

/*===========MAIN FUNCTION==========*/
int main(void){

	loadTokens();
	int fileFound = getFile();
	if(fileFound == 0){
		scanner();	
	}
	
	return 0;
}

void loadTokens(){
		
		char token[MAX_KEYWORD_SIZE];
		ctr = 0;
		
		FILE *fOperator;
		FILE *fKeyword;
		FILE *fRsrvdWrd;
		
		fRsrvdWrd = fopen(FILENAME_RESERVEDWORDS, "r");
		if(fRsrvdWrd != NULL){
			ctr = 0;
			while(fgets(token, MAX_RESERVEDWORD_SIZE, fRsrvdWrd)){
				strcpy(reserved_words[ctr], token);
				ctr++;
			}
			for(ctr = 0; ctr < COUNT_RESERVEDWORDS; ctr++){
				reserved_words[ctr][strlen(reserved_words[ctr])-1]= '\0';
			}
		}
		else{
			printf("\nError loading tokens! Reserved words file not found.\n");
		}
		
		fOperator = fopen(FILENAME_OPERATORS, "r");
		if(fOperator != NULL){
			ctr = 0;
			while(fgets(token, MAX_OPERATOR_SIZE, fOperator)){
				strcpy(operators[ctr], token);
				ctr++;
			}
			for(ctr = 0; ctr < COUNT_OPERATORS; ctr++){
				operators[ctr][strlen(operators[ctr])-1]= '\0';
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
			for(ctr = 0; ctr < COUNT_KEYWORDS; ctr++){
				keywords[ctr][strlen(keywords[ctr])-1]= '\0';
			}
		}
		else{
			printf("\nError loading tokens! Keywords file not found.\n");
		}
		
		fclose(fKeyword);
		fclose(fOperator);
		fclose(fRsrvdWrd);
		
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
	output_file = fopen(FILENAME_OUTPUT, "w");
	fprintf(output_file,"TOKEN\t\tLEXEME\t\tDESCRIPTION\n\n");

	//Terminate if file not found
	int fileFound = 1;
	if(input_file){
		fileFound = 0;
	}
	else{
		printf("\nFile not found!\n");
		fileFound = 1;
		getch();
	}
	
	fclose(input_file);
	fclose(output_file);
	
	return fileFound;
}

void scanner(){
	
	char line[100];
	input_file = fopen(filename, "r");
	while (fgets(line, 100, input_file)){
		isKeyword(line);
		isRsrvdWrd(line);
		isIden(line);
		isOp(line);
	}
	
	return;
}

int match(char [], char []);

void isIden(char line[]){
	
	for(ctr = 0; ctr < strlen(line); ctr++){
		if(line[ctr] == '.'){
			output_file = fopen(FILENAME_OUTPUT, "a");
			fprintf(output_file,"Identifier\t", line[ctr]);

			do{
				ctr++;
				if(line[ctr] == '.'){
					break;
				}
				else{
					fprintf(output_file,"%c", line[ctr]);
				}
			}while(line[ctr] != '.');
			fprintf(output_file,"\n");
			fclose(output_file);
		}
	}
	
	return;
}

void isOp(char line[]){
	
	int matched2;
	
	for(ctr = 0; ctr < (COUNT_OPERATORS); ctr++){
		matched2 = match(line, operators[ctr]);	
		
		if((ispunct(operators[ctr][0])) && (matched2 != -1)){
			output_file = fopen(FILENAME_OUTPUT, "a");
			fprintf(output_file,"Operator\t%s\t\tOperator\n", operators[ctr]);
			fclose(output_file);
			break;
		}
	}
	
	return;
}

void isKeyword(char line[]){
	
	int matched1;
	
	for(ctr = 0; ctr < (COUNT_KEYWORDS*2); ctr++){
		matched1 = match(line, keywords[ctr]);	
		if((isalpha(keywords[ctr][0])) && (matched1 != -1)){
			output_file = fopen(FILENAME_OUTPUT, "a");
			fprintf(output_file,"Keyword\t\t%s\t\tKeyword\n", keywords[ctr]);
			fclose(output_file);
		}
	}
	
	return;
}

void isRsrvdWrd(char line[]){
	
	int matched;
	
	for(ctr = 0; ctr < (COUNT_RESERVEDWORDS*2); ctr++){
		matched = match(line, reserved_words[ctr]);	
		if((isalpha(reserved_words[ctr][0])) && (matched != -1)){
			output_file = fopen(FILENAME_OUTPUT, "a");
			fprintf(output_file,"Reserved word\t%s\t\tReserved word\n", reserved_words[ctr]);
			fclose(output_file);
		}
	}
	
	return;
}

int match(char text[], char pattern[]) {
  int c, d, e, text_length, pattern_length, position = -1;
 
  text_length    = strlen(text);
  pattern_length = strlen(pattern);
 
  if (pattern_length > text_length) {
    return -1;
  }
 
  for (c = 0; c <= text_length - pattern_length; c++) {
    position = e = c;
 
    for (d = 0; d < pattern_length; d++) {
      if (pattern[d] == text[e]) {
        e++;
      }
      else {
        break;
      }
    }
    if (d == pattern_length) {
      return position;
    }
  }
 
  return -1;
}
