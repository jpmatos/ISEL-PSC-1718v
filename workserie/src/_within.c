/*Escreva o programa utilitário within, que copia para o standard output as linhas do standard input que
contenham pelo menos uma das strings passadas como argumento ao programa.*/

#include <stdio.h>
#include <string.h>

void within (int argc, char *argv[]){
	char *line = NULL;
	size_t len = 0;
	//gets line from standard input
	int end = getline(&line, &len, stdin);
	//replaces \n with \0
	line[end-1] = '\0';
	//do the following while stdin isn't an empty line
	while(line[0] != '\0'){
		//goes through all the call arguments
		for(int i = 0; i < argc; i++){
			//see if line matches the current call arguments
			if(!strcmp(argv[i], line))
				//prints line
				printf("%s\n", line);
		}
		//gets line from standard output again
		end = getline(&line, &len, stdin);
		line[end-1] = '\0';
	}
}

int main(int argc, char *argv[]){
	within(argc, argv);
}
