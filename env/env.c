/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/15 12:20:05 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../memory/allocator.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

void	process_envp(char **envp, t_env *env, int *j, int *flag)
{
	int		i;
	char	*tmp;

	while (envp[*j])
	{
		i = 0;
		while (envp[*j][i] != EQ && envp[*j][i] != NUL)
			i++;
		if (envp[*j][i] == EQ && ft_strncmp(envp[*j], "OLDPWD", 6) != 0)
			env[*j].key = ft_substr(envp[*j], 0, i);
		else
		{
			*flag = 1;
			env[*j].key = ft_strdup("OLDPWD");
			tmp = getcwd(NULL, 0);
			env[*j].value = ft_strdup(tmp);
			free(tmp);
		}
		env[*j].value = ft_substr(envp[*j], i + 1, ft_strlen(envp[*j]) - i - 1);
		(*j)++;
	}
}

t_env	*set_env(char **envp, int env_count)
{
	t_env	*env;
	char	*tmp;
	int		flag;
	int		j;

	j = 0;
	flag = 0;
	tmp = NULL;
	env = (t_env *)safe_malloc(sizeof(t_env) * (env_count + 2));
	if (!env)
		return (ft_putstr_fd(MALLOC_ERROR, 2), exit(1), NULL);
	process_envp(envp, env, &j, &flag);
	if (flag == 0)
	{
		env[j].key = ft_strdup("OLDPWD");
		tmp = getcwd(NULL, 0);
		if (!tmp)
			return (ft_putstr_fd(MALLOC_ERROR, 2), exit(1), NULL);
		env[j].value = ft_strdup(tmp);
		free(tmp);
		set_env_key_value_null(env, j);
	}
	else
		just_env_key_value_null(env, j);
	return (env);
}

void	just_env_key_value_null(t_env *env, int j)
{
	env[j].key = NULL;
	env[j].value = NULL;
}

void	update_env_value_with_quotes(struct s_env *env,
	int *j, char **envp, int i)
{
	char	*temp;
	char	*substr;
	char	*old_value;

	temp = env[*j].value;
	env[*j].value = ft_strjoin_char(temp, D_QUOTE);
	safe_free(temp);
	temp = env[*j].value;
	substr = ft_substr(envp[*j], i + 1, ft_strlen(envp[*j]) - i - 1);
	env[*j].value = ft_strjoin(temp, substr);
	safe_free(temp);
	safe_free(substr);
	old_value = env[*j].value;
	env[*j].value = ft_strjoin_char(old_value, D_QUOTE);
	safe_free(old_value);
}

void	process_env_entry(char **envp, struct s_env *env, int *j)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (envp[*j][i] != EQ && envp[*j][i] != NUL)
		i++;
	if (envp[*j][i] == EQ)
	{
		flag = 1;
		env[*j].key = ft_substr(envp[*j], 0, i);
		env[*j].value = ft_strdup(D_EQ);
	}
	else
	{
		env[*j].key = ft_strdup(envp[*j]);
		env[*j].value = NULL;
	}
	if (flag)
		update_env_value_with_quotes(env, j, envp, i);
	(*j)++;
}
