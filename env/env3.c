/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoykan <bsoykan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/01/22 16:54:51 by bsoykan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"

void	*get_exp(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	if (!env)
		return (ft_putstr_fd(ENV_ERROR, 2), exit(1), (void *)0);
	data->export = set_exp(env, i);
	return ((void *)0);
}

void	set_env_key_value_null(t_env *env, int j)
{
	env[j + 1].key = NULL;
	env[j + 1].value = NULL;
}
