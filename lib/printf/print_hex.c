/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:50:11 by agorski           #+#    #+#             */
/*   Updated: 2024/04/30 16:16:12 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_hex(unsigned long int ap, char *template, int len)
{
	if (ap <= 15)
		len += print_char(template[ap % 16]);
	else
	{
		len = ft_print_hex(ap / 16, template, len);
		len += print_char(template[ap % 16]);
	}
	return (len);
}

int	print_hex(unsigned long int ap, int imput)
{
	char	*template;

	if (imput == 'x')
		template = "0123456789abcdef";
	else
		template = "0123456789ABCDEF";
	return (ft_print_hex(ap, template, 0));
}
