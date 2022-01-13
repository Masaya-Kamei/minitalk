/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:35:38 by mkamei            #+#    #+#             */
/*   Updated: 2022/01/13 16:39:48 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	exit_with_errout(const char *errmsg)
{
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

static void	send_one_byte(const pid_t server_pid, const char c)
{
	int		bit_shift_num;
	int		send_signal;

	bit_shift_num = 7;
	while (bit_shift_num >= 0)
	{
		if ((c & (0b00000001 << bit_shift_num)) == 0)
			send_signal = SIGUSR1;
		else
			send_signal = SIGUSR2;
		if (kill(server_pid, send_signal) == -1)
			exit_with_errout(EMSG_KILL);
		while (g_received_signal == 0)
			usleep(10);
		if (g_received_signal != send_signal)
			exit_with_errout(EMSG_COMMUNICATION);
		g_received_signal = 0;
		bit_shift_num--;
	}
}

static void	send_string(const pid_t server_pid, const char *str)
{
	int		i;

	i = 0;
	while (1)
	{
		send_one_byte(server_pid, str[i]);
		if (str[i] == '\0')
			break ;
		i++;
	}
}

static void	siguser_handler(int signum)
{
	g_received_signal = signum;
}

int	main(const int argc, const char **argv)
{
	struct sigaction	act;
	pid_t				server_pid;

	if (argc != 3)
		exit_with_errout(EMSG_ARGUMENTS);
	server_pid = ft_atoi(argv[1]);
	if (server_pid < PID_MIN || server_pid > PID_MAX)
		exit_with_errout(EMSG_SERVER_PID);
	act.sa_handler = siguser_handler;
	act.sa_flags = 0;
	if (sigemptyset(&act.sa_mask) != 0)
		exit_with_errout(EMSG_SIGEMPTYSET);
	if (sigaction(SIGUSR1, &act, NULL) != 0)
		exit_with_errout(EMSG_SIGACTION);
	if (sigaction(SIGUSR2, &act, NULL) != 0)
		exit_with_errout(EMSG_SIGACTION);
	send_string(server_pid, argv[2]);
	return (0);
}
