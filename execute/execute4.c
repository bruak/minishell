/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoykan <bsoykan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/15 15:47:10 by bsoykan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "unistd.h"

void	elif_export(t_data *data, int j)
{
	{
		if (data->token[j].content[1] != NULL
			&& is_redir(data->token[j].content[1]) == 0)
			ft_export(data, &data->token[j].content[1]);
		else
		{
			data->exit_code = 0;
			ft_export_2(data);
		}
	}
}

void	initialize_fds(int *j, t_data *data)
{
	g_signal = DO_ZERO;
	*j = 0;
	data->org_in_fd = dup(1);
	data->org_out_fd = dup(0);
}

void	fork_proccesss(int fd_in, t_data *data, int i, int fd[2])
{
	dup2(fd_in, 0);
	if (data->token[i + 1].command != NULL)
		dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}
