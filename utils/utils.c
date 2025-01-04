/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoykan <bsoykan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:13:42 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/15 17:45:02 by bsoykan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"
#include "../libft/libft.h"

int	is_metacharacter(char c)
{
	if (is_whitespace(c) || (ft_isalpha(c) || ft_isdigit(c)))
		return (1);
	return (0);
}

void	oldpwd_free(t_data *data, int i, char *tmp)
{
	safe_free(data->env[i].value);
	data->env[i].value = ft_strdup(data->old_pwd);
	safe_free(data->export[i].value);
	data->export[i].value = ft_strdup("=\"");
	tmp = ft_strjoin(data->export[i].value, data->old_pwd);
	safe_free(data->export[i].value);
	data->export[i].value = ft_strjoin(tmp, "\"");
	safe_free(tmp);
}

void	new_pwd(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->env[i].key)
	{
		if (ft_strncmp(data->env[i].key, "PWD", 4) == 0)
		{
			safe_free(data->env[i].value);
			tmp = getcwd(NULL, 0);
			data->env[i].value = ft_strdup(tmp);
			safe_free(data->export[i].value);
			data->export[i].value = ft_strdup(tmp);
			safe_free(tmp);
		}
		else if (ft_strncmp(data->export[i].key, "OLDPWD", 7) == 0)
			oldpwd_free(data, i, tmp);
		i++;
	}
}
