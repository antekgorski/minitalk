/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:09:24 by agorski           #+#    #+#             */
/*   Updated: 2024/07/02 21:09:52 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

volatile sig_atomic_t	server_reply = 0;

void	ack_handler(int sig)
{
	(void)sig;
	server_reply = 1;
}
int	send_pid(pid_t server_pid, pid_t client_pid)
{
	int	i;
	int	bit_count;

	bit_count = sizeof(pid_t) * 8 - 1;
	while (bit_count >= 0)
	{
		if ((client_pid & (1 << bit_count)) != 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(1000);
		bit_count--;
	}
	server_reply = 0;
	i = 0;
	while (!server_reply)
	{
		usleep(100);
		if (++i == 30000)
			return (write(1, "server don't recive\n", 20), 0);
	}
	if (server_reply == 1)
		return (ft_printf("Server received client PID: %d\n", client_pid), 1);
	return (0);
}

void	send_char(pid_t server_pid, char c)
{
	int	bit_count;

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
	pid_t	client_pid;
	char	*message;

	signal(SIGUSR2, ack_handler);
	signal(SIGUSR1, ack_handler);
	server_pid = ft_atoi(av[1]);
	client_pid = getpid();
	ft_printf("PID: %d\n", client_pid);
	if (ac == 3 && (send_pid(server_pid, client_pid)))
	{
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
		write(1, "Error Try: ./client [server_pid] [message]\n", 43);
		return (1);
	}
	pause();
	return (0);
}
