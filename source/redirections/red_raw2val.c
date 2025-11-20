/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_raw2val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:19:46 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/20 13:12:32 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include <minishell.h>

int	red_raw2val(t_red *item, t_arr *env)
{
	// char	*line_d;
	// char	*line_q;

	if (item->type != in_heredoc)
		item->val = str_expand(dollar, env, item->raw, 1);
	else
		item->val = expand_quotes(item->raw);
	if (item->val == NULL)
		return (0);
	// line_q = str_expand(quotes, env, line_d, 0);
	// if (item->type != in_heredoc)
	// 	free(line_d);
	// if (line_q == NULL)
	// 	return (0);
	// item->val = line_q;
	return (1);
}
