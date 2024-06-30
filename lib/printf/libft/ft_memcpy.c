/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:50:12 by agorski           #+#    #+#             */
/*   Updated: 2024/03/18 23:04:08 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_temp;
	const char	*src_temp;

	dest_temp = dest;
	src_temp = src;
	if (!dest && !src)
		return (dest);
	while (n--)
	{
		*dest_temp++ = *src_temp++;
	}
	return (dest);
}
