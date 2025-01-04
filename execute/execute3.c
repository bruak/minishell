/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/15 14:22:06 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>

int	fd_control(int fd, char *file, t_data *data)
{
	if (fd == -1)
	{
		data->exit_code = 1;
		return (just_fd_error_message(file));
	}
	return (0);
}

int	handle_double_redir_out(char **content, int *i, t_data *data)
{
	int	fd;

	while (content[*i + 1] != NULL && ft_strncmp(content[*i + 1],
			D_REDIR_OUT, 2))
	{
		fd = open(content[*i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_control(fd, content[*i + 1], data) == 1)
			return (1);
		dup2(fd, 1);
		close(fd);
		(*i)++;
	}
	return (0);
}

void	handle_child_process(int *pipe_fd, int pid, int *status)
{
	close(pipe_fd[1]);
	waitpid(pid, status, 0);
	g_signal = *status / 256;
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}

int	handle_double_redir_in(char **content, int *i, t_data *data)
{
	int		status;
	int		pipe_fd[2];
	pid_t	pid;

	while (is_content_redir(content, i))
	{
		dup2(data->org_out_fd, 1);
		dup2(data->org_in_fd, 0);
		pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
		{
			if (g_signal == IF_SIGEXIT)
				exit(11);
			close(pipe_fd[0]);
			heredoc(pipe_fd[1], content[*i + 1]);
			exit(0);
		}
		else
			handle_child_process(pipe_fd, pid, &status);
		if (g_signal == IF_SIGEXIT)
			return (1);
		(*i)++;
	}
	return (0);
}

int	just_fd_error_message(char *file)
{
	return (ft_putstr_fd(RED_MINISHELL, 2), ft_putstr_fd(file, 2),
		ft_putstr_fd(": ", 2), ft_putstr_fd(FD_ERR, 2), 1);
}
