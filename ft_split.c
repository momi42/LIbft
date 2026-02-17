/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohfalla <mohfalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:37:06 by mohfalla          #+#    #+#             */
/*   Updated: 2025/12/16 14:12:18 by mohfalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **str, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(str[i]);
		i++;
	}
	free (str);
}

static size_t	word_count(char const *s, char c)
{
	size_t	i;
	size_t	w_count;

	w_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			w_count++;
		i++;
	}
	return (w_count);
}

static int	fill_split(char const *s, char c, char **split)
{
	size_t	i;
	size_t	start;
	size_t	index;

	index = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] != c && s[i])
			i++;
		split[index] = ft_substr(s, start, (i - start));
		if (!split[index])
		{
			free_all(split, index);
			return (0);
		}
		index++;
	}
	split[index] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc (sizeof(char *) * (word_count(s, c) + 1));
	if (!split)
		return (NULL);
	if (!fill_split(s, c, split))
		return (NULL);
	return (split);
}
