/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cur_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 06:18:40 by fpaglia           #+#    #+#             */
/*   Updated: 2025/09/13 06:30:36 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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
	char *wd;
	char *buf;
	
	wd = getcwd(buf, 256); 
	write(1, wd, mylen(wd));
	write(1, "\n", 1);
	write (1, buf, mylen(buf));
	return (0);
}
