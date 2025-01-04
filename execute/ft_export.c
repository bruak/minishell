/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
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
#include <stdio.h>

char	*get_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	return (name);
}

int	check_input(t_data *data, char *str)
{
	int		i;

	i = 0;
	if (str[0] == '=')
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		data->exit_code = 1;
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!is_metacharacter(str[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			data->exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export(t_data *data, char **str)
{
	char	*name;
	char	*value;

	data->i = -1;
	while (str[++data->i])
	{
		if (ft_export_isredir_or_inputcheck(data, str, data->i))
			return ;
		name = get_name(str[data->i]);
		data->flag_for_export = is_already_exist(data, name);
		if (ft_strchr(str[data->i], '='))
		{
			value = (ft_strchr(str[data->i], '=') + 1);
			if (!data->flag_for_export)
				if_there_is_no_variable(data, str, name, value);
			else
				if_it_already_exists(data, name, str, value);
		}
		else if (!data->flag_for_export)
			if_export_flag_false(data, name);
		safe_free(name);
		data->exit_code = 0;
	}
}

void	rework_export(t_data *data)
{
	int		i;
	int		j;
	char	**exp_tmp;

	i = 0;
	j = 0;
	exp_tmp = data->exp;
	while (data->exp[i])
		i++;
	data->exp = safe_malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (exp_tmp[i])
	{
		data->exp[i] = ft_strdup(exp_tmp[i]);
		i++;
	}
	data->exp[i] = ft_strdup(data->tmp);
	data->exp[i + 1] = NULL;
	while (exp_tmp[j])
	{
		safe_free(exp_tmp[j]);
		j++;
	}
	safe_free(exp_tmp);
	safe_free(data->tmp);
}
