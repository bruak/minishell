/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:50:44 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/16 12:36:38 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"

void	remove_env_value_from_export(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (data->export[i].key)
	{
		if (!ft_strncmp(data->export[i].key, str, ft_strlen(str)))
		{
			while (data->export[i].key)
			{
				move_export_entry(data, i);
				i++;
			}
			break ;
		}
		i++;
	}
}

void	remove_entry(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (data->env[i].key)
	{
		if (!ft_strncmp(data->env[i].key, str, ft_strlen(str)))
		{
			while (data->env[i].key)
			{
				move_env_entry(data, i);
				i++;
			}
			break ;
		}
		i++;
	}
	remove_env_value_from_export(data, str);
}

int	quote_counter(t_data *data)
{
	int		i;
	char	quote;

	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == S_QUOTE || data->input[i] == D_QUOTE)
		{
			data->syntax_flag = 1;
			quote = data->input[i];
			i++;
			while (data->input[i] && data->input[i] != quote)
				i++;
			if (data->input[i] != quote)
				return (1);
			else
				data->syntax_flag = 0;
		}
		i++;
	}
	return (1);
}

void	free_for_ctrld_and_exit(t_data *data, int exit_code)
{
	free_for_ctrl_d(data, 1);
	exit(exit_code);
}

void	free_for_crtrld_and_atoiexit(t_data *data, char **args)
{
	free_for_ctrl_d(data, 1);
	exit(ft_atoi(args[1]));
}
