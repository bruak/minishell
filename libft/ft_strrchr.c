/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:48:26 by mkocaman          #+#    #+#             */
/*   Updated: 2023/07/09 12:50:12 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int a)
{
	int	i;

	i = (int)ft_strlen(str);
	while (i >= 0)
	{
		if (*(str + i) == (char)a)
			return ((char *)str + i);
		i--;
	}
	return (0);
}
