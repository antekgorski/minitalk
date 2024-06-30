/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:56:49 by agorski           #+#    #+#             */
/*   Updated: 2024/04/08 21:27:53 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if ((big == NULL) && (len == 0))
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	while (*big && len)
	{
		while (*(little + i) == *(big + i) && (i < len) && *(little + i))
		{
			if (*(little + i + 1) == '\0')
				return ((char *)big);
			i++;
		}
		big++;
		len--;
	}
	return (NULL);
}
