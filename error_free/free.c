/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/18 11:59:27 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"

void	free_exp(t_data *data)
{
	int		i;

	i = 0;
	while (data->exp[i] != NULL)
	{
		if (data->export[i].key != NULL)
			safe_free(data->export[i].key);
		if (data->export[i].value != NULL)
			safe_free(data->export[i].value);
		i++;
	}
	safe_free(data->export);
}

void	free_env(t_data *data)
{
	int		i;

	i = 0;
	while (data->env[i].key != NULL)
	{
		safe_free(data->env[i].key);
		if (data->env[i].value != NULL)
			safe_free(data->env[i].value);
		i++;
	}
	safe_free(data->env);
}

void	ft_free(t_data *data)
{
	int		j;

	j = 0;
	while (data && data->token && data->token[j].command)
	{
		free_content(data, j);
		if (data->token[j].before_redir)
			safe_free(data->token[j].before_redir);
		data->token[j].before_redir = NULL;
		while (data->token[j].after_redir)
		{
			free_after_redir(data, j);
			safe_free(data->token[j].after_redir);
			data->token[j].after_redir = NULL;
		}
		safe_free(data->token[j].command);
		j++;
	}
	free_cmd(data);
	safe_free(data->input);
	safe_free(data->token);
}

void	free_cmd(t_data *data)
{
	int		i;

	i = 0;
	if (data && data->cmd)
	{
		while (data->cmd[i])
		{
			safe_free(data->cmd[i]);
			data->cmd[i] = NULL;
			i++;
		}
		safe_free(data->cmd);
		data->cmd = NULL;
	}
}

void	free_content(t_data *data, int j)
{
	int	i;

	i = 0;
	if (data->token[j].content)
	{
		if (data->token[j].before_redir == NULL)
		{
			safe_free(data->token[j].content);
			return ;
		}
		while (data->token[j].content[i])
		{
			safe_free(data->token[j].content[i]);
			i++;
		}
		data->token[j].content = NULL;
	}
}
