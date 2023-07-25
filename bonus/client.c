/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:27:13 by rleskine          #+#    #+#             */
/*   Updated: 2023/03/16 10:40:21 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft.h"
#include "ft_printf.h"

void	print_8k(void)
{
	char	*s;

	s = "8k";
	write(1, s, 2);
}

void	sig_wait(int pid, int signo, int wait)
{
	usleep(wait);
	kill(pid, signo);
	pause();
}

void	send_msg(int s_pid, char *msg, int bitshift, int i)
{
	unsigned char	txchar;

	while (bitshift >> i > 0 && ++i)
		sig_wait(s_pid, SIGUSR2, 25);
	sig_wait(s_pid, SIGUSR1, 75);
	while (i)
		if (bitshift >> --i & 1)
			sig_wait(s_pid, SIGUSR2, 25);
	else
		sig_wait(s_pid, SIGUSR1, 25);
	usleep(250);
	while (*msg)
	{
		bitshift = 8;
		txchar = *msg;
		while (bitshift)
		{
			if ((txchar >> --bitshift) & 1)
				sig_wait(s_pid, SIGUSR2, 20);
			else
				sig_wait(s_pid, SIGUSR1, 20);
		}
		msg++;
	}
}

int	main(int ac, char **ag)
{
	int					s_pid;
	extern void			handler();
	struct sigaction	act;
	sigset_t			set;

	if (ac > 1)
		s_pid = atoi(*(ag + 1));
	if (ac > 3)
		ft_printf("Too many parameters!\n");
	if (ac != 3 || s_pid < 1)
		return (ft_printf("Usage %s pid message\n\tWhere pid is process id of"
				"server process and message is the message to send, "
				"use quotes if necessary\n", *ag));
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	act.sa_flags = 0;
	act.sa_mask = set;
	act.sa_handler = &handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	send_msg(s_pid, *(ag + 2), ft_strlen(*(ag + 2)), 0);
	pause();
}

void	handler(int signo, siginfo_t *info, void *context)
{
	static int	status;

	(void)context;
	if (signo == SIGUSR1 && (status == 1 || status == 3))
	{
		print_8k();
		status = 2;
	}
	else if (signo == SIGUSR2 && (status == 0 || status == 2))
		status++;
	else if (signo == SIGUSR2 && (status == 1 || status == 3))
	{
		if (status == 3)
			ft_printf("\n");
		ft_printf("Server (pid %d) acknowledged message sent\n", info->si_pid);
	}
}
