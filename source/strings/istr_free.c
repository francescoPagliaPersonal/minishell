
#include <minishell.h>

void	istr_free(void *item)
{
	if (item == NULL)
		return ;
	if (((t_istr *)item)->str != NULL)
		free(((t_istr *)item)->str);
	free(item);
}