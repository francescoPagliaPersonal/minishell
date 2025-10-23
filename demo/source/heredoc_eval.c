/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_eval.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:50:21 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/23 18:47:06 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	int		fd;
	char	*line;
	t_shell shell;
	
	if (argc != 2)
		return (printf("Needs 1 limiter\n"), 1);
	shell.env = malloc(sizeof(t_arr));
	if(!shell.env)
		return (1);
	shell.env->arr = envp;
	fd = heredoc(argv[1], &shell);
	if (fd == -1)
		printf(("Error by heredoc\n"));
	else
	{
		while (1)
		{
			line = get_next_line(fd);
			if (!line)
			{
				close (fd);
				break ;
			}
			printf("%s", line);
			free(line);
		}
	}
	return (free(shell.env),0);
}
