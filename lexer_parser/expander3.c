/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:28:04 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/18 12:29:01 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"

void	if_question_mark(t_data *data, char **tmp, int *j)
{
	*tmp = ft_strjoin(*tmp, ft_itoa(data->exit_code));
	*j += 1;
}

void	handle_dquote_else_side(t_data *data, char *tmp, char *tmp2)
{
	if (env2(data, &tmp2))
		little_just_for_compiling_tmps(tmp2, tmp);
	else
		little_just_for_tmp_null(tmp2, tmp);
}

void	little_if_isalnum_control(t_data *data, char **tmp2, int i, int *j)
{
	*tmp2 = ft_strjoin_char(*tmp2, data->cmd[i][*j]);
	*j += 1;
}

void	safe_free_tmp_2(t_data *data, char **tmp2, char **tmp)
{
	if (env2(data, tmp2))
		*tmp = ft_strjoin(*tmp, *tmp2);
}

void	if_not_32_and_not_whitespace(t_data *data, char **tmp, int i, int *j)
{
	if (data->cmd[i][*j] == D_QUOTE)
		*tmp = handle_dquote(data, i, j, *tmp);
	else if (data->cmd[i][*j] == S_QUOTE)
		*tmp = handle_squote(data, i, j, *tmp);
	else if (data->cmd[i][*j] == '$')
		*tmp = handle_dollar(data, i, j, *tmp);
	else
		little_if_isalnum_control(data, tmp, i, j);
}
