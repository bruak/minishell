/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:09:43 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/18 12:17:47 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "library/minishell.h"
#include "memory/allocator.h"
#include "libft/libft.h"

int	g_signal;

void	starter_function(t_data *data, char **envp)
{
	char	*tmp;
	int		i;

	i = 0;
	data->envp = envp;
	while (envp[i])
		i++;
	data->exp = (char **)safe_malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (envp[i])
	{
		data->exp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp = getcwd(NULL, 0);
	data->exp[i] = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	data->exp[i + 1] = NULL;
}

int	pipe_checker(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd[i])
	{
		if (ft_strncmp(data->cmd[i], "|", 2) == 0
			&& (data->cmd[i + 1] == NULL
				|| ft_strncmp(data->cmd[i + 1], "|", 1) == 0))
			return (1);
		i++;
	}
	return (0);
}

void	input_redir_execute(t_data *data)
{
	handle_input(data);
	redir_lexer(data);
	if (pipe_checker(data))
	{
		ft_putstr_fd(SYNTX_ERR, 2);
		ft_free(data);
		data->exit_code = 127;
		return ;
	}
	execute(data);
}

void	process_loop(t_data *data)
{
	while (1)
	{
		data->syntax_flag = 0;
		data->input = readline(CLRFUL_MINISHELL);
		if (!data->input)
			free_for_ctrl_d(data, 0);
		if (ft_strlen(data->input))
		{
			add_history(data->input);
			if (quote_counter(data)
				&& data->syntax_flag == 1)
			{
				ft_putstr_fd(SYNTX_ERR, 2);
				safe_free(data->input);
				data->exit_code = 127;
				continue ;
			}
			input_redir_execute(data);
		}
		else
			free(data->input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 1 && !av)
		return (erro_premium(FUNNY_ERROR), 2);
	initialize_env(&data, envp);
	signal_action();
	process_loop(&data);
}
