/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:09:24 by agorski           #+#    #+#             */
/*   Updated: 2024/07/02 11:29:19 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

volatile sig_atomic_t	server_reply = 0;

void	ack_handler(int sig)
{
	server_reply = 1; // Ustaw flagę na 1 po otrzymaniu potwierdzenia
}
void send_pid(pid_t server_pid, pid_t client_pid)
{
	int bit_count;
	bit_count = sizeof(pid_t) * 8 - 1;
	signal(SIGUSR1, ack_handler);
	while(bit_count >= 0)
	{
		if((client_pid & (1 <<bit_count)) != 0)
			kill(client_pid, SIGUSR1);
			else
			kill(client_pid, SIGUSR2);
			usleep(1000);
			bit_count--;
	}
	server_reply = 0;
	while(!server_reply)
	{
		usleep(100);
	}
	if(server_reply == 1)
	ft_printf("the server received the client PID: %d\n", client_pid);
}

void	send_char(pid_t server_pid, char c)
{
	int	bit_count;

	signal(SIGUSR2, ack_handler);
	bit_count = 0;
	while (bit_count < 8)
	{
		server_reply = 0;
		if ((c & (1 << bit_count)) != 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		while (!server_reply)
		{
			usleep(100);
		}
		bit_count++;
	}
}

int	main(int ac, char **av)
{
	pid_t	server_pid;
	char	*message;

	if (ac == 3)
	{
		server_pid = ft_atoi(av[1]);
		message = av[2];
		while (*message != '\0')
		{
			send_char(server_pid, *message);
			message++;
		}
		send_char(server_pid, '\n');
	}
	else
	{
		write(1, "Error\nTry: ./client [server_pid] [message]\n", 43);
		return (1);
	}
	return (0);
}
