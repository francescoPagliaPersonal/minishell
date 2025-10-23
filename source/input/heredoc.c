/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:16:42 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/23 19:22:23 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * Checks weather the given str contains quotes.
 * Return value:
 * 1 if quoted, 0 if not.
*/
static int	is_quoted(char *str)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = 1;
		i++;
	}
	if (quote == 1)
		return (1);
	return (0);
}

/*
 * Processes the line by expanding the env values if found.
 * Return value:
 * -1 on error, 0 on success.
*/
static int	process_line(char **line, t_shell *shell, int expand)
{
	char	*expand_line;

	expand_line = str_expand(dollar, shell->env, *line, expand);
	if (!expand_line)
		return (-1);
	free (*line);
	*line = expand_line;
	return (0);
}

int	heredoc(char *limiter, t_shell *shell)
{
	int		expand;
	int		fd;
	char	*line;

	expand = 1;
	if (is_quoted(limiter))
		expand = 0;
	limiter = str_expand(quotes, shell->env->arr, limiter, 0);
	if (!limiter)
		return (-1);
	fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline(">");
		if (!line)
			return (close (fd), -1);
		if (ft_strchr(line, '$') && expand == 1)
		{
			if (process_line(&line, shell, expand) == -1)
				return (free(line), close (fd), -1);
		}
		if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			close (fd);
			fd = open("/tmp/heredoc_tmp", O_RDONLY);
			return (fd);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
	}
	return (-1);
}
