/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:40:44 by mkamei            #+#    #+#             */
/*   Updated: 2021/06/10 14:29:13 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	send_character(pid_t server_pid, char c, int is_acknowledgement)
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
			write_msg_and_exit(ERR_KILL);
		if (is_acknowledgement == 1)
		{
			while (g_received_signal == 0)
				usleep(10);
			if (g_received_signal != send_signal)
				write_msg_and_exit(ERR_COMMUNICATION);
			g_received_signal = 0;
		}
		else
			usleep(1000);
		bit_shift_num--;
	}
}

static void	send_string(pid_t server_pid, char *str, int is_acknowledgement)
{
	int		i;

	i = 0;
	while (1)
	{
		send_character(server_pid, str[i], is_acknowledgement);
		if (str[i] == '\0')
			break ;
		i++;
	}
}

static void	change_pid_type_from_int_to_string(int pid, char pid_str[])
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (pid != 0)
	{
		pid_str[i] = pid % 10 + '0';
		pid = pid / 10;
		i++;
	}
	pid_str[i] = '\0';
	j = 0;
	i--;
	while (i > j)
	{
		tmp = pid_str[j];
		pid_str[j++] = pid_str[i];
		pid_str[i--] = tmp;
	}
}

void	communicate_with_server(pid_t server_pid, char *str)
{
	char	client_pid_str[PID_MAX_DIGITS_NUM + 1];
	pid_t	client_pid;
	int		is_acknowledgement;

	client_pid = getpid();
	change_pid_type_from_int_to_string(client_pid, client_pid_str);
	g_received_signal = 0;
	is_acknowledgement = 0;
	send_string(server_pid, client_pid_str, is_acknowledgement);
	is_acknowledgement = 1;
	send_string(server_pid, str, is_acknowledgement);
	send_character(server_pid, ASCII_EOT, is_acknowledgement);
}
