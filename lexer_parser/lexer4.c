/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoykan <bsoykan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/15 16:55:37 by bsoykan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"

int	handle_flag(t_data *data, int i, int k)
{
	if (data->input[i] == data->input[i + 1] && data->input[i] != PIPET)
	{
		data->cmd[k] = safe_malloc(sizeof(char) * 3);
		data->cmd[k][0] = data->input[i];
		data->cmd[k][1] = data->input[i + 1];
		data->cmd[k][2] = NUL;
		i += 2;
	}
	else
	{
		data->cmd[k] = safe_malloc(sizeof(char) * 2);
		data->cmd[k][0] = data->input[i];
		data->cmd[k][1] = NUL;
		i++;
	}
	return (i);
}

int	is_whitespace(char c)
{
	if ((c == SPACE || c < 0) || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
