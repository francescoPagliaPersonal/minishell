/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:16:42 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/20 19:03:40 by vmanuyko         ###   ########.fr       */
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

static int	process_line(char **line, t_shell *shell)
{
	char	*expand_line;

	expand_line = 
}

int	heredoc(char *limiter, t_shell *shell)
{
	int		expand;
	int		fd[2];
	char	*line;

	expand = 1;
	if (is_quoted(limiter))
	{
		limiter = ft_strtrim(limiter, "\'\"");
		if (!limiter)
			return (-1);
		expand = 0;
	}
	if (pipe(fd) == -1)
		return(perror(ER_PIPE), -1);
	while (1)
	{
		line = readline(">");
		if (!line)
			return (close (fd[0]), close (fd[1]), -1);
		if (ft_strchr(line, '$') && expand == 1)
		{
			if (process_line(&line, shell) == -1)
				return (free(line), close (fd[0]), close (fd[1]), -1);
		}
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
			return (close(fd[1]), fd[0]);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free (line);
	}
	return (-1);
}
