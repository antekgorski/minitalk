/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:55:54 by agorski           #+#    #+#             */
/*   Updated: 2024/04/08 21:14:25 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_occurrence;

	last_occurrence = s;
	while (*s++ != '\0')
	{
		if (*s == (char)c)
			last_occurrence = s;
	}
	if (*last_occurrence != (char)c && (char)c != '\0')
		return (NULL);
	return ((char *)last_occurrence);
}
