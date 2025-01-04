/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:39:47 by mkocaman          #+#    #+#             */
/*   Updated: 2023/07/18 14:42:57 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *a, const char *b, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(b));
	i = 0;
	while (b[i] && i < size - 1)
	{
		a[i] = b[i];
		i++;
	}
	a[i] = 0;
	return (ft_strlen(b));
}
