/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoykan <bsoykan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:30:23 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/15 17:45:06 by bsoykan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"
#include "../libft/libft.h"

void	your_function(t_data *data, char **args)
{
	char	*tmp;

	tmp = create_tmp(args, data);
	handle_access(data, args);
	safe_free(tmp);
}

void	handle_low_ld_pwd(t_data *data)
{
	char	*tmp;
	char	*tmp2;

	tmp = cd_env(data, "OLDPWD");
	if (tmp == NULL)
	{
		data->exit_code = 1;
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return ;
	}
	safe_free(data->old_pwd);
	tmp2 = getcwd(NULL, 0);
	data->old_pwd = ft_strdup(tmp2);
	safe_free(tmp2);
	chdir(tmp);
	new_pwd(data);
	safe_free(tmp);
	data->exit_code = 0;
}

void	move_export_entry(t_data *data, int i)
{
	char	*tmp;

	tmp = NULL;
	tmp = data->export[i].key;
	data->export[i].key = data->export[i + 1].key;
	tmp = NULL;
	safe_free(tmp);
	tmp = data->export[i].value;
	data->export[i].value = data->export[i + 1].value;
	tmp = NULL;
	safe_free(tmp);
	tmp = data->exp[i];
	data->exp[i] = data->exp[i + 1];
	tmp = NULL;
	safe_free(tmp);
	i++;
}

void	move_env_entry(t_data *data, int i)
{
	char	*tmp;

	tmp = NULL;
	tmp = data->env[i].key;
	data->env[i].key = data->env[i + 1].key;
	tmp = NULL;
	safe_free(tmp);
	tmp = data->env[i].value;
	data->env[i].value = data->env[i + 1].value;
	tmp = NULL;
	safe_free(tmp);
	tmp = data->envp[i];
	data->envp[i] = data->envp[i + 1];
	tmp = NULL;
	safe_free(tmp);
	i++;
}

void	ft_unset(t_data *data, char *str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return ;
	if (ft_strncmp(str, D_ASTERISK, 1) == 0)
	{
		while (data->env[i].key)
		{
			free_and_nullify(&data->env[i].key, &data->env[i].value);
			i++;
		}
	}
	else
		remove_entry(data, str);
	data->exit_code = 0;
}
