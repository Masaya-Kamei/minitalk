/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 18:03:25 by mkamei            #+#    #+#             */
/*   Updated: 2021/06/10 12:07:04 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "../libft/libft.h"
# include <signal.h>

# define PID_MIN 100
# define PID_MAX 99998
# define ASCII_EOT 4
# define BUFFER_SIZE 100
# define SERVER 0
# define CLIENT 1
# define SUCCESS 0
# define ERR_SIGEMPTYSET 1
# define ERR_SIGACTION 2
# define ERR_ARGUMENTS 3
# define ERR_CLIENT_PID 4
# define ERR_KILL 5
# define ERR_MALLOC 6
# define END_SERVER 7
# define END_COMMUNICATION 8

void	write_msg_and_exit(int num);
int		free_and_return(char *str, int status);
void	write_pid(int server_or_client, pid_t pid);
void	loop_communication(void);

int		g_received_signal;

#endif
