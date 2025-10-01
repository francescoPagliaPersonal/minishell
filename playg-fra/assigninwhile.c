/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigninwhile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:08:52 by fpaglia           #+#    #+#             */
/*   Updated: 2025/09/19 15:14:24 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <aio.h>

int	main(void)
{
	pid_t	pid;
	int		status;

	pid = 1;
	while (pid > 0)
	{
		pid = waitpid(-1, &status, WNOHANG);
		write(1, "print", 5);
	}
	return (0);
}
