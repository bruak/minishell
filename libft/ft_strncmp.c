/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:57:51 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/01 23:05:04 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t a)
{
	size_t	i;

	i = 0;
	while (i < a)
	{
		if (*str1 != *str2)
			return ((unsigned char)*str1 - (unsigned char)*str2);
		if (*str1 == '\0' && *str2 == '\0')
			return (0);
		i++;
		str1++;
		str2++;
	}
	return (0);
}
