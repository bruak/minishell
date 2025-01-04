/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:37:31 by mkocaman          #+#    #+#             */
/*   Updated: 2023/07/08 16:16:41 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *b, const void *a, size_t len)
{
	size_t	i;

	if (len == 0 || b == a)
		return (b);
	i = 0;
	while (i < len)
	{
		((unsigned char *) b)[i] = ((unsigned char *) a)[i];
		i++;
	}
	return (b);
}
