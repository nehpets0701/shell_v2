#ifndef HSH_H
#define HSH_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdbool.h>

int main(int argc, char **argv, char **env);
char **_strtok(char *s, char *delim);
int _strcmp(char *s1, char *s2);
unsigned int _strlen(char *p);
char *_strcpy(char *src, char *dest);
int printPrompt(void);
int builtins(char **s, int n, char **e, char *i, char **a, char **h, int hi);
void sigint (int sig);
int executeProg(char **subInputs, char **env);
void execute(char *adress, char **input, char **env);
char *_getenv(char *section, char **env);
char *catcmd(char *path, char *cmd);
void free_double(char **dptr);
char *_strdup(char *dest, char *src);
void printEnv(char **env);
void cd(char **subInputs, char **env, char **argv, int num);
char *_strcat(char *dest, char *src);
void _setenv(char **subInputs);
void _unsetenv(char **subInputs);
void printHistory(char **history, int historyInt);

extern char **environ;

#endif
