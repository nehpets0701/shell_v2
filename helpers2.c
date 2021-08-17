#include "hsh.h"

/**
 * catcmd - combines command with path adress
 * @path: adress to add command to
 * @cmd: command to add onto
 * Return: new combined string
 */
char *catcmd(char *path, char *cmd)
{
	int len, i;
	char *newpath, slash = '/';

	len = _strlen(path);

	for (i = 0; cmd[i] != '\0'; i++)
		if (cmd[i] == '\n')
			cmd[i] = '\0';
	newpath = malloc(sizeof(char) * (len + 2 + _strlen(cmd)));
	if (newpath == NULL)
		return (NULL);
	_strcpy(newpath, path);
	newpath[len] = slash;
	len++;
	for (i = 0; cmd[i]; i++)
		newpath[len + i] = cmd[i];
	newpath[len + i] = '\0';
	return (newpath);
}

/**
 * free_double - frees up all allocated space of a double pointer
 * @dptr: double pointer to free.
 * Return: void
 */
void free_double(char **dptr)
{
	unsigned int i = 0;

	if (dptr == NULL)
		return;
	while (dptr[i])
		free(dptr[i]), i++;
	if (dptr[i] == NULL)
		free(dptr[i]);
	free(dptr);
}

/**
 * _strdup - duplicates a string into an empty string
 * @dest: destination of the duplicated string
 * @src: the source of the string to be duplicated
 * Return: destination string
 */
char *_strdup(char *dest, char *src)
{
	dest = malloc((_strlen(src) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	_strcpy(dest, src);
	return (dest);
}

/**
 *_strcat-cat
 *Return:char
 *@dest:input
 *@src:input
 */
char *_strcat(char *dest, char *src)
{
	char *cat = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return (cat);
}
