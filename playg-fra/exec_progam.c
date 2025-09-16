/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_progam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:34:29 by fpaglia           #+#    #+#             */
/*   Updated: 2025/09/16 13:00:44 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	char	**argv;
	int		i = -1;
	pid_t	pid, subproc;
	int		status = 0;

	/*Simulating 2 commands where the management of the parameter is different*/
	argv = (char **)malloc(6 * sizeof(char *));
	
	argv[0] = strdup("ls");
	argv[1] = strdup("-a");
	/* Using a tilde the program gives back an error but if running in the shell would be ok
	argv[2] = strdup("~");*/
	argv[2] = strdup("/");
	argv[3] = strdup("-l");
	argv[4] = strdup("-s");
	argv[5] = NULL; 

	/*display the content of the environment that is an extern variable filled by the system*/
	while (__environ[++i] != NULL)
		printf("%s\n", __environ[i]);

	i = -1;
	while (argv[++i] != NULL)
		printf("%s\n", argv[i]); 

	pid = getpid();
	printf("main program pid  : %d\n", pid);
	/* with fork we open a subprocess that is referred by pid in the parent and is 
	 * recognized as 0 in the child */	
	pid	= fork();
	printf("return of fork pid: %d", pid);
	/* the child see itself as == 0 and start the execution of the task given */
	if (pid == 0)
		execve("/bin/ls", argv, __environ);
	/* the parents observe the status of the child over time to understand how to 
	 * proceed with the result */
	else
	{
		/* while the two macros return 0 > meaning the process is not finished
		 * nor has not been closed by a signal*/
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			/*check the value of the subprocess with the options of not beeing traced
			 * have been flagged to continue due to a sigstop/ sigcont process */
			subproc = waitpid(pid, &status, WUNTRACED | WCONTINUED);
			if (subproc == -1)
			{
				printf("Err \n");
				exit(EXIT_FAILURE);
			}
			/* If the subprocess didn't fail evaluate the status of the sbprocess ends
			 * check against the litteral different macros which confirm the reason of 
			 * the exit */
			if (WIFEXITED(status)) 
				printf("exited, status=%d\n", WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				printf("killed by signal %d\n", WTERMSIG(status));
			else if (WIFSTOPPED(status))
				printf("stopped by signal %d\n", WSTOPSIG(status));
			else if (WIFCONTINUED(status))
				printf("continued\n");
		}
		exit(EXIT_SUCCESS);
	}
	return (0);
}
