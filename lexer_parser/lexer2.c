/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:37:00 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/18 12:11:07 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"
#include "../libft/libft.h"

int	is_chracter(t_data *data, int i)
{
	return (data->input[i] && !is_whitespace(data->input[i])
		&& data->input[i] != PIPET && data->input[i] != REDIR_OUT
		&& data->input[i] != REDIR_IN);
}

void	little_bastard_enhancer(int *count, int *i)
{
	(*count)++;
	(*i)++;
}

int	process_string(char *str, int i, int count)
{
	while (str[i])
	{
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
		{
			i++;
			while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE)
				i++;
		}
		if (!(is_whitespace(str[i])) && str[i] != PIPET && str[i]
			!= REDIR_OUT && str[i] != REDIR_IN)
		{
			count++;
			while (str[i] && !(is_whitespace(str[i]))
				&& str[i] != PIPET && str[i]
				!= REDIR_OUT && str[i] != REDIR_IN)
				i++;
		}
		else if (str[i] == PIPET || str[i] == REDIR_OUT || str[i] == REDIR_IN)
			little_bastard_enhancer(&count, &i);
		else
			i++;
	}
	return (count);
}

int	arg_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	count = process_string(str, i, count);
	return (count);
}

void	redir_lexer(t_data *data)
{
	int	i;
	int	k;
	int	j;

	i = -1;
	while (data->token[++i].command && checker(data, i) == 1)
	{
		k = 0;
		j = 0;
		data->token[i].before_redir = NULL;
		while (is_content_null_is_redir(data, i, j))
			update_before_redir(data, i, &j);
		while (data->token[i].content[j + k] != NULL)
			k++;
		data->token[i].after_redir = safe_malloc(sizeof(char *) * (k + 1));
		k = 0;
		while (data->token[i].content[j])
		{
			data->token[i].after_redir[k++]
				= ft_strdup(data->token[i].content[j++]);
			data->token[i].redirect = 1;
		}
		data->token[i].after_redir[k] = NULL;
	}
}
