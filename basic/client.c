/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:27:13 by rleskine          #+#    #+#             */
/*   Updated: 2023/03/16 10:39:18 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft.h"
#include "ft_printf.h"

#ifndef WAIT_TIME
# define WAIT_TIME		160
#endif

void	sig_wait(int pid, int signo, int wait)
{
	kill(pid, signo);
	usleep(wait);
}

void	send_msg(char *msg, int s_pid, unsigned char txchar)
{
	int	bitshift;

	usleep(WAIT_TIME * 6);
	while (*msg)
	{
		bitshift = 8;
		txchar = *msg;
		while (bitshift)
		{
			if ((txchar >> --bitshift) & 1)
				sig_wait(s_pid, SIGUSR2, WAIT_TIME);
			else
				sig_wait(s_pid, SIGUSR1, WAIT_TIME);
		}
		usleep(WAIT_TIME * 2);
		msg++;
	}
}

int	main(int ac, char **ag)
{
	char			*msg;
	int				s_pid;
	int				bitshift;

	if (ac > 1)
		s_pid = atoi(*(ag + 1));
	if (ac != 3 || s_pid < 1)
		return (ft_printf("Usage %s pid message\n\tWhere pid is process id of"
				"server process and message is the message to send, "
				"use quotes if necessary\n", *ag));
	msg = *(ag + 2);
	bitshift = ft_strlen(msg);
	ac = 0;
	while (bitshift >> ac > 0 && ++ac)
		sig_wait(s_pid, SIGUSR2, WAIT_TIME);
	sig_wait(s_pid, SIGUSR1, WAIT_TIME * 2);
	while (ac)
	{
		if (bitshift >> --ac & 1)
			sig_wait(s_pid, SIGUSR2, WAIT_TIME);
		else
			sig_wait(s_pid, SIGUSR1, WAIT_TIME);
	}
	send_msg(msg, s_pid, 0);
}
