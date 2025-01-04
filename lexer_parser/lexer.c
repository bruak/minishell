/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:59:53 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/16 17:36:48 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"
#include "../libft/libft.h"

int	handle_quotes(t_data *data, int main_indx, int k)
{
	char	quote_type;
	int		j;

	j = 1;
	quote_type = data->input[main_indx];
	while (data->input[main_indx + j] && data->input[main_indx + j]
		!= quote_type)
		j++;
	data->cmd[k] = safe_malloc(sizeof(char) * (j + 2));
	j = 0;
	while (data->input[main_indx] && (data->input[main_indx]
			!= quote_type || j == 0))
	{
		data->cmd[k][j] = data->input[main_indx];
		main_indx++;
		j++;
	}
	is_quote_type(data, main_indx, quote_type);
	data->cmd[k][j++] = data->input[main_indx];
	main_indx++;
	if (if_chracter_end(data, main_indx))
		data->cmd[k][j] = NUL;
	else
		process_input(data, &main_indx, &j, k);
	return (main_indx);
}

void	process_input(struct s_data *data, int *main_indx, int *j, int k)
{
	data->cmd[k][*j] = NUL;
	while (data->input[*main_indx] && !is_whitespace(data->input[*main_indx])
		&& data->input[*main_indx] != PIPET
		&& data->input[*main_indx] != REDIR_OUT
		&& data->input[*main_indx] != REDIR_IN)
	{
		data->cmd[k] = ft_strjoin_char(data->cmd[k], data->input[*main_indx]);
		(*main_indx)++;
		(*j)++;
	}
	if (*main_indx >= ((int)ft_strlen(data->input)))
	{
		data->cmd[k][*j] = NUL;
		(*j)++;
		return ;
	}
	data->cmd[k] = ft_strjoin_char(data->cmd[k], data->input[*main_indx]);
	(*main_indx)++;
	(*j)++;
	data->cmd[k][*j] = NUL;
}

void	is_quote_type(t_data *data, int main_indx, char quote_type)
{
	if (data->input[main_indx] != quote_type)
		data->syntax_flag = 1;
}

void	handle_input(t_data *data)
{
	int	main_indx;
	int	cmd_i;

	main_indx = 0;
	cmd_i = 0;
	g_signal = DO_ZERO;
	data->cmd = safe_malloc(sizeof(char *) * (arg_count(data->input) + 1));
	while (data->input[main_indx])
	{
		while (is_whitespace(data->input[main_indx]))
			main_indx++;
		if (data->input[main_indx] == S_QUOTE
			|| data->input[main_indx] == D_QUOTE)
			main_indx = handle_quotes(data, main_indx, cmd_i);
		else if (data->input[main_indx] != PIPET && data->input[main_indx]
			!= REDIR_OUT && data->input[main_indx] != REDIR_IN)
			main_indx = handle_word(data, main_indx, cmd_i);
		else
			main_indx = handle_flag(data, main_indx, cmd_i);
		cmd_i++;
		while (data->input[main_indx] && is_whitespace(data->input[main_indx]))
			main_indx++;
	}
	data->cmd[cmd_i] = NULL;
	pipe_counter(data);
}

int	handle_word(t_data *data, int i, int k)
{
	int	j;

	j = 0;
	while (data->input[i + j] && !is_whitespace(data->input[i + j])
		&& data->input[i + j] != PIPET && data->input[i + j]
		!= REDIR_OUT && data->input[i + j] != REDIR_IN)
		j++;
	data->cmd[k] = safe_malloc(sizeof(char) * (j + 2));
	j = 0;
	while (data->input[i] && !is_whitespace(data->input[i])
		&& data->input[i] != PIPET && data->input[i]
		!= REDIR_OUT && data->input[i] != REDIR_IN && data->input[i] > 32)
	{
		data->cmd[k][j] = data->input[i];
		i++;
		j++;
	}
	data->cmd[k][j] = '\0';
	return (i);
}
