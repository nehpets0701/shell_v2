#include "hsh.h"

/**
*printEnv-prints enviornment
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
*@argv:argv
*@num:num
*/
void cd(char **subInputs, char **env, char **argv, int num)
{
	int i;
	char *path;

	if (subInputs[1] == NULL)
	{
		path = _getenv("HOME", env);
		chdir(path);
		for (i = 0; environ[i] != NULL; i++)
		{
			if (environ[i][0] == 'P' && environ[i][1] == 'W' && environ[i][2] == 'D')
				environ[i] = "PWD=/home/";
		}
		free(path);
	}
	else if (_strcmp(subInputs[1], "-") == 0)
	{
		chdir("/home");
		for (i = 0; environ[i] != NULL; i++)
		{
			if (environ[i][0] == 'P' && environ[i][1] == 'W' && environ[i][2] == 'D')
				environ[i] = "PWD=/home/";
		}
	}
	else
	{
		if (chdir(subInputs[1]) == 0)
		{
			for (i = 0; environ[i] != NULL; i++)
			{
				if (environ[i][0] == 'P' && environ[i][1] == 'W' && environ[i][2] == 'D')
				{
					environ[i] = "PWD=test";
				}
			}
		}
		else
			fprintf(stderr, "%s: %d, cd: can't cd to %s", argv[0], num, subInputs[1]);
	}
}

/**
*_setenv-sets var
*@subInputs:subinputs
*/
void _setenv(char **subInputs)
{
	int i;

	/*printf("%s\n", _getenv("PWD", env));*/
	for (i = 0; environ[i] != NULL; i++)
	{
		if (environ[i] == subInputs[1])
		{
			printf("%s\n", environ[i]);
			environ[i] = subInputs[2];
		}
	}
	/*printf("%s\n", _getenv("PWD", env));*/
}

/**
*_unsetenv-remove var
*@subInputs:subinputs
*/
void _unsetenv(char **subInputs)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (environ[i] == subInputs[1])
		{
			environ[i] = NULL;
		}
	}
}

/**
*printHistory-history
*@history:history
*@historyInt:position in history
*/
void printHistory(char **history, int historyInt)
{
	while (history[historyInt] != NULL)
	{
		printf("%s\n", history[historyInt]);
		historyInt++;
	}
}
