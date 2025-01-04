/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:09:19 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/16 14:11:05 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../memory/allocator.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	str = (char *)safe_malloc((sizeof(char)
				* (ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!str)
		return (NULL);
	while (s1[i] != 0)
	{
		str[j] = s1[i++];
		j++;
	}
	i = 0;
	while (s2[i] != 0)
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	return (str[j] = 0, str);
}

char	*ft_strjoin_char(char const *s1, char const s2)
{
	char			*str;
	unsigned int	i;

	if (s1 == NULL)
	{
		str = (char *)safe_malloc((sizeof(char) * 2));
		str[0] = s2;
		str[1] = '\0';
		return (str);
	}
	str = (char *)safe_malloc((sizeof(char) * (ft_strlen(s1)) + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = s2;
	i++;
	return (str[i] = '\0', str);
}
