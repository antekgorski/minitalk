/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:39:53 by agorski           #+#    #+#             */
/*   Updated: 2024/03/20 14:28:25 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*costr;

	if (!s1 || !s2)
		return (NULL);
	costr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (costr == NULL)
		return (NULL);
	ft_strlcpy(costr, (char *)s1, (ft_strlen(s1) + 1));
	ft_strlcat(costr, (char *)s2, (ft_strlen(s1) + ft_strlen(s2) + 1));
	return (costr);
}
