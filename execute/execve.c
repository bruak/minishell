/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:27:30 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/18 12:44:12 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include "../memory/allocator.h"
#include "sys/wait.h"

char	*find_path(t_data *data, char *cmd)
{
	int		i;
	char	**path;
	char	*tmp;
	char	*tmp2;

	i = 0;
	path = ft_split(cd_env(data, PATH), COLON);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (path[0] == NULL)
		return (free(path), NULL);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], D_SLASH);
		tmp2 = ft_strjoin(tmp, cmd);
		safe_free(tmp);
		if (access(tmp2, X_OK) == 0)
			return (free_split(path), tmp2);
		safe_free(tmp2);
	}
	return (free_split(path), NULL);
}

void	fork_proccess(char *path, char **tmp, t_data *data, t_token token)
{
	if (tmp[0] == NULL)
	{
		printf(MINISHELL_COMMAND_NOT_FOUND, token.command);
		data->exit_code = 127;
		exit(127);
	}
	if (path == NULL)
	{
		printf(MINISHELL_COMMAND_NOT_FOUND, token.command);
		data->exit_code = 127;
		exit(127);
	}
	if (execve(path, tmp, data->envp) == -1)
	{
		printf(MINISHELL_COMMAND_NOT_FOUND, token.command);
		data->exit_code = 127;
		exit(127);
	}
	else
		data->exit_code = 0;
}

void	little_fork_error_message(t_data *data)
{
	printf(MINISHEL_FORK_ERR, NOT_OPEN_ERR);
	ft_free(data);
}

void	exit_status_handle(t_data *data, int pid, int status, char **tmp)
{
	int	i;

	i = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	while (tmp[i] != NULL)
		safe_free(tmp[i++]);
	safe_free(tmp);
}

void	ft_execve(t_data *data, t_token token)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**tmp;

	status = 0;
	if (ft_strncmp(token.command, "<<", 3) == 0)
		return ;
	tmp = ft_split(token.before_redir, SPACE);
	path = find_path(data, token.command);
	pid = fork();
	if (pid == 0)
		fork_proccess(path, tmp, data, token);
	else if (pid < 0)
		little_fork_error_message(data);
	else
	{
		exit_status_handle(data, pid, status, tmp);
		if (path != NULL)
			safe_free(path);
	}
}
