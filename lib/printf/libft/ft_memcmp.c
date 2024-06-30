/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:05:30 by agorski           #+#    #+#             */
/*   Updated: 2024/03/18 22:58:07 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*exts1;
	const unsigned char	*exts2;

	exts1 = (const unsigned char *)s1;
	exts2 = (const unsigned char *)s2;
	while (n != 0)
	{
		if (*exts1 != *exts2)
		{
			return (*exts1 - *exts2);
		}
		exts1++;
		exts2++;
		n--;
	}
	return (0);
}
