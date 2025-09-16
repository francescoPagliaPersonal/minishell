/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_progam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:34:29 by fpaglia           #+#    #+#             */
/*   Updated: 2025/09/16 11:24:32 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{
	char	**argv;
	char	**argv2;
	int		i = -1;

	/*Simulating 2 commands where the management of the parameter is different*/
	argv = (char **)malloc(4 * sizeof(char *));
	argv2 = (char **)malloc(6 * sizeof(char *));
	
	argv[0] = strdup("ls");
	argv[1] = strdup("-als");
	argv[2] = strdup("/");
	argv[3] = NULL;
	
	argv2[0] = strdup("ls");
	argv2[1] = strdup("-a");
	argv2[2] = strdup("~");
	argv2[3] = strdup("-l");
	argv2[4] = strdup("-s");
	argv2[5] = NULL; 

	/*display the content of the environment that is an extern variable filled by the system*/
	while (__environ[++i] != NULL)
		printf("%s\n", __environ[i]);

	i = -1;
	while (argv[++i] != NULL)
		printf("%s\n", argv[i]); 
		
	execve("/bin/ls", argv, __environ);

	/* this second process is not running as wel as the main program seems not relevant anymore*/
	execve("/bin/ls", argv2, __environ);
	return (0);
}
