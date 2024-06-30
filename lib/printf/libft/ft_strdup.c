/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:22:14 by agorski           #+#    #+#             */
/*   Updated: 2024/04/04 16:46:16 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;

	new = malloc(ft_strlen(s) + 1);
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, (char *)s, ft_strlen(s) + 1);
	return (new);
}
