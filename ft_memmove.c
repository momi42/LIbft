/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohfalla <mohfalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:26:59 by mohfalla          #+#    #+#             */
/*   Updated: 2025/12/09 13:35:45 by mohfalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	num;

	if (!dest && !src)
		return (NULL);
	if ((unsigned char *)dest < (const unsigned char *)src)
	{
		num = 0;
		while (n > 0)
		{
			((unsigned char *)dest)[num] = ((const unsigned char *)src)[num];
			num++;
			n--;
		}
	}
	else if ((unsigned char *)dest > (const unsigned char *)src)
	{
		while (n-- > 0)
		{
			((unsigned char *)dest)[n] = ((const unsigned char *)src)[n];
		}
	}
	return (dest);
}
