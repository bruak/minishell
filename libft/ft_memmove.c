/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:34:43 by mkocaman          #+#    #+#             */
/*   Updated: 2023/07/05 14:34:45 by mkocaman         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *sour, size_t len)
{
	if (dest == 0 && sour == 0)
		return (0);
	if (dest < sour)
		ft_memcpy(dest, sour, len);
	else if (dest > sour)
	{
		while (len--)
			*((unsigned char *)(dest + len)) = *((unsigned char *)(sour + len));
	}
	return (dest);
}
