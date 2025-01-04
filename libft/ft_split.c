/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:37:25 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/18 11:50:48 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../memory/allocator.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (word);
}

static int	ft_size_word(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

static char	**ft_freee(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		word;
	char	**strs;
	int		j;

	i = 0;
	j = -1;
	word = ft_count_word(s, c);
	strs = (char **)safe_malloc((word + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (++j < word)
	{
		while (s[i] == c)
			i++;
		strs[j] = ft_substr(s, i, ft_size_word(s, c, i));
		if (!(strs[j]))
			return (ft_freee(strs, j));
		i += ft_size_word(s, c, i);
	}
	strs[j] = 0;
	return (strs);
}
