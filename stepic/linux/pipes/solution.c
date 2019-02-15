#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *command = malloc(strlen(argv[1]));
	strcpy(command, argv[1]);
	if(argc == 3)
	{
		strcat(command, " ");
		strcat(command, argv[2]);
	}
	FILE *util_pipe = popen(command, "r");
	char *s = malloc(1000);
	int k = 0;
	while(1)
	{
		s = fgets(s, 1000, util_pipe);
		if(s == 0)
			break;
		for(int i = 0; i < strlen(s); i++)
		{
			if(s[i] == '0')
				k++;
		}
	}
	free(s);
	printf("%d\n", k);
	return 0;
}
