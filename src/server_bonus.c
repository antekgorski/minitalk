/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:19:04 by agorski           #+#    #+#             */
/*   Updated: 2024/07/04 16:56:25 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	get_pid(int *signum, int *bit_count, int *client_pid, int *reciving_pid)
{
	if (*signum == SIGUSR1)
		*client_pid |= (1 << ((*bit_count)--));
	if (*signum == SIGUSR2)
		*client_pid |= (0 << ((*bit_count)--));
	if (*bit_count < 0)
	{
		*reciving_pid = 0;
		kill(*client_pid, SIGUSR2);
		*bit_count = sizeof(pid_t) * 8 - 1;
	}
}
// ft_printf("Recived client PID: %d\n", *client_pid);

void	print_one_char(int *character, int *client_pid, int *reciving_pid,
		int *char_bit_count)
{
	if (*character == '\0')
	{
		*reciving_pid = 1;
		ft_printf("\n");
		kill(*client_pid, SIGUSR2);
		*client_pid = 0;
	}
	else
	{
		ft_printf("%c", *character);
		kill(*client_pid, SIGUSR2);
	}
	*char_bit_count = 0;
	*character = 0;
}

void	get_char(int *signum, int *char_bit_count, int *client_pid,
		int *reciving_pid)
{
	static int	character;

	if (*signum == SIGUSR1)
		character |= (1 << (*char_bit_count)++);
	if (*signum == SIGUSR1)
		kill(*client_pid, SIGUSR1);
	if (*signum == SIGUSR2)
		character |= (0 << (*char_bit_count)++);
	if (*signum == SIGUSR2)
		kill(*client_pid, SIGUSR1);
	if (*char_bit_count == 8)
		print_one_char(&character, client_pid, reciving_pid, char_bit_count);
}

void	handle_signals(int signum)
{
	static int	bit_count = sizeof(pid_t) * 8 - 1;
	static int	client_pid;
	static int	char_bit_count;
	static int	reciving_pid = 1;

	if (reciving_pid)
		get_pid(&signum, &bit_count, &client_pid, &reciving_pid);
	else
		get_char(&signum, &char_bit_count, &client_pid, &reciving_pid);
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

// #include "../inc/minitalk_bonus.h"

// void	handle_signals(int signum)
// {
// 	static int	character;
// 	static int	bit_count;

// 	if (signum == SIGUSR1)
// 	{
// 		character |= (1 << bit_count);
// 		bit_count++;
// 	}
// 	else if (signum == SIGUSR2)
// 	{
// 		character |= (0 << bit_count);
// 		bit_count++;
// 	}
// 	if (bit_count == 8)
// 	{
// 		ft_printf("%c", character);
// 		bit_count = 0;
// 		character = 0;
// 	}
// }

// int	main(void)
// {
// 	pid_t	pid;
// 	// struct sigaction sa;

// 	pid = getpid();
// 	ft_printf("PID: %d\n", pid);
// 	ft_printf("Waiting for message...\n");

// 	// sa.sa_handler = handle_signals;
// 	// sigemptyset(&sa.sa_mask);
// 	// sa.sa_flags = 0;
// 	// sigaction(SIGUSR1, &sa, NULL);
// 	// sigaction(SIGUSR2, &sa, NULL);

// 	signal(SIGUSR1, handle_signals);
// 	signal(SIGUSR2, handle_signals);
// 	while (1)
// 	{
// 	}
// 	return (0);
// }
