/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:21:05 by mkamei            #+#    #+#             */
/*   Updated: 2022/01/13 17:46:48 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

static void	exit_with_errout(const char *errmsg)
{
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

static char	receive_one_byte(void)
{
	char	c;
	int		bit_shift_count;
	int		signal;

	c = 0;
	bit_shift_count = 0;
	while (bit_shift_count < 8)
	{
		while (g_received_signal == 0)
			usleep(10);
		signal = g_received_signal;
		g_received_signal = 0;
		c <<= 1;
		if (signal == SIGUSR2)
			c++;
		bit_shift_count++;
		if (kill(g_client_pid, signal) == -1)
			exit_with_errout(EMSG_KILL);
	}
	return (c);
}

static void	receive_string(void)
{
	char	c;

	while (1)
	{
		c = receive_one_byte();
		if (c == '\0')
			break ;
		write(STDOUT_FILENO, &c, 1);
	}
	write(STDOUT_FILENO, "\n--- [", 6);
	ft_putnbr_fd(g_client_pid, 1);
	write(STDOUT_FILENO, "] Communication end ---\n\n", 25);
}

static void	siguser_handler(int signum, siginfo_t *siginfo, void *ucontext)
{
	(void)*ucontext;
	g_client_pid = siginfo->si_pid;
	g_received_signal = signum;
}

int	main(const int argc, const char **argv)
{
	struct sigaction	act;

	(void)(**argv);
	if (argc != 1)
		exit_with_errout(EMSG_ARGUMENTS);
	act.sa_sigaction = siguser_handler;
	act.sa_flags = 0;
	if (sigemptyset(&act.sa_mask) != 0)
		exit_with_errout(EMSG_SIGEMPTYSET);
	if (sigaction(SIGUSR1, &act, NULL) != 0)
		exit_with_errout(EMSG_SIGACTION);
	if (sigaction(SIGUSR2, &act, NULL) != 0)
		exit_with_errout(EMSG_SIGACTION);
	write(STDOUT_FILENO, "Server PID: ", 12);
	ft_putnbr_fd(getpid(), 1);
	write(STDOUT_FILENO, "\n\n", 2);
	while (1)
		receive_string();
	return (0);
}
