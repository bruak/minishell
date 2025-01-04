/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoykan <bsoykan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:13:17 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/15 15:19:54 by bsoykan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"

void	last_dup_and_close_fd(int originalout_fd, int originalin_fd)
{
	dup2(originalout_fd, 1);
	dup2(originalin_fd, 0);
	close(originalout_fd);
	close(originalin_fd);
}

void	ft_set_exit_and_pwd(t_data *data)
{
	data->exit_code = 0;
	ft_pwd();
}

void	ft_set_exit_and_echo(t_data *data, char **content)
{
	ft_echo(content);
	data->exit_code = 0;
}

void	ft_execute(t_data *data, int j, int original_in_fd,
	int original_out_fd)
{
	if (data->token[j].redirect)
	{
		if (change_dup(data->token[j], data))
		{
			last_dup_and_close_fd(original_out_fd,
				original_in_fd);
			return (ft_free(data), (void)0);
		}
	}
	if (ft_strncmp(data->token[j].command, "echo", 5) == 0)
		ft_set_exit_and_echo(data, data->token[j].content);
	else if (ft_strncmp(data->token[j].command, "cd", 3) == 0)
		ft_cd(data, &data->token[j].content[1]);
	else if (ft_strncmp(data->token[j].command, "pwd", 4) == 0)
		ft_set_exit_and_pwd(data);
	else if (ft_strncmp(data->token[j].command, "export", 7) == 0)
		elif_export(data, j);
	else if (ft_strncmp(data->token[j].command, "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp(data->token[j].command, "exit", 5) == 0)
		ft_exit(data->token[j].content, data->exit_code, data);
	else if (ft_strncmp(data->token[j].command, "unset", 6) == 0)
		ft_unset(data, data->cmd[j + 1]);
	else
		ft_execve(data, data->token[j]);
}
