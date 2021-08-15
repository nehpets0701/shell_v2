#include "hsh.h"

/*
*main-main for shell 2
*Return: 0 or errors
*@argc:argc
*@argv:argv
*@env:enviornment
*/
int main(int argc, char **argv, char **env)
{
	char whole[1024];
	char *input = NULL;
	char **subInputs = NULL;
	size_t length = 1024;
	int num, i, j, read = 0, error = 0, flag = 0;

	(void)argc;
	(void)argv;
	(void)env;
	(void)whole;
	signal(SIGINT, sigint);
	while (1)
	{
		flag = 0;
		printPrompt();

		input = malloc(1024);
		if (input == NULL)
			return (-1);

		read = getline(&input, &length, stdin);
		if (read == -1)
		{
			fprintf(stdout, "\n");
			free(input);
			return (-1);
		}
		if (read == 0)
		{
			free(input);
			continue;
		}
		if (input[read - 1] == '\n')
			input[read - 1] = '\0';
		_strcpy(whole, input);
		subInputs = _strtok(input, " ");
		for (i = 0; subInputs[i] != NULL; i++)
		if (i != 0)
			num = i + 1;
		else
			num = 1;
		if (subInputs[0] != NULL)
		{
			for (i = 0; subInputs[i] != NULL; i++)
			{
				for (j = 0; subInputs[i][j] != '\0'; j++)
				{
					if (subInputs[i][j] == '#')
						subInputs[i][j] = '\0';
				}
			}


			flag = handleBuiltins(subInputs, num, env, input);
			if (flag == 1)
				continue;
			if (flag == 0)
				error = executeProg(subInputs, env);
		}
		else
		{
			free(input);
			continue;
		}
		if (error == -1)
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], num, subInputs[0]);
		free (input);
		i = 0;
		while (subInputs[i] != NULL)
		{
			free(subInputs[i]);
			i++;
		}
	}
}

/**
 *printPrompt-print $
 *Return: void
 */
int printPrompt(void)
{
	int print = 0;
	char *prompt = "$ ";

	if (isatty(STDIN_FILENO) != 0)
		print = write(STDOUT_FILENO, prompt, 2);
	if (print == -1)
		return (-1);
	return (0);
}

/**
*handleBuiltins-directs to builtin functions
*@input:input
*@subInputs:delimited input
*/
int handleBuiltins(char **subInputs, int num, char **env, char *input)
{
	int flag = 0;

	if (_strcmp(subInputs[0], "exit") == 0)
	{
		flag = 1;
		free(input);
		free(subInputs);
		if (num > 1)
			exit(atoi(subInputs[1]));
		else
			exit(0);
	}

	if (_strcmp(subInputs[0], "cd") == 0)
	{
		flag = 1;
		cd(subInputs, env);
	}

	if (_strcmp(subInputs[0], "env") == 0)
	{
		flag = 1;
		printEnv(env);
	}

	/*setenv*/

	/*unsetenv*/

	/*alias-adv*/

	/*help-adv*/

	/*history-adv*/

	return (flag);
}

/**
 *sigint-stop control c
 *Return:void
 *@sig:signal
 */
void sigint (int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$", 3);
}
