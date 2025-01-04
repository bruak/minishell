/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:40:24 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/13 14:18:37 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"
#include "../memory/allocator.h"

void	erro_premium(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		safe_free(strs[i]);
		i++;
	}
	safe_free(strs);
}
