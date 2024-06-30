/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:38:13 by agorski           #+#    #+#             */
/*   Updated: 2024/04/30 23:27:26 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(char *s)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (write(1, "(null)", 6));
	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}
