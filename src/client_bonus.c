/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:18:15 by agorski           #+#    #+#             */
/*   Updated: 2024/07/04 16:50:59 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static int	g_reply_bit_char[2];

void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		g_reply_bit_char[0] = 1;
	}
	else if (sig == SIGUSR2)
	{
		g_reply_bit_char[1] = 1;
	}
}

int	send_pid(pid_t server_pid, pid_t client_pid)
{
	int	i;
	int	bit_count;

	g_reply_bit_char[0] = 0;
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
	i = 0;
	while (g_reply_bit_char[1] == 0)
	{
		usleep(100);
		if (++i == 30000)
			return (ft_printf("server don't recive\n"), 0);
	}
	if (g_reply_bit_char[1] == 1)
		ft_printf("Server received client PID: %d\n", client_pid);
	return (0);
}

void	send_char(pid_t server_pid, char c)
{
	static int	bit_count;

	bit_count = 0;
	while (bit_count < 8)
	{
		g_reply_bit_char[0] = 0;
		if ((c & (1 << bit_count)) != 0)
			kill(server_pid, SIGUSR1);
		else if ((c & (0 << bit_count)) == 0)
			kill(server_pid, SIGUSR2);
		while (g_reply_bit_char[0] == 0)
		{
			usleep(1000);
		}
		bit_count++;
	}
}

void	send_msg(char *message, int server_pid)
{
	while (*message != '\0')
	{
		g_reply_bit_char[1] = 0;
		send_char(server_pid, *message);
		while (g_reply_bit_char[1] == 0)
			usleep(10);
		message++;
	}
}

int	main(int ac, char **av)
{
	pid_t	server_pid;
	pid_t	client_pid;

	if (ac == 3)
	{
		signal(SIGUSR1, ack_handler);
		signal(SIGUSR2, ack_handler);
		server_pid = ft_atoi(av[1]);
		client_pid = getpid();
		ft_printf("PID: %d\n", client_pid);
		send_pid(server_pid, client_pid);
		send_msg(av[2], server_pid);
		g_reply_bit_char[0] = 0;
		send_char(server_pid, '\0');
		if (g_reply_bit_char[1] == 1)
		{
			ft_printf("message delivered and printed by the server\n");
			g_reply_bit_char[0] = 0;
		}
	}
	else
		return ((write(1, "Try: ./client [server_pid] [message]\n", 37)), 0);
	return (0);
}

// #include "../inc/minitalk_bonus.h"

// void	send_char(pid_t server_pid, char c)
// {
// 	int	bit_count;

// 	bit_count = 0;
// 	while (bit_count < 8)
// 	{
// 		if ((c & (1 << bit_count)) != 0)
// 			kill(server_pid, SIGUSR1);
// 		else
// 			kill(server_pid, SIGUSR2);
// 		usleep(100);
// 		bit_count++;
// 	}
// }

// int	main(int ac, char **av)
// {
// 	pid_t	pid;
// 	char	*message;

// 	if (ac == 3)
// 	{
// 		pid = ft_atoi(av[1]);
// 		message = av[2];
// 		while (*message != '\0')
// 		{
// 			send_char(pid, *message);
// 			message++;
// 		}
// 		send_char(pid, '\n');
// 	}
// 	else
// 	{
// 		write(1, "Error\nTry: ./client [server_pid] [message]\n", 43);
// 		return (1);
// 	}
// 	return (0);
// }
