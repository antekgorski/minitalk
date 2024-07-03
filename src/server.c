/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:28:03 by agorski           #+#    #+#             */
/*   Updated: 2024/07/03 00:07:14 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include <stdio.h>

void	handle_signals(int signum)
{
	static int	character;
	static int	bit_count = sizeof(pid_t) * 8 - 1;
	static int	client_pid;
	static int	reciving_pid = 1;
	static int char_bit_count;

	if (reciving_pid)
	{
		if (signum == SIGUSR1)
			client_pid |= (1 << (bit_count--));
		if (signum == SIGUSR2)
			client_pid |= (0 << (bit_count--));
		if (bit_count < 0)
		{
			reciving_pid = 0;
			kill(client_pid, SIGUSR2);
			printf("Recived client PID: %d\n", client_pid);
			bit_count = sizeof(pid_t) * 8 - 1;
		}
	}
	else
	{
		if (signum == SIGUSR1)
			character |= (1 << char_bit_count++);
		if (signum == SIGUSR2)
			character |= (0 << char_bit_count++);
		if (char_bit_count == 8)
		{
			ft_printf("%c", character);
			char_bit_count = 0;
			character = 0;
		}
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	ft_printf("Waiting for message...\n");
	signal(SIGUSR1, handle_signals);
	signal(SIGUSR2, handle_signals);
	while (1)
	{
	}
	return (0);
}
