/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:18:11 by agorski           #+#    #+#             */
/*   Updated: 2024/04/30 23:01:47 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_number_len(int number)
{
	int	len;

	len = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		len++;
	while (number != 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}

int	print_number(int number)
{
	ft_putnbr_fd(number, 1);
	return (ft_number_len(number));
}
