/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:03:57 by mkocaman          #+#    #+#             */
/*   Updated: 2023/07/05 18:03:59 by mkocaman         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *src, int a)
{
	while (*src != 0 && (char)a != *src)
		src++;
	if ((char)a == *src)
		return ((char *)src);
	return (0);
}
