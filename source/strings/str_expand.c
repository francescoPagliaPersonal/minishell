/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:29:47 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/20 13:41:59 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_strings.h"
#include "ms_structs.h"
#include <minishell.h>
#include <time.h>

int clear_quotes(t_arr *istr)
{
	int i;
	t_istr *tmp;
	char *line;

	i = 0;
	while (i < istr->size)
	{
		tmp = (t_istr *)istr->arr[i];
		if (tmp->type == 0)
		{
			line = expand_quotes(tmp->str);
			if (line == NULL)
				return (0);
			free(tmp->str);
			tmp->str = line;
			line = NULL;
		}
		i++;
	}
	return (1);
}

char **istr_to_arr(t_arr *istr)
{
	char **arr;
	char *tmp;
	int i;

	i = 0;
	arr = (char **)calloc(istr->size + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (i < istr->size)
	{
		tmp =((t_istr *)istr->arr[i])->str;
		arr[i] = ft_strdup(tmp);
		if (arr[i] == NULL)
			return (arr_free(arr), NULL);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char *join_expansions(t_arr *istr)
{
	char *line;
	char **arr;
	
	if (!clear_quotes(istr))
		return (NULL);
	arr = istr_to_arr(istr);
	if (arr == NULL)
		return (NULL);
	line = arr_to_str(arr, 0);
	if (line == NULL)
		return (arr_free(arr), NULL);
	return (line);	
}

char	*str_expand(int (*f)(t_quote *data, char *str, int use_quote),
			t_arr *env, char *str, int use_quote)
{
	char	*line;
	t_quote	data;

	if (str == NULL)
		return (NULL);
	if (*str == '\0')
		return (ft_strdup(""));
	line = NULL;
	data.expand = tar_init(NULL, istr_free);
	data.env = env;
	data.quote = 0;
	if (data.expand == NULL)
		return (NULL);
	if (!f(&data, str, use_quote))
		return (arr_free((char **)data.expand->arr), free(data.expand), NULL);
	if (data.expand->size != 0)
		line = join_expansions(data.expand);
	// {
	// 	clear_quotes(data.expand, env);
	// 	arr_print((char **)data.expand->arr, '\n', 1);
	// 	line = arr_to_str((char **)data.expand->arr, 0);
	// 	free(data.expand);
	// }
	tar_free(data.expand);
	if (line == NULL)
		return (NULL);
	return (line);
}
