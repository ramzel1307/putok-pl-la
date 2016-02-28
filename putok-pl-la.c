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
#define MAX_NAME_SIZE 256

/*===========MAIN FUNCTION==========*/
int main(void){

	//Get file name
	char *filename;
	printf("Enter filename: ");
	scanf("%s", filename);

	//Open input and output files
	FILE *input_file;
	FILE *output_file;
	input_file = fopen(filename, "r");
	output_file = fopen("output.txt", "w");

	//Terminate if file not found
	if(!input_file){
		printf("File not found!\n");
		return 1;
	}
	else{
		printf("Merong putok!\n");
		char str[MAX_NAME_SIZE];

		while(fgets(str, sizeof str, input_file) != NULL){
			lexical(str);
		}
	}
	fclose(input_file);
	fclose(output_file);

	return 0;
}

//Lexical function
//    It accepts the line sent by the main function, reads it per character, then categorizes it by its lexeme and token.
//	  Then it stacks the information to the symbol table for later use.

void lexical(char str[]){

	int i = 0, j;
	int len = strlen(str), idlen;
	int ctr = 0;
	char iden[MAX_NAME_SIZE];
	char *tkn ,*stacktoken;
	char *p;

	while(i < len){
		if(islower(str[i])){
			iden[ctr] = str[i];
			iden[ctr+1] = '\0';
			ctr++;
			i++;
			printf("IDENTIFIER ");

			while(isalpha(str[i]) || isdigit(str[i])){
				iden[ctr] = str[i];
				iden[ctr+1] = '\0';
				ctr++;
				i++;
			}
			i--;

			tkn = "Identifier_";
			char *id = iden;
			stacktoken = (char *)malloc(1 + strlen(tkn) + strlen(id));
			strcpy(stacktoken, tkn);
			strcat(stacktoken, id);

			//Push into symbol table
			push(stacktoken);

			/*while((p = pop()) != NULL){
				printf("%s\n", p);
				free(p);
			}*/

			if(str[i] == '('){
				printf("LPAREN ");
				stacktoken = "Parenthesis_L";
				push(stacktoken);
			}
			else if(str[i] == '+'){
				i++;
				if(str[i] == '+'){
					printf("INCREMENT ");
					stacktoken = "Increment";
					push(stacktoken);
				}
			}
			else if(str[i] == '-'){
				i++;
				if(str[i] == '-'){
					printf("DECREMENT ");
					stacktoken = "Decrement";
					push(stacktoken);
				}
			}

		}
		else if(isdigit(str[i])){
			i++;
			while(isdigit(str[i])){
				i++;
			}
			if(str[i] == '.'){
				i++;
				while(isdigit(str[i])){
					i++;
				}
				printf("decimal ");
				stacktoken = "Constant_Decimal";
				push(stacktoken);
			}
			else{
				printf("integer ");
				stacktoken = "Constant_Integer";
				push(stacktoken);
			}
			i--;
		}
		else if (str[i] == '+'){
			printf("ARITH_OPERATOR ");
			stacktoken = "Arith_Op_+";
			push(stacktoken);
		}
		else if (str[i] == '-'){
			printf("ARITH_OPERATOR ");
			stacktoken = "Arith_Op_-";
			push(stacktoken);
		}
		else if (str[i] == '*'){
			printf("ARITH_OPERATOR ");
			stacktoken = "Arith_Op_*";
			push(stacktoken);
		}
		else if (str[i] == '/'){
			printf("ARITH_OPERATOR ");
			stacktoken = "Arith_Op_/";
			push(stacktoken);
		}
		else if (str[i] == '='){
			i++;
			if(str[i] == '='){
				printf("CONDITIONAL_OPERATOR ");
				stacktoken = "Conditional_Op_==";
				push(stacktoken);
			}
			else{
				printf("ASSIGN_OPERATOR ");
				stacktoken = "Assign_Op";
				push(stacktoken);
			}
		}
		else if(str[i] == '#'){
			printf("Comment ");
			//while(i < len){
			break;
			//}
		}
		else if(str[i] == 'B'){
			i++;
			if(str[i] == 'A'){
				i++;
				if(str[i] == 'R'){
					i++;
					if(str[i] == 'K'){
						printf("BARK ");
						stacktoken = "BARK";
						push(stacktoken);
					}
				}
			}
			else if(str[i] == 'O'){
				i++;
				if(str[i] == 'O'){
					i++;
					if(str[i] == 'L'){
						i++;
						if(str[i] == ' '){
							printf("BOOL ");
							stacktoken = "BOOL";
							push(stacktoken);
						}
					}
				}
			}
		}
		else if(str[i] == 'C'){
			i++;
			if(str[i] == 'H'){
				i++;
				if(str[i] == 'A'){
					i++;
					if(str[i] == 'R'){
						i++;
						if(str[i] == ' '){
							printf("CHAR ");
							stacktoken = "CHAR";
							push(stacktoken);
						}
					}
				}
			}
			else if(str[i] == 'L'){
				i++;
				if(str[i] == 'E'){
					i++;
					if(str[i] == 'A'){
						i++;
						if(str[i] == 'R'){
							printf("CLEAR ");
							stacktoken = "CLEAR";
							push(stacktoken);
						}
					}
				}
			}
		}
		else if(str[i] == 'D'){
			i++;
			if(str[i] == 'E'){
				i++;
				if(str[i] == 'C'){
					i++;
					if(str[i] == ' '){
						printf("DEC ");
						stacktoken = "DEC";
						push(stacktoken);
					}
				}
			}
			else if(str[i] == 'O'){
				printf("DO ");
				stacktoken = "DO";
				push(stacktoken);
			}
		}
		else if(str[i] == 'E'){
			i++;
			if(str[i] == 'N'){
				i++;
				if(str[i] == 'D'){
					printf("END ");
					stacktoken = "END";
					push(stacktoken);
				}
			}
		}
		else if(str[i] == 'F'){
			i++;
			if(str[i] == 'A'){
				i++;
				if(str[i] == 'L'){
					i++;
					if(str[i] == 'S'){
						i++;
						if(str[i] == 'E'){
							printf("FALSE ");
							stacktoken = "FALSE";
							push(stacktoken);
						}
					}
				}
			}
			else if(str[i] == 'E'){
				i++;
				if(str[i] == 'E'){
					i++;
					if(str[i] == 'D'){
						printf("FEED ");
						stacktoken = "FEED";
						push(stacktoken);
					}
				}
			}
			else if(str[i] == 'O'){
				i++;
				if(str[i] == 'R'){
					printf("FOR ");
					stacktoken = "FOR";
					push(stacktoken);
				}
			}
		}
		else if(str[i] == 'I'){
			i++;
			if(str[i] == 'F'){
				printf("IF ");
				stacktoken = "IF";
				push(stacktoken);
			}
			else if(str[i] == 'N'){
				i++;
				if(str[i] == 'T'){
					i++;
					if(str[i] == ' '){
						printf("INT ");
						stacktoken = "INT";
						push(stacktoken);
					}
				}
			}
		}
		else if(str[i] == 'L'){
			i++;
			if(str[i] == 'A'){
				i++;
				if(str[i] == 'S'){
					i++;
					if(str[i] == 'T'){
						printf("LAST ");
						stacktoken = "LAST";
						push(stacktoken);
					}
				}
			}
		}
		else if(str[i] == 'R'){
			i++;
			if(str[i] == 'E'){
				i++;
				if(str[i] == 'T'){
					i++;
					if(str[i] == 'U'){
						i++;
						if(str[i] == 'R'){
							i++;
							if(str[i] == 'N'){
								printf("RETURN ");
								stacktoken = "RETURN";
								push(stacktoken);
							}
						}
					}
				}
			}
		}
		else if(str[i] == 'S'){
			i++;
			if(str[i] == 'T'){
				i++;
				if(str[i] == 'R'){
					i++;
					if(str[i] == ' '){
						printf("STR ");
						stacktoken = "STR";
						push(stacktoken);
					}
				}
			}
		}
		else if(str[i] == 'T'){
			i++;
			if(str[i] == 'H'){
				i++;
				if(str[i] == 'E'){
					i++;
					if(str[i] == 'N'){
						printf("THEN ");
						stacktoken = "THEN";
						push(stacktoken);
					}
				}
			}
			else if(str[i] =='R'){
				i++;
				if(str[i] == 'U'){
					i++;
					if(str[i] == 'E'){
						printf("TRUE ");
						stacktoken = "TRUE";
						push(stacktoken);
					}
				}
			}
		}
		else if(str[i] == 'W'){
			i++;
			if(str[i] == 'H'){
				i++;
				if(str[i] == 'I'){
					i++;
					if(str[i] == 'L'){
						i++;
						if(str[i] == 'E'){
							printf("WHILE ");
							stacktoken = "WHILE";
							push(stacktoken);
						}
					}
				}
			}
		}
		else if(str[i] == '('){
			printf("LPAREN ");
			stacktoken = "Parenthesis_L";
			push(stacktoken);
		}
		else if(str[i] == ')'){
			printf("RPAREN ");
			stacktoken = "Parenthesis_R";
			push(stacktoken);
		}
		else if(str[i] == '{'){
			printf("LBRACE ");
			stacktoken = "Brace_L";
			push(stacktoken);
		}
		else if(str[i] == '}'){
			printf("RBRACE ");
			stacktoken = "Brace_R";
			push(stacktoken);
		}
		else if(str[i] == '"'){
			int a = i, cnl = 0, ctl = 0;
			i++;
			while(str[i] != '"'){
				i++;
				if(str[i] == '['){
					i++;
					if(str[i] == 'N'){
						i++;
						if(str[i] == 'L'){
							i++;
							if(str[i] == ']'){
								i++;
								cnl++;
							}
						}
					}
					else if(str[i] == 'T'){
						i++;
						if(str[i] == ']'){
							i++;
							ctl++;
						}
					}
				}
			}
			int size = i - a, b;
			char lit[size];
			for(b = 0; b <= i; b++){
				lit[b] = str[a];
				a++;
			}
			printf("LITERAL ");
			stacktoken = "String_Constant";
			push(stacktoken);

			if(cnl > 0) printf("%d NEWLINES ", cnl);
			if(cnl > 0) printf("%d TABS ", ctl);

		}
		else if(str[i] == '\''){
			i += 2;
			if(str[i] == '\''){
				printf("char ");
				stacktoken = "Single_Char";
				push(stacktoken);
			}
			else{
				printf("ERROR ");
				stacktoken = "String_Constant";
				push(stacktoken);
			}
		}
		//else if(str[i] == ','){
		//	printf("DELIMITER ");

		//}
		else if(str[i] == '@'){
			i++;
			if(islower(str[i])){
				printf("FEED_INPUT ");
				stacktoken = "FEED_@";
				push(stacktoken);
			}
			/*while(str[i] != ','){
				i++;
			}
			if(str[i] == ','){
				printf("DELIMITER ");
			}*/
		}
		else if(str[i] == '%'){
			i++;
			if(isupper(str[i])){
				printf("FEED_INPUT ");
				stacktoken = "FEED_%";
				push(stacktoken);

				while(str[i] != ')'){
					i++;
				}
				if(str[i] == ')'){
					printf("RPAREN ");
					stacktoken = "Parenthesis_R";
					push(stacktoken);
				}
			}
			else if (isdigit(str[i])){
				printf("ARITH_OPERATOR");
				stacktoken = "Arith_Op_%";
				push(stacktoken);
			}
		}
		else if(str[i] == '&'){
			i++;
			if(str[i] == '&'){
				printf("LOGICAL_AND ");
				stacktoken = "Logical_AND";
				push(stacktoken);
			}
		}
		else if(str[i] == '|'){
			i++;
			if(str[i] == '|'){
				printf("LOGICAL_OR ");
				stacktoken = "Logical_OR";
				push(stacktoken);
			}
		}
		else if(str[i] == '!'){
			i++;
			if(isalpha(str[i])){
				printf("LOGICAL_NOT ");
				stacktoken = "Logical_NOT";
				push(stacktoken);
			}
			else if(str[i] == '='){
				printf("CONDITIONAL_OPERATOR_!= ");
				stacktoken = "Conditional_Op_!=";
				push(stacktoken);
			}
		}
		else if(str[i] == '>'){
			i++;
			if(str[i] == '='){
				printf("CONDITIONAL_OPERATOR_>= ");
				stacktoken = "Conditional_Op_>=";
				push(stacktoken);
			}
			else if(isalpha(str[i]) || isdigit(str[i]) || str[i] == ' '){
				printf("CONDITIONAL_OPERATOR_> ");
				stacktoken = "Conditional_Op_>";
				push(stacktoken);
			}
		}
		else if(str[i] == '<'){
			i++;
			if(str[i] == '='){
				printf("CONDITIONAL_OPERATOR_<= ");
				stacktoken = "Conditional_Op_<=";
				push(stacktoken);
			}
			else if(isalpha(str[i]) || isdigit(str[i]) || str[i] == ' '){
				printf("CONDITIONAL_OPERATOR_< ");
				stacktoken = "Conditional_Op_<";
				push(stacktoken);
			}
		}

		else if(str[i] == '\n'){

		}
		else if(str[i] == '\t'){

		}
		else if(str[i] == ' '){

		}
		else if(str[i] == ','){
			printf("COMMA ");
			stacktoken = "Comma";
			push(stacktoken);
		}
		else if(str[i] == ';'){
			printf("SEMICOLON ");
			stacktoken = "Semicolon";
			push(stacktoken);
		}
		else{
			printf("UNKNOWN ");
			stacktoken = "Unknown";
			push(stacktoken);
		}

	i++;
	}
	printf("\n");

}

