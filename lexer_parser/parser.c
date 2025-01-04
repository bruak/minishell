/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:45:44 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/16 16:14:49 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"
#include "../libft/libft.h"

void	parse_and_organize_commands(t_data *data)
{
	int	cmd_i;
	int	tokn_i;
	int	content_i;

	cmd_i = 0;
	tokn_i = 0;
	while (data->cmd[cmd_i])
	{
		content_i = 0;
		while (data->cmd[content_i])
			content_i++;
		token_content_allocation(data, tokn_i, content_i);
		data->token[tokn_i].command = ft_strdup(data->cmd[cmd_i]);
		process_command(data, &cmd_i, tokn_i, &content_i);
		data->token[tokn_i].content[content_i] = NULL;
		if (!data->cmd[cmd_i])
		{
			tokn_i++;
			break ;
		}
		cmd_i++;
		tokn_i++;
	}
	data->token[tokn_i].command = NULL;
}

void	process_command(struct s_data *data, int *cmd_i,
	int tokn_i, int *content_i)
{
	if (data->cmd[*cmd_i] && (ft_strncmp(data->cmd[*cmd_i], D_PIPET, 2)))
	{
		*content_i = 0;
		data->token[tokn_i].content[(*content_i)++]
			= ft_strdup(data->cmd[*cmd_i]);
		(*cmd_i)++;
		while ((data->cmd[*cmd_i] && ft_strncmp(data->cmd[*cmd_i], D_PIPET, 2)))
		{
			data->token[tokn_i].content[*content_i]
				= ft_strdup(data->cmd[*cmd_i]);
			(*cmd_i)++;
			(*content_i)++;
		}
	}
}

void	token_content_allocation(t_data *data, int tokn_i, int content_i)
{
	data->token[tokn_i].redirect = 0;
	data->token[tokn_i].content = safe_malloc(sizeof(char *) * (content_i + 2));
}

void	process_pipe_and_redirection(struct s_data *data, int *i,
	int *flag, int *pipe_count)
{
	*flag = 0;
	if (ft_strchr(data->cmd[*i], PIPET))
	{
		(*pipe_count)++;
		*flag = 1;
	}
	(*i)++;
}

void	pipe_counter(t_data *data)
{
	int	i;
	int	pipe_count;
	int	flag;

	i = 0;
	pipe_count = 0;
	flag = 0;
	while (data->cmd[i])
		process_pipe_and_redirection(data, &i, &flag, &pipe_count);
	data->token = safe_malloc(sizeof(t_token) * (pipe_count + 2));
	expander(data);
	parse_and_organize_commands(data);
}
