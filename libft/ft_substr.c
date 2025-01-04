/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoykan <bsoykan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:12:17 by mkocaman          #+#    #+#             */
/*   Updated: 2024/02/22 12:30:35 by bsoykan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../memory/allocator.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0 || ft_strlen(s) == 0)
		return (ft_strdup(""));
	while (i < len && s[i + start] != 0)
		i++;
	str = (void *)safe_malloc((sizeof(char) * i) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[j] != 0)
	{
		if (j >= start && i < len)
			str[i++] = s[start++];
		j++;
	}
	str[i] = 0;
	return (str);
}
