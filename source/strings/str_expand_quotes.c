/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expand_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:50:13 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/20 12:46:14 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include "ms_structs_support.h"
#include <minishell.h>

static char	*save_substr(char *str, char **end, t_quote *data)
{
	char	*line;

	if (str + 1 <= *end || str + 1 == *end + 1 || *(*end + 1) == '\0')
	{
		if (*str == data->quote)
			str++;
		line = ft_strncpy(str, *end - str + 1);
		if (line == NULL)
			return (NULL);
		if (!tar_putstr(data->expand, line))
			return (NULL);
		free(line);
	}
	if (*(*end + 1) == data->quote && data->quote != '\0')
	{
		str = *end + 2;
		(*end)++;
		data->quote = str_isquoted(**end);
	}
	else
		str = *end + 1;
	return (str);
}

int	quotes(t_quote *data, char *str, int use_quote)
{
	char	*end;

	(void)use_quote;
	end = str;
	while (*str)
	{
		data->quote = str_isquoted(*end);
		if (*(end + 1) == data->quote
			/*|| (*(end + 1) == '$' && data->quote != '\'' )*/
			|| (data->quote == 0 && ft_strchr("\'\"", *(end + 1)) != NULL))
			str = save_substr(str, &end, data);
		if (str == NULL)
			return (0);
		end++;
	}
	return (1);
}

char *expand_quotes(char *str)
{
	char	*line;
	t_quote	data;

	if (str == NULL)
		return (NULL);
	if (*str == '\0')
		return (ft_strdup(""));
	line = NULL;
	data.expand = tar_init(NULL, free);
	data.quote = 0;	
	if (data.expand == NULL)
		return (NULL);
	if (!quotes(&data, str, 0))
		return (tar_free(data.expand), NULL);
	if (data.expand->size != 0)
	{
		line = arr_to_str((char **)data.expand->arr, 0);
		free(data.expand);
	}
	if (line == NULL)
		return (tar_free(data.expand), NULL);
	return (line);
}