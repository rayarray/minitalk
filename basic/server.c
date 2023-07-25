/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:44:22 by rleskine          #+#    #+#             */
/*   Updated: 2023/03/15 17:34:30 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static unsigned char	*g_msg;

int	printmsg(int *size, int *mask)
{
	if (*mask > 0)
	{
		g_msg++;
		*g_msg = 0;
		*(g_msg + 1) = 0;
		(*mask)--;
	}
	if (*mask == 0)
	{
		g_msg = g_msg - *size;
		write(1, g_msg, *size);
		free(g_msg);
		g_msg = 0;
		*size = 0;
		*mask = 0;
	}
	return (0);
}

int	helper(int signo)
{
	static int	size;
	static int	mask;

	if (signo == 0)
		return (size + 1);
	if (signo == -1)
		return (printmsg(&size, &mask));
	if (mask < 1 && signo == SIGUSR2)
		mask--;
	else if (mask < 1)
		mask = -mask;
	else
	{
		size += (signo - 30);
		mask--;
		if (mask > 0)
			size = size << 1;
		else
		{
			mask = size;
			return (1);
		}
	}
	return (0);
}

int	main(void)
{
	extern void			handler();
	struct sigaction	act;
	sigset_t			set;

	ft_printf("Server PID is %d\n", (int)getpid());
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	act.sa_flags = 0;
	act.sa_mask = set;
	act.sa_handler = &handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		;
}

void	handler(int signo)
{
	if (g_msg)
	{
		if (signo == SIGUSR2)
			(*g_msg)++;
		if ((*(g_msg + 1))++ < 7)
			*g_msg = *g_msg << 1;
		if (*(g_msg + 1) == 8)
			helper(-1);
	}
	else if (helper(signo))
	{
		g_msg = (unsigned char *)malloc(sizeof(unsigned char) * helper(0));
		if (!g_msg)
			exit(-1);
		ft_bzero(g_msg, helper(0));
	}
}
