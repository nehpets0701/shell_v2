#include "hsh.h"

/**
 *executeProg-executes given command
 *Return: void
 *@subInputs:subinputs
 *@env:enviornment
 */
int executeProg(char **subInputs, char **env)
{
	char **path, *adress, *getpath;
	int i, fd;

	if (env == NULL)
		return (-1);

	fd = access(subInputs[0], F_OK);
	if (fd == 0)
	{
		execute(subInputs[0], subInputs, env);
		return (1);
	}
	fd = 0;
	getpath = _getenv("PATH", env);
	if (getpath == NULL)
		return (-1);
	path = _strtok(getpath, ":");
	for (i = 0; path[i] != NULL; i++)
	{
		adress = catcmd(path[i], subInputs[0]);
		fd = access(adress, F_OK);
		if (fd == 0)
		{
			execute(adress, subInputs, env);
			free(adress);
			free(getpath);
			free_double(path);
			return (1);
		}
		free(adress);
	}
	free(getpath);
	free_double(path);
	return (-1);
}

/**
 * execute - finds and executes valid commands
 * @adress: Location of a command file
 * @input: what the user inputs in shell
 * @env: env variables if needed
 * return: void
 */
void execute(char *adress, char **input, char **env)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(adress, input, env) == -1)
		{
			perror("Execve Error");
			exit(0);
		}
	}
	else
		wait(NULL);
}
