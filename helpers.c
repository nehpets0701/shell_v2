#include "hsh.h"

/**
 *_strcmp-compare
 *Return:0/1
 *@s1:input
 *@s2:input
 */
int _strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 == *s2)
	{
		return (0);
	}
	else
	{
		return (*s1 - *s2);
	}
}

/**
 *_strcpy-add letter
 *Return:0
 *@dest:input
 *@src:input
 */
char *_strcpy(char *dest, char *src)
{
	char *start = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return (start);
}

/**
 *_strlen-strlen
 *Return:unsigned int
 *@p:input
 */
unsigned int _strlen(char *p)
{
	unsigned int count = 0;

	if (p == NULL)
		return (0);

	while (*p != '\0')
	{
		count++;
		p++;
	}

	return (count);
}

/**
 * _strtok - break strings into token using delimiters
 *
 * @s: content of the string
 *
 * @delim: delimiters used to split the string
 *
 * Return: tokens from string
 */

char **_strtok(char *s, char *delim)
{
	char **tok;
	char *str;
	int i = 1, index = 0;

	if (s == NULL)
		return (NULL);

	while (s[index])
	{
		if (s[index] == *delim)
			i++;
		index++;
	}

	tok = malloc(sizeof(char *) * (i + 1));
	if (tok == NULL)
	{
		free(tok);
		return (NULL);
	}
	tok[i] = NULL;

	i = 0;
	str = strtok(s, delim);
	while (1)
	{
		if (str == NULL)
			break;
		tok[i] = malloc(sizeof(char) * _strlen(str) + 1);
		if (tok[i] == NULL)
		{
			i = 0;
			while (tok[i] != NULL)
			{
				free(tok[i]);
				i++;
			}
			free(tok[i]);
			free(str);
			free(tok);
			return (NULL);
		}
		_strcpy(tok[i], str);
		i++;
		str = strtok(NULL, delim);
	}
	tok[i] = NULL;
	/*i = 0;
	while (tok[i] != NULL)
	{
		free(tok[i]);
		i++;
	}
	free(tok);*/
	free(str);
	return (tok);
}

/**
 * _getenv - gets a string of the designated path location
 * @section: the string to look for in the environment
 * @env: the environment variable
 * Return: return the string of the section in the environment
 */
char *_getenv(char *section, char **env)
{
	char *envtoken, *envpart = NULL, *result = NULL;
	int i, j, flag = 1;

	if (env[0] == NULL)
		return (NULL);
	for (i = 0; env[i]; i++)
	{
		for (j = 0; section[j]; j++)
			if (env[i][j] != section[j])
				flag = 1;
		if (flag == 0)
		{
			envpart = _strdup(envpart, env[i]);
			envtoken = strtok(envpart, "=");
			envtoken = strtok(NULL, "\n");
			result = _strdup(result, envtoken);
			free(envpart);
			return (result);
		}
		flag = 0;
	}
	return (NULL);
}
