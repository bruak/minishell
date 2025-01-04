/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:21:50 by mkocaman          #+#    #+#             */
/*   Updated: 2023/07/04 13:22:13 by mkocaman         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int ch)
{
	int	alpha;
	int	digit;

	alpha = ft_isalpha(ch);
	digit = ft_isdigit(ch);
	if (alpha == 1 || digit == 1)
		return (1);
	else
		return (0);
}
