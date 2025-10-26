/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:42:56 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/26 20:19:34 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* This small demo evaluate if pipes are somehow connected to some kind of data.
 * basically if after the delimiter has been found no char have been detected
 * then an error of unexpected token will be thrown.
 */
int main(int ac, char **av, char **env)
{
	t_shell	sh;
	
	(void)ac;
	(void) av;
	init_shell(&sh, env);
	while (1)
	{
		if (get_command(&sh))
			cmd_validate_pipes(sh.cmd_line);
		reset_shell(&sh);		
	}
	free_shell(&sh);
	return (0);	
}