/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:35:19 by mkamei            #+#    #+#             */
/*   Updated: 2022/01/13 17:46:20 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BONUS_H
# define SERVER_BONUS_H

# include "libft.h"
# include <signal.h>

# define EMSG_SIGEMPTYSET "Sigemptyset Error"
# define EMSG_SIGACTION "Sigaction Error"
# define EMSG_KILL "Kill Error"
# define EMSG_ARGUMENTS "Arguments Error"

static int	g_received_signal = 0;
static int	g_client_pid = 0;

#endif
