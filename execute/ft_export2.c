/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:36:02 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/18 12:12:11 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"

void	if_there_is_no_variable(t_data *data, char **str,
		char *name, char *value)
{
	ft_export_adding_new_key(data, str, data->i);
	ft_export_adding_new_key2(data, name, value);
}

void	if_it_already_exists(t_data *data, char *name, char **str, char *value)
{
	if (data->flag_for_export)
		update_export_env_value(data, name, str, data->i);
	update_export_value(data, name, value);
}

int	ft_export_isredir_or_inputcheck(t_data *data, char **str, int i)
{
	if (is_redir(str[i]))
		return (1);
	if (ft_export_input_check(data, str, i))
		return (1);
	return (0);
}

int	ft_export_input_check(t_data *data, char **str, int i)
{
	while (check_input(data, str[i]))
	{
		i++;
		if (!str[i])
			return (1);
	}
	return (0);
}

void	ft_export_adding_new_key2(t_data *data, char *name, char *value)
{
	int	j;

	j = 0;
	while (data->export[j].key)
		j++;
	data->export[j].key = ft_strdup(name);
	data->tmp = ft_strjoin("=", value);
	data->tmp = ft_strjoin(name, data->tmp);
	rework_export(data);
	free_exp(data);
	get_exp(data, data->exp);
}
