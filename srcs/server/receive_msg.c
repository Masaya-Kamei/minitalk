/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 11:55:10 by mkamei            #+#    #+#             */
/*   Updated: 2021/06/10 12:55:24 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	receive_character(char *c, pid_t client_pid)
{
	int		bit_shift_count;
	int		signal;

	*c = 0;
	bit_shift_count = 0;
	while (bit_shift_count < 8)
	{
		while (g_received_signal == 0)
			usleep(10);
		signal = g_received_signal;
		g_received_signal = 0;
		*c <<= 1;
		if (signal == SIGINT)
			return (END_SERVER);
		else if (signal == SIGUSR2)
			(*c)++;
		if (client_pid != 0)
		{
			if (kill(client_pid, signal) == -1)
				return (ERR_KILL);
		}
		bit_shift_count++;
	}
	return (SUCCESS);
}

static char	*strjoin_str_and_buf(char *str, char *buf)
{
	char	*tmp;

	buf[BUFFER_SIZE] = '\0';
	tmp = ft_strjoin(str, buf);
	free(str);
	str = tmp;
	return (str);
}

static int	receive_string(char **str, pid_t client_pid)
{
	char	buf[BUFFER_SIZE + 1];
	int		i;
	int		status;

	i = 0;
	*str = ft_strdup("");
	if (*str == NULL)
		return (ERR_MALLOC);
	while (1)
	{
		status = receive_character(&buf[i], client_pid);
		if (status == ERR_KILL || status == END_SERVER)
			return (free_and_return(*str, status));
		if (buf[i] == ASCII_EOT)
			return (free_and_return(*str, END_COMMUNICATION));
		else if (buf[i] == '\0' || i + 1 == BUFFER_SIZE)
		{
			*str = strjoin_str_and_buf(*str, buf);
			if (*str == NULL)
				return (ERR_MALLOC);
			if (buf[i] == '\0')
				return (SUCCESS);
		}
		i = (i + 1) % BUFFER_SIZE;
	}
}

static int	receive_client_pid(pid_t *client_pid)
{
	char	*client_pid_str;
	int		status;

	*client_pid = 0;
	status = receive_string(&client_pid_str, *client_pid);
	if (status == ERR_MALLOC || status == ERR_KILL || status == END_SERVER)
		write_msg_and_exit(status);
	else if (status == END_COMMUNICATION)
		return (END_COMMUNICATION);
	*client_pid = ft_atoi(client_pid_str);
	free(client_pid_str);
	if (*client_pid < PID_MIN || *client_pid > PID_MAX)
		write_msg_and_exit(ERR_CLIENT_PID);
	return (SUCCESS);
}

void	loop_communication(void)
{
	pid_t	client_pid;
	char	*str;
	int		status;

	while (1)
	{
		g_received_signal = 0;
		status = receive_client_pid(&client_pid);
		if (status == END_COMMUNICATION)
			continue ;
		write_pid(CLIENT, client_pid);
		while (1)
		{
			status = receive_string(&str, client_pid);
			if (status == ERR_MALLOC
				|| status == ERR_KILL || status == END_SERVER)
				write_msg_and_exit(status);
			else if (status == END_COMMUNICATION)
				break ;
			ft_putendl_fd(str, 1);
			free(str);
		}
		write(1, "--- Communication end\n\n", 23);
	}
}
