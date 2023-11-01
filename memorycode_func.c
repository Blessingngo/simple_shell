#include "shell.h"

/**
* bfree- function that frees a pointer and sets the address to NULL
* @ptr: Address of the pointer to free
*
* Return: 1 if freed, otherwise 0.
*/
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
