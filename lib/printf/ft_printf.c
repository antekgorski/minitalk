/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:40:09 by agorski           #+#    #+#             */
/*   Updated: 2024/07/01 18:46:32 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//#include <stdio.h>

static int	ft_print_sign(int imput, va_list ap)
{
	int	i;

	i = 0;
	if (imput == 'c')
		i = print_char(va_arg(ap, int));
	else if (imput == 's')
		i = print_string(va_arg(ap, char *));
	else if (imput == 'p')
		i = print_pointer(va_arg(ap, unsigned long long *));
	else if (imput == 'd' || imput == 'i')
		i = print_number(va_arg(ap, int));
	else if (imput == 'u')
		i = print_unsigned(va_arg(ap, unsigned int));
	else if (imput == 'x' || imput == 'X')
		i = print_hex(va_arg(ap, unsigned int), imput);
	return (i);
}

int	ft_printf(const char *imput, ...)
{
	va_list			ap;
	unsigned int	i;

	i = 0;
	va_start(ap, imput);
	while (*imput)
	{
		if (*imput == '%')
		{
			imput++;
			if (ft_strchr("cspdiuxX", *imput))
				i += ft_print_sign(*imput, ap);
			else if (*imput == '%')
				i += write(1, "%", 1);
		}
		else
			i += write(1, imput, 1);
		imput++;
	}
	va_end(ap);
	return (i);
}

// int	main(void)
//{
// int		k;
// void	*ptr1;
// void	*ptr2;
// int		i;
// int		j;

// unsigned int	l;
// ptr1 = &i;
// ptr2 = &j;
// l = 123456789;
// j = 235;
// i = 412;
// k = 0;
// k = ft_printf("123456789");
// k = ft_printf("1234567890qwertyuiopas %% %c dfghjklzxcvbnm", 'W');
// k = ft_printf("1234567890qwertyuiopas %s dfghjklzxcvbnm", "string12345");
// k = ft_printf("TESTtestTEST %x TESTtestTEST", i);
// k = ft_printf("TESTtestTEST %X TESTtestTEST", i);
// k = printf("TESTtestTEST %x TESTtestTEST", i);
// k = printf("TESTtestTEST %X TESTtestTEST", i);
// k = ft_printf("123 %d 123 %i", i, j);
// k = ft_printf("%u\n", -1);
// ft_printf("%i\n", k);
// k = printf("%u\n", -1);
// ft_printf("%i\n", k);
// k = ft_printf("123 %p 123 %p\t", ptr1, ptr2);
// write(1, "\t", 1);
// ft_printf("%i\n", k);
// k = printf("123 %p 123 %p\t", ptr1, ptr2);
// write(1, "\t", 1);
// printf("%i\n", k);
// return (0);
//}