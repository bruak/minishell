/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/16 17:37:19 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"
#include "../libft/libft.h"

char	*two_quote_cont(struct s_data *data, int i, int *j, char *tmp)
{
	while (data->cmd[i][*j] == D_QUOTE || data->cmd[i][*j] == S_QUOTE)
	{
		if (data->cmd[i][*j] == D_QUOTE)
			tmp = handle_dquote(data, i, j, tmp);
		else
			tmp = handle_squote(data, i, j, tmp);
	}
	return (tmp);
}

void	update_command(struct s_data *data, char *tmp, int *i)
{
	safe_free(data->cmd[*i]);
	if (tmp != NULL)
		data->cmd[*i] = ft_strdup(tmp);
	else
		data->cmd[*i] = ft_strdup("");
	(*i)++;
}

void	check_command(t_data *data, char **tmp, int i, int *j)
{
	*j += 1;
	if (data->cmd[i][*j] == D_QUOTE)
		*tmp = handle_dquote(data, i, j, *tmp);
	else if (data->cmd[i][*j] == S_QUOTE)
		*tmp = handle_squote(data, i, j, *tmp);
	else if (data->cmd[i][*j] == DOLLAR)
		*tmp = handle_dollar(data, i, j, *tmp);
	else
		*tmp = handle_word2(data, i, j, *tmp);
}

void	little_just_for_compiling_tmps(char *tmp2, char *tmp)
{
	tmp = ft_strjoin(tmp, tmp2);
	safe_free(tmp2);
}

void	little_just_for_tmp_null(char *tmp2, char *tmp)
{
	safe_free(tmp2);
	tmp2 = ft_strdup("");
	tmp = ft_strjoin(tmp, tmp2);
}
