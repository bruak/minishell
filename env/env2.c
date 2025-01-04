/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:50:21 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/16 16:00:39 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"
#include "../libft/libft.h"

char	*cd_env(t_data *data, char *str)
{
	int		i;
	char	*result;

	i = 0;
	if (!str)
		return (NULL);
	while (data->env[i].key && ft_strncmp(data->env[i].key,
			str, ft_strlen(str)))
		i++;
	if (data->env[i].key && !ft_strncmp(data->env[i].key, str, ft_strlen(str)))
	{
		result = data->env[i].value;
		return (ft_strdup(result));
	}
	return (NULL);
}

int	env2(t_data *data, char **tmp2)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (data->env[i].key)
	{
		if (data->env[i].key != NULL && !ft_strncmp(data->env[i].key, *tmp2,
				ft_strlen(*tmp2) + 1))
		{
			tmp = ft_strdup(data->env[i].value);
			if (tmp)
			{
				*tmp2 = ft_strdup(tmp);
				safe_free (tmp);
			}
			else
				*tmp2 = ft_strdup("");
			return (1);
		}
		i++;
	}
	return (0);
}

void	initialize_env(t_data *data, char **envp)
{
	char	*tmp;

	data->exit_code = 0;
	starter_function(data, envp);
	tmp = getcwd(NULL, 0);
	data->old_pwd = ft_strdup(tmp);
	data->token = 0;
	data->cmd = 0;
	safe_free(tmp);
	get_env(data, data->envp);
	get_exp(data, data->exp);
	new_pwd(data);
}

void	*get_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env = set_env(env, i);
	data->exit_code = 0;
	return ((void *)0);
}

t_env	*set_exp(char **envp, int env_count)
{
	t_env	*env;
	int		j;

	j = 0;
	env = (t_env *)safe_malloc(sizeof(t_env) * (env_count + 1));
	while (envp[j] != NULL)
		process_env_entry(envp, env, &j);
	env[j].key = NULL;
	env[j].value = NULL;
	return (env);
}
