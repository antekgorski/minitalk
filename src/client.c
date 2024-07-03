/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:09:24 by agorski           #+#    #+#             */
/*   Updated: 2024/07/03 16:04:14 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

int		server_reply = 0;

void	ack_handlerc(int sig)
{
	(void)sig;
	server_reply = 1;
}

void	ack_handler(int sig)
{
	(void)sig;
	server_reply = 1;
}
int	send_pid(pid_t server_pid, pid_t client_pid)
{
	int	i;
	int	bit_count;

	server_reply = 0;
	bit_count = sizeof(pid_t) * 8 - 1;
	while (bit_count >= 0)
	{
		if ((client_pid & (1 << bit_count)) != 0)
		{
			kill(server_pid, SIGUSR1);
			usleep(1000);
		}
		else
		{
			kill(server_pid, SIGUSR2);
			usleep(1000);
		}
		usleep(1000);
		bit_count--;
	}
	i = 0;
	while (!server_reply)
	{
		usleep(100);
		if (++i == 30000)
			return (write(1, "server don't recive\n", 20), 0);
	}
	if (server_reply == 1)
		ft_printf("Server received client PID: %d\n", client_pid);
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
			usleep(1000);
		}
		bit_count++;
	}
}

int	main(int ac, char **av)
{
	pid_t	server_pid;
	pid_t	client_pid;
	char	*message;

	if (ac == 3)
	{
		signal(SIGUSR1, ack_handler);
		signal(SIGUSR2, ack_handlerc);
		server_pid = ft_atoi(av[1]);
		client_pid = getpid();
		ft_printf("PID: %d\n", client_pid);
		send_pid(server_pid, client_pid);
		message = av[2];
		while (*message != '\0')
		{
			server_reply = 0;
			send_char(server_pid, *message);
			message++;
			while (!server_reply)
			{
				usleep(1000);
			}
		}
		// send_char(server_pid, '\n');
		send_char(server_pid, '\0');
	}
	else
	{
		write(1, "Error Try: ./client [server_pid] [message]\n", 43);
		return (1);
	}
	return (0);
}
