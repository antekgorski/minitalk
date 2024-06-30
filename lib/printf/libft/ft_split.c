/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agorski <agorski@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:07:58 by agorski           #+#    #+#             */
/*   Updated: 2024/04/08 21:43:55 by agorski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_initvar(size_t *index, int *word_index, int *start_of_word)
{
	*index = 0;
	*word_index = 0;
	*start_of_word = -1;
}

static void	*ft_free_words(char **words, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(words[i++]);
	free(words);
	return (NULL);
}

static char	*ft_fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = 0;
	return (word);
}

static int	ft_word_count(const char *str, char c)
{
	int	count;
	int	trigger;

	count = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (count);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	index;
	int		word_index;
	int		start_of_word;

	ft_initvar(&index, &word_index, &start_of_word);
	result = ft_calloc((ft_word_count(s, c) + 1), sizeof(char *));
	if (!result)
		return (NULL);
	while (index <= ft_strlen(s))
	{
		if (s[index] != c && start_of_word < 0)
			start_of_word = index;
		else if ((s[index] == c || index == ft_strlen(s)) && start_of_word >= 0)
		{
			result[word_index] = ft_fill_word(s, start_of_word, index);
			if (!(result[word_index]))
				return (ft_free_words(result, word_index));
			start_of_word = -1;
			word_index++;
		}
		index++;
	}
	return (result);
}
