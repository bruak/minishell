/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:59:54 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/18 12:08:27 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../library/minishell.h"
#include "../memory/allocator.h"

void	free_export(t_data *data)
{
	int		i;

	i = 0;
	while (data->exp[i] != NULL)
	{
		safe_free(data->exp[i]);
		i++;
	}
	safe_free(data->exp);
}

void	free_for_ctrl_d(t_data *data, int flag)
{
	if (flag == 1)
		ft_free(data);
	free_exp(data);
	free_export(data);
	free_env(data);
	safe_free(data->old_pwd);
	if (flag == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(data->exit_code);
	}
	else
		ft_putstr_fd("exit\n", 1);
}

void	free_after_redir(t_data *data, int j)
{
	int	i;

	i = 0;
	while (data->token[j].after_redir[i])
	{
		safe_free(data->token[j].after_redir[i]);
		data->token[j].after_redir[i] = NULL;
		i++;
	}
}
