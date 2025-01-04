/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/18 12:37:17 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"
#include "../memory/allocator.h"

void	handle_home(t_data *data)
{
	char	*tmp;

	tmp = cd_env(data, HOME);
	if (tmp == NULL)
	{
		ft_putstr_fd(HOME_ERR, 2);
		return ;
	}
	safe_free(data->old_pwd);
	data->old_pwd = getcwd(NULL, 0);
	chdir(tmp);
	new_pwd(data);
}

void	ft_cd(t_data *data, char **args)
{
	char	*tmp;

	if (args[0] == NULL || ft_strncmp(args[0], D_TILDE, 1) == 0)
		handle_home(data);
	else if (ft_strncmp(args[0], DOT_NUL, 3) == 0)
	{
		tmp = getcwd(NULL, 0);
		safe_free(data->old_pwd);
		data->old_pwd = ft_strdup(tmp);
		free(tmp);
		chdir("..");
		new_pwd(data);
		data->exit_code = 0;
	}
	else if (ft_strncmp(args[0], D_HYPHEN, 1) == 0)
		handle_low_ld_pwd(data);
	else
	{
		create_tmp(args, data);
		handle_access(data, args);
	}
}

void	ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	ft_putstr_fd(tmp, 1);
	safe_free(tmp);
	ft_putstr_fd(D_NEWLINE, 1);
}

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i].key)
	{
		ft_putstr_fd(data->env[i].key, 1);
		ft_putstr_fd(D_EQ, 1);
		ft_putstr_fd(data->env[i].value, 1);
		ft_putstr_fd(D_NEWLINE, 1);
		i++;
	}
	data->exit_code = 0;
}

void	ft_exit(char **args, int exit_code, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		while (args[i][j])
			numeric_argument_required_error(args, i, &j);
		i++;
	}
	i = 1;
	while (args[i])
		i++;
	if (i == 1)
		free_for_ctrld_and_exit(data, exit_code);
	else if (i == 2)
		free_for_crtrld_and_atoiexit(data, args);
	else
	{
		ft_putstr_fd(EXIT_NWLINE, 2);
		ft_putstr_fd(MINISHELL_EXIT, 2);
		return ;
	}
}
