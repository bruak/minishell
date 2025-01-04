/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoykan <bsoykan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/15 16:55:32 by bsoykan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"
#include "../libft/libft.h"

void	redir_zero_init(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].command)
	{
		data->token[i].redir_in = 0;
		data->token[i].redir_out = 0;
		i++;
	}
}

int	is_redir(char *str)
{
	if (ft_strncmp(str, D_REDIR_OUT, 2) == 0
		|| ft_strncmp(str, D_REDIR_IN, 2) == 0
		|| ft_strncmp(str, D_REDIR_OUT_2, 3) == 0
		|| ft_strncmp(str, D_REDIR_IN_2, 3) == 0)
		return (1);
	return (0);
}

void	update_before_redir(struct s_data *data, int i, int *j)
{
	char	*tmp;

	tmp = data->token[i].before_redir;
	data->token[i].before_redir = ft_strjoin(data->token[i].before_redir,
			data->token[i].content[(*j)++]);
	safe_free(tmp);
	tmp = data->token[i].before_redir;
	data->token[i].before_redir = ft_strjoin(data->token[i].before_redir,
			D_SPACE);
	safe_free(tmp);
}

int	is_content_null_is_redir(t_data *data, int i, int j)
{
	return (data->token[i].content[j] != NULL
		&& !is_redir(data->token[i].content[j]));
}

int	if_chracter_end(t_data *data, int i)
{
	return (data->input[i] && (is_whitespace(data->input[i])
			|| data->input[i] == PIPET
			|| data->input[i] == REDIR_OUT
			|| data->input[i] == REDIR_IN
			|| data->input[i] == NUL));
}
