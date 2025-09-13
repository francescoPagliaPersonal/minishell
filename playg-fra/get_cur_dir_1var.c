/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cur_dir_1var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 06:18:40 by fpaglia           #+#    #+#             */
/*   Updated: 2025/09/13 06:37:00 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int mylen(char *str)
{
	int i;
	
	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\0')
		i++;
	return (i);
}

int main()
{
	char *buf;
	buf = (char *)malloc(256 * sizeof(char));
	getcwd(buf, 256); 
	write (1, buf, mylen(buf));
	if (buf)
		free(buf);
	return (0);
}
