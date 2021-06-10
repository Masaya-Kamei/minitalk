/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 18:04:38 by mkamei            #+#    #+#             */
/*   Updated: 2021/06/10 11:57:07 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	handler(int signum)
{
	g_received_signal = signum;
}

void	write_msg_and_exit(int num)
{
	const char	msgs[8][30] =
		{"Success\n", "Sigemptyset Error\n", "Sigaction Error\n",
		 "Arguments Error\n", "Invalid Client PID\n", "Kill Error\n",
		 "Malloc Error\n", "\nServer End\n"};

	if (num == SUCCESS || num == END_SERVER)
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

int	free_and_return(char *str, int status)
{
	free(str);
	return (status);
}

void	write_pid(int server_or_client, pid_t pid)
{
	if (server_or_client == SERVER)
	{
		write(1, "Server PID: ", 12);
		ft_putnbr_fd(pid, 1);
		write(1, "\n\n", 2);
	}
	else
	{
		write(1, "Client PID: ", 12);
		ft_putnbr_fd(pid, 1);
		write(1, "\n", 1);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	act;

	(void)(**argv);
	if (argc != 1)
		write_msg_and_exit(ERR_ARGUMENTS);
	act.sa_handler = handler;
	act.sa_flags = 0;
	if (sigemptyset(&act.sa_mask) != 0)
		write_msg_and_exit(ERR_SIGEMPTYSET);
	if (sigaction(SIGUSR1, &act, NULL) != 0)
		write_msg_and_exit(ERR_SIGACTION);
	if (sigaction(SIGUSR2, &act, NULL) != 0)
		write_msg_and_exit(ERR_SIGACTION);
	if (sigaction(SIGINT, &act, NULL) != 0)
		write_msg_and_exit(ERR_SIGACTION);
	write_pid(SERVER, getpid());
	loop_communication();
	return (0);
}
