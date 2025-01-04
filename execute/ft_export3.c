/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoykan <bsoykan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:36:02 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/15 15:49:20 by bsoykan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"
#include "../libft/libft.h"

void	ft_export_adding_new_key(t_data *data, char **str, int i)
{
	int	j;

	j = 0;
	while (data->envp[j])
		j++;
	data->envp[j] = ft_strdup(str[i]);
	data->envp[j + 1] = NULL;
	free_env(data);
	get_env(data, data->envp);
}

void	update_export_env_value(t_data *data, char *name, char **str, int i)
{
	int	j;

	j = 0;
	while (data->envp[j] && ft_strncmp(data->envp[j], name,
			ft_strlen(name)))
		j++;
	if (data->envp[j] == NULL)
		data->envp[j + 1] = NULL;
	data->envp[j] = ft_strdup(str[i]);
	free_env(data);
	get_env(data, data->envp);
}

void	update_export_value(t_data *data, char *name, char *value)
{
	int		i;

	i = 0;
	while (data->export[i].key)
	{
		if (ft_strncmp(data->export[i].key, name,
				(ft_strlen(name) + ft_strlen(data->export[i].key))) == 0)
		{
			safe_free(data->export[i].value);
			data->export[i].value = ft_strjoin("=", value);
			data->exp[i] = ft_strdup(data->export[i].key);
			data->exp[i] = ft_strjoin(data->exp[i], data->export[i].value);
			free_exp(data);
			get_exp(data, data->exp);
		}
		i++;
	}
}

void	if_export_flag_false(t_data *data, char *name)
{
	int		j;

	j = 0;
	while (data->export[j].key)
		j++;
	data->export[j].key = ft_strdup(name);
	data->export[j].value = NULL;
	data->tmp = ft_strdup(name);
	rework_export(data);
	free_exp(data);
	get_exp(data, data->exp);
}

int	is_already_exist(t_data *data, char *name)
{
	int		i;

	i = 0;
	while (data->export[i].key)
	{
		if (ft_strncmp(data->export[i].key, name,
				(ft_strlen(name) + ft_strlen(data->export[i].key))) == 0)
			return (1);
		i++;
	}
	return (0);
}
