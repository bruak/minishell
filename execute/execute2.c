/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/18 11:45:43 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"
#include <fcntl.h>

int	is_content_redir(char **content, int *i)
{
	return (content[*i + 1] != NULL
		&& ft_strncmp(content[*i + 1], D_REDIR_IN_2, 3)
		&& ft_strncmp(content[*i + 1], ">>", 3)
		&& ft_strncmp(content[*i + 1], ">", 2)
		&& ft_strncmp(content[*i + 1], "<", 2));
}

int	handle_double_redir_out_2(char **content, int *i, t_data *data)
{
	int		fd;

	while (content[*i + 1] != NULL && ft_strncmp(content[*i + 1],
			D_REDIR_OUT_2, 3))
	{
		fd = open(content[*i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd_control(fd, content[*i + 1], data) == 1)
			return (1);
		dup2(fd, 1);
		close(fd);
		(*i)++;
	}
	return (0);
}

int	handle_double_redir_in_2(char **content, int *i, t_data *data)
{
	int	fd;

	while (content[*i + 1] != NULL && ft_strncmp(content[*i + 1],
			D_REDIR_IN, 2) != 0)
	{
		if (access(content[*i + 1], F_OK) == 0)
		{
			fd = open(content[*i + 1], O_RDONLY);
			if (fd_control(fd, content[*i + 1], data) == 1)
				return (1);
			dup2(fd, 0);
			close(fd);
		}
		else
			return (fd_control(-1, content[*i + 1], data), 1);
		(*i)++;
	}
	return (0);
}

int	change_dup_2(int *i, char **content, t_data *data)
{
	if (content[*i + 1] != NULL && ft_strncmp(content[*i],
			D_REDIR_OUT, 2) == 0)
	{
		if (handle_double_redir_out(content, i, data) == 1)
			return (1);
	}
	else if (!ft_strncmp(content[*i], D_REDIR_IN_2, 3))
	{
		if (handle_double_redir_in(content, i, data) == 1)
			return (1);
	}
	else if (ft_strncmp(content[*i], D_REDIR_OUT_2, 3) == 0)
	{
		if (handle_double_redir_out_2(content, i, data) == 1)
			return (1);
	}
	else if (ft_strncmp(content[*i], D_REDIR_IN, 2) == 0)
	{
		if (handle_double_redir_in_2(content, i, data) == 1)
			return (1);
	}
	return (0);
}

int	change_dup(t_token token, t_data *data)
{
	int		i;
	char	**content;

	i = 0;
	content = token.after_redir;
	while (content[i] != NULL)
	{
		if (change_dup_2(&i, content, data) == 1)
			return (1);
		i++;
	}
	return (0);
}
