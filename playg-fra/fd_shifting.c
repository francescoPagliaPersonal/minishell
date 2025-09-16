/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_shifting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:00:24 by fpaglia           #+#    #+#             */
/*   Updated: 2025/09/16 14:24:35 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd;
	char buff[200];

	fd = open("permute", O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	printf("the new fd is: %d  ", fd);
	while (*buff != '~')
	{
		read(0, buff, 128);
		printf("%s", buff);
	}
//	printf("|  I'm writing something to the new file!\n");
	close(fd);
	return (0);

}
