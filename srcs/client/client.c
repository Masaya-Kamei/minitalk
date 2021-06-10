/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 09:52:16 by mkamei            #+#    #+#             */
/*   Updated: 2021/06/09 20:15:55 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	handler(int signum)
{
	g_received_signal = signum;
}

void	write_msg_and_exit(int num)
{
	const char	msgs[7][30] =
		{"Success\n", "Sigemptyset Error\n", "Sigaction Error\n",
		 "Arguments Error\n", "Invalid Server PID\n", "Kill Error\n",
		 "Communication Error\n"};

	if (num == SUCCESS)
	{
		write(1, msgs[num], ft_strlen(msgs[num]));
		exit(0);
	}
	else
	{
		write(2, msgs[num], ft_strlen(msgs[num]));
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	act;
	pid_t				server_pid;

	if (argc != 3)
		write_msg_and_exit(ERR_ARGUMENTS);
	server_pid = ft_atoi(argv[1]);
	if (server_pid < PID_MIN || server_pid > PID_MAX)
		write_msg_and_exit(ERR_SERVER_PID);
	act.sa_handler = handler;
	act.sa_flags = 0;
	if (sigemptyset(&act.sa_mask) != 0)
		write_msg_and_exit(ERR_SIGEMPTYSET);
	if (sigaction(SIGUSR1, &act, NULL) != 0)
		write_msg_and_exit(ERR_SIGACTION);
	if (sigaction(SIGUSR2, &act, NULL) != 0)
		write_msg_and_exit(ERR_SIGACTION);
	communicate_with_server(server_pid, argv[2]);
	return (0);
}
