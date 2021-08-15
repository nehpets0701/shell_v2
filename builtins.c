#include "hsh.h"

/**
*printEnv-prints enviornment
*@subInputs:subinputs
*@env:env
*/
void printEnv(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
		printf("%s\n", env[i]);
}

/**
*cd-cd
*@subInputs:subinputs
*@env:env
*/
void cd(char **subInputs, char **env)
{
	char *path;
	if (subInputs[1] == NULL)
	{
		path = _getenv("HOME", env);
		chdir(path);
		free(path);
	}
	else if (_strcmp(subInputs[1], "-") == 0)
		chdir("/home");
	else
		chdir(subInputs[1]);
	/*printf("%s\n", _getenv("PWD", env));*/
}
