/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:20:44 by agorski           #+#    #+#             */
/*   Updated: 2024/04/30 23:36:54 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer(void *ptr)
{
	int		len;
	char	x;

	len = 0;
	x = 'x';
	if (!ptr)
		return (write(1, "(nil)", 5));
	len += write(1, "0x", 2);
	len += print_hex((unsigned long int)ptr, x);
	return (len);
}
