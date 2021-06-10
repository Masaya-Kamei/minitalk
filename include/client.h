/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:53:18 by mkamei            #+#    #+#             */
/*   Updated: 2021/06/10 11:39:42 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "../libft/libft.h"
# include <signal.h>

# define PID_MIN 100
# define PID_MAX 99998
# define PID_MAX_DIGITS_NUM 5
# define ASCII_EOT 4
# define SUCCESS 0
# define ERR_SIGEMPTYSET 1
# define ERR_SIGACTION 2
# define ERR_ARGUMENTS 3
# define ERR_SERVER_PID 4
# define ERR_KILL 5
# define ERR_COMMUNICATION 6

void	write_msg_and_exit(int num);
void	communicate_with_server(pid_t server_pid, char *str);

int		g_received_signal;

#endif
