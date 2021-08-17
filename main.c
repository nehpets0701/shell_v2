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
	char *input = NULL, **subInputs = NULL, whole[1024], **history = NULL;
	size_t length = 1024;
	int num, i, j, read = 0, error = 0, flag = 0, historyInt = -1;

	(void)argc;
	signal(SIGINT, sigint);
	while (1)
	{
		historyInt++;
		flag = 0;
		printPrompt();
		input = malloc(1024);
		if (input == NULL)
			return (-1);
		history = malloc(10000);
		if (history == NULL)
			return (-1);
		read = getline(&input, &length, stdin);
		if (read == -1)
		{
			fprintf(stdout, "\n");
			free(input);
			free(history);
			return (-1);
		}
		if (read == 0)
		{
			free(input);
			free(history);
			continue;
		}
		if (input[read - 1] == '\n')
			input[read - 1] = '\0';
		_strcpy(whole, input);
		history[historyInt] = input;
		subInputs = _strtok(input, " ");
		for (i = 0; subInputs[i] != NULL; i++)
		if (i != 0)
			num = i + 1;
		else
			num = 1;
		if (subInputs[0] != NULL)
		{
			for (i = 0; subInputs[i] != NULL; i++)
				for (j = 0; subInputs[i][j] != '\0'; j++)
					if (subInputs[i][j] == '#')
						subInputs[i][j] = '\0';
			free(input);
			flag = builtins(subInputs, num, env, input, argv, history, historyInt);
			if (flag == 1)
				continue;
			if (flag == 0)
				error = executeProg(subInputs, env);
		}
		else
		{
			free(input);
			free(history);
			continue;
		}
		if (error == -1)
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], num, subInputs[0]);
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
*builtins-directs to builtin functions
*Return:0/1 flag
*@i:input
*@s:delimited input
*@n:n
*@e:env
*@a:argv
*@h:history
*@hi:historyInt
*/
int builtins(char **s, int n, char **e, char *i, char **a, char **h, int hi)
{
	int flag = 0;

	(void)i;
	if (_strcmp(s[0], "exit") == 0)
	{
		flag = 1;
		free(s);
		if (n > 1)
			exit(atoi(s[1]));
		else
			exit(0);
	}

	if (_strcmp(s[0], "cd") == 0)
	{
		flag = 1;
		cd(s, e, a, n);
	}
	if (_strcmp(s[0], "env") == 0)
	{
		flag = 1;
		printEnv(e);
	}
	if (_strcmp(s[0], "setenv") == 0)
	{
		flag = 1;
		_setenv(s);
	}
	if (_strcmp(s[0], "unsetenv") == 0)
	{
		flag = 1;
		_unsetenv(s);
	}
	/*alias-adv, help-adv*/
	if (_strcmp(s[0], "history") == 0)
	{
		flag = 1;
		printHistory(h, hi);
	}
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
