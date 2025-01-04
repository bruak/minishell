/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:00:27 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/13 14:19:04 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../memory/allocator.h" 

static int	ft_len(int n, int flag)
{
	int	cont;

	cont = 0;
	if (n == 0)
		cont++;
	while (n != 0)
	{
		n = n / 10;
		cont++;
	}
	if (flag < 0)
		cont++;
	return (cont);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;
	long	n2;

	n2 = n;
	if (n2 < 0)
		sign = -1;
	else
		sign = 1;
	n2 = n2 * sign;
	len = ft_len(n2, sign);
	str = (char *)safe_malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = 0;
	while (--len >= 0)
	{
		str[len] = 48 + (n2 % 10);
		n2 = n2 / 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
