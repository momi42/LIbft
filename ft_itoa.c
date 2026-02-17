/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohfalla <mohfalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:23:37 by mohfalla          #+#    #+#             */
/*   Updated: 2025/12/13 14:28:35 by mohfalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits(long int n)
{
	int	d;

	d = 0;
	if (n < 0)
	{
		n = -n;
		d = 1;
	}
	if (n == 0)
		d = 1;
	while (n > 0)
	{
		n /= 10;
		d++;
	}
	return (d - 1);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			d;
	int			i;
	long int	num;

	num = (long int)n;
	d = digits(num);
	i = 0;
	str = (char *)malloc(sizeof(char) * (d + 2));
	if (!str)
		return (0);
	str[d + 1] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		i = 1;
		num = -num;
	}
	while (d >= i)
	{
		str[d--] = ((num % 10) + '0');
		num /= 10;
	}
	return (str);
}
