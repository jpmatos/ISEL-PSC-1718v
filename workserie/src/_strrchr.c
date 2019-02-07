/*Implemente a função ​ _strrchr​ , que será a sua versão da função ​ strrchr da biblioteca ​ standard da
linguagem C, sem recorrer a outras funções dessa biblioteca.*/
#include <stdio.h>

/* The strrchr() function returns a pointer to the  last  occurrence of the character c in the string s. */
char* _strrchar(char* s, char c)
{
	char* latest;
	for (int i = 0; s[i] != EOF; i++)
	{
		if (s[i] == c)
		{
			latest = &s[i];
		}
	}
	return latest;
}

int main()
{
	char string[] = "hello, world!";
	char* pointer = _strrchar(string, 'o');
	printf("pointer to first 'o': %p; pointer to second 'o': %p\n", &string[4], &string[8]);
	printf("char chosen: %c; pointer to last char: %p\n", *pointer, pointer);
}
