#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* vars_func.c*/
int is_chain(info_t *info, char *buf, size_t *p);
int replace_variables(info_t *info);
int replace_aliases(info_t *info);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_string(char **old, char *new);

/* mystrings.c*/
int _strcmp(char *s1, char *s2);
char *_starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
int _strlen(char *s);

/* my_strings1.c*/
char *_strcpy(char *dest, char *source);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

/* shloop.c */
void fork_cmd(info_t *info);
char *find_cmd(info_t *info);
int find_builtin(info_t *info);
int hsh(info_t *info, char **av);

/* memory_code.c*/
int bfree(void **ptr);

/* my_lists1.c*/
ssize_t get_node_index(list_t *head, list_t *node);
list_t *node_starts_with(list_t *node, char *prefix, char c);
size_t print_list(const list_t *head);
char **list_to_strings(list_t *head);
size_t get_list_length(const list_t *head);

/* my_lists.c*/
void free_list(list_t **head_ptr);
int delete_node_at_index(list_t **head, unsigned int index);
size_t print_list_str(const list_t *h);
list_t *add_node_end(list_t **head, const char *str, int num);
list_t *add_node(list_t **head, const char *str, int num);

/* getenv_func.c*/
int _set_env(info_t *info, char *var, char *value);
int _unset_env(info_t *info, char *var);
char **get_environ(info_t *info);

/* my_exit_func.c*/
char *_strncat(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);
char *_strchr(char *s, int c);

/* my_errors2.c*/
void _remove_comments(char *buf);
char *convert_number(long int num, int base, int flags);
int print_s(int input, int fd);
void print_error(info_t *info, char *estr);
int _erratoi(char *s);

/* my_errors.c*/
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);
int _eputchar(char c);
void _eputs(char *str);

/* my_environ.c*/
int populate_env_list(info_t *info);
int myset_env(info_t *info);
int myunset_env(info_t *info);
char *get_env(info_t *info, const char *name);
int print_env(info_t *info);

/* my_builtins2.c*/
int _my_alias(info_t *info);
int print_alias(list_t *node);
int _set_alias(info_t *info, char *str);
int _unset_alias(info_t *info, char *str);
int my_history(info_t *info);

/* my_builtins.c*/
int _my_exit(info_t *info);
int _mycd(info_t *info);
int _my_help(info_t *info);


/* my_atoi.c*/
int is_delim(char c, char *delim);
int is_alphabetic(int c);
int is_interactive(info_t *info);
int _atoi(char *s);

/* getlinefunc.c*/
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused)) int sig_num);

/* getinfo_func.c*/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* myhistory.c*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* realloc_func.c*/
char *_memset(char *s, char b, unsigned int);
void ffree(char **str_arr);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* mytokenizer.c */
char **strtow(char *str, char *d);
char **strtow2(char *str, char *d);

/* parser_func.c*/
int is_cmd(info_t *info, char *path);
char *dup_chars(const char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *command);


/* loophsh.c */
int loophsh(char **);

#endif
