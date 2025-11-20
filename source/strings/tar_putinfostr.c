#include "libft.h"
#include "ms_structs.h"
#include <minishell.h>

int	tar_putinfostr(t_arr *arr, char *str, int value)
{
	t_istr	*item;

	item = ft_calloc(1, sizeof(t_istr));
	if (item == NULL)
		return (0);
	item->str = ft_strdup(str);
	item->type = value;
	item->len = ft_strlen(str);
	if (item->str == NULL)
		return (free(item), 0);
	if (!tar_linkone(arr, item))
		return (0);
	return (1);
}