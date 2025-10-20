/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:16:42 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/20 14:46:18 by vmanuyko         ###   ########.fr       */
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
 * 2nd part of process_line function which sets the values
 * in line based on the key.
 * Return value:
 * -1 on error, 0 on success.
*/
static int	set_values(char **line, t_shell *shell, char *key)
{
	int		id;
	char	*value;
	char	*part_line;
	size_t	len;
	char	*processed_line;
	
	len = 0;
	id = env_getid(shell->env->arr, key);
	env_getvalue(shell->env->arr, &value, id);
	if (!value)
		value = ft_strdup("");
	while ((*line)[len] != '$')
		len++;
	part_line = ft_strncpy(*line, len);
	if (!part_line)
		return (-1);
	processed_line = ft_strjoin(part_line, value);
	free(part_line);
	free(value);
	if (!processed_line)
		return (-1);
	free (*line);
	*line = processed_line;
	return (0);
}

/*
 * Finds the variable expansions in a line processed by heredoc
 * and replaces them with value;
 * Return value:
 * -1 on error, 0 on success;
*/
static int	process_line(char **line, t_shell *shell)
{
	char	*key;
	size_t	i;
	size_t	key_len;

	i = 0;
	key_len = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			while ((*line)[i] && (*line)[i] != ' ')
			{
				key_len++;
				i++;
			}
			i -= key_len;
			break ;
		}
		i++;
	}
	key = ft_strncpy(*line + i + 1, key_len - 1);
	if (!key)
		return (-1);
	if (set_values(line, shell, key) == -1)
		return (-1);
	return (free (key), 0);
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
	{
		perror(ER_PIPE);
		return(-1);
	}
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			close (fd[0]);
			close (fd[1]);
			return (-1);
		}
		if (ft_strchr(line, '$') && expand == 1)
		{
			if (process_line(&line, shell) == -1)
			{
				free(line);
				close (fd[0]);
				close (fd[1]);
				return (-1);
			}
		}
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			close(fd[1]);
			return (fd[0]);
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free (line);
	}
	return (-1);
}
