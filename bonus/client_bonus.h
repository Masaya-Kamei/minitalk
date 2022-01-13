/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:32:47 by mkamei            #+#    #+#             */
/*   Updated: 2022/01/13 17:46:32 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_BONUS_H
# define CLIENT_BONUS_H

# include "libft.h"
# include <signal.h>

# define PID_MIN 100
# define PID_MAX 99998

# define EMSG_SIGEMPTYSET "Sigemptyset Error"
# define EMSG_SIGACTION "Sigaction Error"
# define EMSG_KILL "Kill Error"
# define EMSG_ARGUMENTS "Arguments Error"
# define EMSG_SERVER_PID "Invalid Server PID"
# define EMSG_COMMUNICATION "Communication Error"

static int	g_received_signal = 0;

#endif
