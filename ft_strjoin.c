/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohfalla <mohfalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:30:21 by mohfalla          #+#    #+#             */
/*   Updated: 2025/12/09 18:05:35 by mohfalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	size_t	i;
	size_t	j;
	char	*new;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	new = (char *)malloc (sizeof(char) * (l1 + l2 + 1));
	if (!new)
		return (0);
	i = 0;
	j = 0;
	while (i < l1)
	{
		new[i] = s1[i];
		i++;
	}
	while (j < l2)
	{
		new[j + i] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}
