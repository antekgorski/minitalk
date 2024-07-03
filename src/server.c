/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:28:03 by agorski           #+#    #+#             */
/*   Updated: 2024/07/03 16:27:32 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	handle_signals(int signum)
{
	static int	character;
	static int	bit_count = sizeof(pid_t) * 8 - 1;
	static int	client_pid;
	static int	char_bit_count;
	static int	reciving_pid = 1;

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
			ft_printf("Recived client PID: %d\n", client_pid);
			bit_count = sizeof(pid_t) * 8 - 1;
		}
	}
	else
	{
		if (signum == SIGUSR1)
		{
			character |= (1 << char_bit_count++);
			kill(client_pid, SIGUSR1);
		}
		if (signum == SIGUSR2)
		{
			character |= (0 << char_bit_count++);
			kill(client_pid, SIGUSR1);
		}
		if (char_bit_count == 8)
		{
			if (character == '\0')
			{
				reciving_pid = 1;
				client_pid = 0;
				ft_printf("\n");
			}
			else
			{
				ft_printf("%c", character);
				kill(client_pid, SIGUSR2);
			}
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
