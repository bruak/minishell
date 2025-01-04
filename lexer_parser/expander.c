/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:16:37 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/18 12:25:29 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"
#include "../memory/allocator.h"

char	*handle_dquote(t_data *data, int i, int *j, char *tmp)
{
	char	*tmp2;

	*j += 1;
	while (data->cmd[i][*j] && data->cmd[i][*j] != D_QUOTE)
	{
		if (data->cmd[i][*j] == DOLLAR)
		{
			*j += 1;
			if (data->cmd[i][*j] == '?')
			{
				if_question_mark(data, &tmp, j);
				continue ;
			}
			else
				while (ft_isalnum(data->cmd[i][*j]))
					little_if_isalnum_control(data, &tmp2, i, j);
			handle_dquote_dollar(data, &tmp, &tmp2);
		}
		else
			tmp = ft_strjoin_char(tmp, data->cmd[i][(*j)++]);
	}
	if (data->cmd[i][*j] && data->cmd[i][*j + 1] > 32
			&& !(is_whitespace(data->cmd[i][*j + 1])))
		check_command(data, &tmp, i, j);
	return (tmp);
}

char	*handle_squote(t_data *data, int i, int *j, char *tmp)
{
	*j += 1;
	while (data->cmd[i][*j] && data->cmd[i][*j] != S_QUOTE)
	{
		tmp = ft_strjoin_char(tmp, data->cmd[i][*j]);
		*j += 1;
	}
	if (data->cmd[i][*j] && data->cmd[i][*j + 1] > 32
			&& !(is_whitespace(data->cmd[i][*j + 1])))
	{
		*j += 1;
		if (data->cmd[i][*j] == D_QUOTE)
			tmp = handle_dquote(data, i, j, tmp);
		else if (data->cmd[i][*j] == S_QUOTE)
			tmp = handle_squote(data, i, j, tmp);
		else if (data->cmd[i][*j] == '$')
			tmp = handle_dollar(data, i, j, tmp);
		else
			tmp = handle_word2(data, i, j, tmp);
	}
	return (tmp);
}

char	*handle_dollar(t_data *data, int i, int *j, char *tmp)
{
	char	*tmp2;

	*j += 1;
	tmp2 = NULL;
	if (data->cmd[i][*j] == '$')
		return (*j += 1, ft_strjoin(tmp, "$"));
	if (data->cmd[i][*j] == '?')
	{
		if_question_mark(data, &tmp, j);
		while (data->cmd[i][*j] > 32 && !(is_whitespace(data->cmd[i][*j])))
			if_not_32_and_not_whitespace(data, &tmp, i, j);
		return (tmp);
	}
	while (ft_isalnum(data->cmd[i][*j]))
		little_if_isalnum_control(data, &tmp2, i, j);
	if (tmp2)
		safe_free_tmp_2(data, &tmp2, &tmp);
	else
		little_just_for_tmp_null(tmp2, tmp);
	if (data->cmd[i][*j] == '$')
		tmp = handle_dollar(data, i, j, tmp);
	while (data->cmd[i][*j] > 32 && !(is_whitespace(data->cmd[i][*j])))
		if_not_32_and_not_whitespace(data, &tmp, i, j);
	return (tmp);
}

char	*handle_word2(t_data *data, int i, int *j, char *tmp)
{
	char	*tmp2;

	if (tmp == NULL)
		tmp = ft_strdup("");
	while (data->cmd[i][*j] != 0)
	{
		if (data->cmd[i][*j] == '$')
			tmp = handle_dollar(data, i, j, tmp);
		else if (data->cmd[i][*j] == D_QUOTE)
			tmp = handle_dquote(data, i, j, tmp);
		else if (data->cmd[i][*j] == S_QUOTE)
		{
			tmp = handle_squote(data, i, j, tmp);
		}
		else
		{
			tmp2 = NULL;
			tmp2 = ft_strjoin(tmp2, tmp);
			tmp = ft_strjoin_char(tmp2, data->cmd[i][*j]);
			safe_free(tmp2);
			*j += 1;
		}
	}
	return (tmp);
}

void	expander(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (data->cmd[i])
	{
		j = 0;
		tmp = NULL;
		if (data->cmd[i][j] == D_QUOTE || data->cmd[i][j] == S_QUOTE)
			tmp = two_quote_cont(data, i, &j, tmp);
		else if (data->cmd[i][j] == DOLLAR)
			tmp = handle_dollar(data, i, &j, tmp);
		else
			tmp = handle_word2(data, i, &j, tmp);
		update_command(data, tmp, &i);
		if (tmp)
			safe_free(tmp);
	}
}
