/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readtheline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:41:47 by fpaglia           #+#    #+#             */
/*   Updated: 2025/09/17 18:26:30 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>

/* Readline is an extensive software that has several builtin functionality
 * in shell completion. try using tab while on it.
 * the outcome of the tool should be injected in an history file 
 * to be later used with multiple command 
 * this small example shows a loop that saves content in an history file 
 * and return to the shell for a new input.
 * 
 * HOWEVER!!! the real program should be capable of recognizing if we are launching the shell 
 * in an interactive way requiring the readline to be active or if we 
 * are starting from a static input to be processed. */	
int main()
{
	char *str;
	int history = open(".shell_history", O_WRONLY | O_CREAT | O_APPEND, 0644);
	int tty = dup(1);
	while (1)
	{
	str = readline("prompt here% ");
	ft_putendl_fd(str, history);
	/* the dup2 approach here is presented for demonstration purpose, 
	 * a simple write does the work*/
	// dup2(history, 1);
	// printf("%s\n", str);
	// dup2(tty, 1);
	free(str);
	}
	return (0);
}
