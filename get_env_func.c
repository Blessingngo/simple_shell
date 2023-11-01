#include "shell.h"

/**
 * get_environ - function that returns a copy of the string array
 * for the environment.
 * @info: Structure containing potential arguments (unused here)
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
{
	info->environ = list_to_strings(info->env);
	info->env_changed = 0;
}
	return (info->environ);
}

/**
 * _unset_env - function that removes an environment variable
 * @info: Structure containing potential arguments (unused here)
 * @var: The environment variable to remove
 * Return: 1 on delete, 0 otherwise
 */
int _unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
	return (0);

	while (node)
{
	p = _starts_with(node->str, var);
	if (p && *p == '=')
{
	info->env_changed = delete_node_at_index(&(info->env), i);
	i = 0;
	node = info->env;
	continue;
}
	node = node->next;
	i++;
}
	return (info->env_changed);
}

/**
 * _set_env - Initialize a new environment variable or
 * modify an existing one.
 * @info: Structure containing potential arguments (unused here)
 * @var: The environment variable
 * @value: The value to set for the environment variable
 * Return: Always 0
 */
int _set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
	return (0);

	buf = malloc(strlen(var) + strlen(value) + 2);
	if (!buf)
	return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
{
	p = _starts_with(node->str, var);
	if (p && *p == '=')
{
	free(node->str);
	node->str = buf;
	info->env_changed = 1;
	return (0);
}
	node = node->next;
}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
