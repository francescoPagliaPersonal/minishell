#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

enum e_n
{
	OUT,
	PIPE,
	BACKGROUND
};

typedef struct s_proc
{
	int			id;
	pid_t		cpid;
	enum e_n	go_to;
	char		*stdin_f;
	char		*stdout_f;
	int			fd_io[2];
	char		**prog;
	int			status;
} t_proc;

typedef struct s_shell
{
	char	*prompt;
	int		count;
	t_proc	*item;
	char	**sy_env;
	char	**paths;
	int		last_command;

} t_shell;


void prova1(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	printf("SIGUSR1 sent by: %d\n", info->si_pid);
}

void prova2(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	printf("SIGUSR2 sent by: %d\n", info->si_pid);
}
void set_sig_mask(struct sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sigaddset(&sa->sa_mask, SIGUSR2);
	sigaddset(&sa->sa_mask, SIGUSR1);
}

/* The signal handler can be accoumulated using  the same structure  
 * no need to have one struct per handler at all.
 * the result is demonstrated by this software, the sa_sigaction is getting 
 * modified for by each handler the moment it's reassigned.
 * in practice the sig action is a table (a struct) and each time the function
 * is called is updating the values of the handler.
 * so by doing: 
 * sa_sigaction=handler1 
 * sigaction(this_signal, struct, old struct)
 * the handler for this_signal will be set to handler1
 * if furthermore sa_sigaction=handler2 will be defined it will need to be
 * associated to the a different signal usign again the sigaction function
 * withouth that the handler2 will never be used for anything.
 */
void init_signals(struct sigaction *sa)
{
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = prova1;
	sigaction(SIGUSR1, sa, NULL);
	sa->sa_sigaction = prova2;
	sigaction(SIGUSR2, sa, NULL);
	set_sig_mask(sa);
}

int main(int ac, char **av, char **env)
{
	t_shell data;
	struct sigaction sa;

	
	printf("mypid: %d\n", getpid());
	init_signals(&sa);
	while (1)
	{
		pause();
	
	/* sa.sa_mask = List all the signal we want to block while a process is running */
	
	// if (collect_data(data))
	// 	process_data(data);
	// else clean(data);	
	}
}
