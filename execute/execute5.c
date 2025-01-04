/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/16 16:03:37 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"
#include <sys/wait.h>

int	proccess_execute(t_data *data, int j)
{
	if (check_dup_and_close_fd(data, j))
		return (1);
	if (ft_strncmp(data->token[j].command, ECHO, 5) == 0)
	{
		ft_echo(data->token[j].content);
		data->exit_code = 0;
	}
	else if (ft_strncmp(data->cmd[j], CD, 3) == 0)
		ft_cd(data, &data->token[j].content[1]);
	else if (ft_strncmp(data->cmd[j], LOW_PWD, 4) == 0)
	{
		data->exit_code = 0;
		ft_pwd();
	}
	else if (ft_strncmp(data->cmd[j], EXPORT, 7) == 0)
		elif_export(data, j);
	else if (ft_strncmp(data->cmd[j], ENV, 4) == 0)
		ft_env(data);
	else if (ft_strncmp(data->cmd[j], EXIT, 5) == 0)
		ft_exit(data->token[j].content, data->exit_code, data);
	else if (ft_strncmp(data->cmd[j], UNSET, 6) == 0)
		ft_unset(data, data->cmd[j + 1]);
	else
		ft_execve(data, data->token[j]);
	return (0);
}

int	check_dup_and_close_fd(t_data *data, int j)
{
	if (data->token[j].redirect)
	{
		if (change_dup(data->token[j], data))
		{
			last_dup_and_close_fd(data->org_out_fd, data->org_in_fd);
			return (ft_free(data), 1);
		}
	}
	return (0);
}

void	execute(t_data *data)
{
	int		j;

	j = 0;
	initialize_fds(&j, data);
	if (data->token[1].command == NULL)
	{
		if (proccess_execute(data, j))
			return ;
		j++;
	}
	else
		execute_with_pipe(data);
	last_dup_and_close_fd(data->org_out_fd, data->org_in_fd);
	ft_free(data);
}

int	execute_with_pipe_2(t_data *data, int fd[2], int status)
{
	if (data->pid < 0)
		return (1);
	else
	{
		close(fd[1]);
		waitpid(data->pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
	}
	return (0);
}

void	execute_with_pipe(t_data *data)
{
	int		i;
	int		fd_out;
	int		status;
	int		fd[2];
	int		fd_in;

	fd_out = dup(1);
	fd_in = dup(0);
	i = -1;
	status = 0;
	while (data->token[++i].command != NULL)
	{
		pipe(fd);
		data->pid = fork();
		if (data->pid == 0)
		{
			fork_proccesss(fd_in, data, i, fd);
			ft_execute(data, i, fd_in, fd_out);
			exit(data->exit_code);
		}
		else if (execute_with_pipe_2(data, fd, status))
			return (little_fork_error_message(data), (void)0);
		fd_in = fd[0];
	}
}
