/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:28:03 by agorski           #+#    #+#             */
/*   Updated: 2024/07/01 14:11:25 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signals(int signum)
{
	static int	character;
	static int	bit_count;

	if (signum == SIGUSR1)
	{
		character |= (1 << bit_count);
		bit_count++;
	}
	else if (signum == SIGUSR2)
	{
		character |= (0 << bit_count);
		bit_count++;
	}
	if (bit_count == 8)
	{
		ft_printf("%c", character);
		bit_count = 0;
		character = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

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
