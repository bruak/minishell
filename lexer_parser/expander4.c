/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:05:33 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/16 18:05:33 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"
#include "../memory/allocator.h"

void	handle_dquote_dollar(t_data *data, char **tmp, char **tmp2)
{
	if (env2(data, tmp2))
	{
		*tmp = ft_strjoin(*tmp, *tmp2);
		safe_free(*tmp2);
		*tmp2 = NULL;
	}
	else
	{
		safe_free(*tmp2);
		*tmp2 = NULL;
	}
}

int	checker(t_data *data, int i)
{
	if (ft_strncmp(data->token[i].command, "|", 2) == 0
		|| data->token[i].command == NULL)
	{
		data->token[i].content = safe_malloc(sizeof(char *) * 1);
		data->token[i].content[0] = NULL;
		data->token[i].before_redir = safe_malloc(sizeof(char *) * 1);
		data->token[i].before_redir = NULL;
		data->token[i].after_redir = safe_malloc(sizeof(char *) * 1);
		data->token[i].after_redir = NULL;
		return (0);
	}
	return (1);
}
