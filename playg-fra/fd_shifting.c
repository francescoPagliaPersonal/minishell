/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_shifting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:00:24 by fpaglia           #+#    #+#             */
/*   Updated: 2025/09/16 15:52:07 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int		fdin;
	int 	fdout;

    char    *str;
	char	*a = "a";
	
	/*some preliminary ideas to get the username on the shell together 
	 * with the current path */
	printf("%s::%s\n %%", getenv("USER"), getenv("PWD"));

	fdin = 0;
	/* created a new file that uses the following bitmasks for the options:
	 * O_WRONLY: open with the purpose to only write into it
	 * O_CREAT: create the file shall it not exists
	 * 0_APPEND: start from the last line do not allow for data overwrite.*/
	fdout = open("permute", O_WRONLY | O_CREAT | O_APPEND, 0644);
	/* mapped the new file to the stdout so the data is written there*/
	dup2(fdout, STDOUT_FILENO);
	str = a;
	while (str[0] != '~')
	{
		str = get_next_line(fdin);
		/*open the file defined above with tail -f permute notice at any new line
		 * the data is written in there*/
		printf("%s\n", str);
		if (str[0] != '~')
		{
	    	free(str);
			str = a;
		}
	}
	free(str);
	return (0);

}

