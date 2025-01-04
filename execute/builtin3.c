/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/13 14:18:37 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "../libft/libft.h"
#include "../memory/allocator.h"

void	numeric_argument_required_error(char **args, int i, int *j)
{
	if (ft_isdigit(args[i][*j]) == 0 && args[i][*j]
			!= HYPHEN && args[i][*j] != '+')
	{
		ft_putstr_fd(EXIT_NWLINE, 2);
		ft_putstr_fd("minishell: exit:", 2);
		ft_putstr_fd(args[i], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	(*j)++;
}

void	swap_and_free(char **dest, char **src)
{
	char	*tmp;

	tmp = NULL;
	tmp = *dest;
	*dest = *src;
	safe_free(tmp);
}

void	free_and_nullify(char **key, char **value)
{
	safe_free(*key);
	safe_free(*value);
	*key = NULL;
	*value = NULL;
}

void	swap_and_free_env(t_data *data, const char *str)
{
	int	i;

	i = 0;
	while (data->env[i].key)
	{
		if (!ft_strncmp(data->env[i].key, str, ft_strlen(str)))
		{
			while (data->env[i].key)
			{
				swap_and_free(&data->env[i].key, &data->env[i + 1].key);
				swap_and_free(&data->env[i].value, &data->env[i + 1].value);
				i++;
			}
			break ;
		}
		i++;
	}
}

int	is_special_arg(char *arg)
{
	return (ft_strncmp(arg, D_PIPET, 2) == 0
		|| ft_strncmp(arg, D_REDIR_OUT, 2) == 0
		|| ft_strncmp(arg, D_REDIR_IN, 2) == 0
		|| ft_strncmp(arg, D_REDIR_OUT_2, 3) == 0
		|| ft_strncmp(arg, D_REDIR_IN_2, 3) == 0);
}
