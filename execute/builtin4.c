/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/14 16:35:48 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"
#include "../libft/libft.h"

void	while_process_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (is_special_arg(args[i]))
			break ;
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(D_SPACE, 1);
		i++;
	}
}

void	ft_echo(char **args)
{
	int	i;
	int	j;
	int	newline;

	newline = 1;
	i = 1;
	while (args[i] && args[i][0] == HYPHEN)
	{
		j = 1;
		while (args[i][j] == N)
			j++;
		if (args[i][j] != NUL)
			break ;
		newline = 0;
		i++;
	}
	while_process_args(args + i);
	if (newline)
		ft_putstr_fd(D_NEWLINE, 1);
}

char	*create_tmp(char **args, t_data *data)
{
	char	*tmp;

	if (args[0][0] == SLASH)
	{
		tmp = ft_strdup(args[0]);
		tmp = ft_strjoin(D_SLASH, tmp);
	}
	else
	{
		tmp = cd_env(data, BIG_PWD);
		tmp = ft_strjoin(tmp, D_SLASH);
		tmp = ft_strjoin(tmp, args[0]);
	}
	return (tmp);
}

void	handle_access(t_data *data, char **args)
{
	char	*tmp;

	if (access(args[0], F_OK) == 0)
	{
		safe_free(data->old_pwd);
		tmp = getcwd(NULL, 0);
		data->old_pwd = ft_strdup(tmp);
		safe_free(tmp);
		chdir(args[0]);
		new_pwd(data);
		data->exit_code = 0;
	}
	else
	{
		data->exit_code = 1;
		ft_putstr_fd(BASH_CD, 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(FD_ERR, 2);
	}
}

void	ft_export_2(t_data *data)
{
	int	i;

	i = 0;
	while (data->export[i].key)
	{
		ft_putstr_fd(DECLERE_X, 1);
		ft_putstr_fd(data->export[i].key, 1);
		ft_putstr_fd(data->export[i].value, 1);
		ft_putstr_fd(D_NEWLINE, 1);
		i++;
	}
}
