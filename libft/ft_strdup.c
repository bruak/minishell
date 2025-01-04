/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:46:26 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/15 12:19:38 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../memory/allocator.h"

char	*ft_strdup(const char *str)
{
	char	*str2;
	size_t	len;

	len = ft_strlen(str) + 1;
	str2 = (char *)safe_malloc(len);
	if (!str2)
		return (NULL);
	ft_memcpy(str2, str, len);
	return (str2);
}
