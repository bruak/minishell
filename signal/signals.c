/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoykan <bsoykan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:32:48 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/13 15:32:56 by bsoykan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"
#include "sys/signal.h"
#include <stdio.h>
#include <readline/readline.h>

void	signal_direction(int sig)
{
	if (sig == SIGINT)
	{
		if (g_signal == IF_HEREDOC_SIGNAL)
		{
			exit (IF_SIGEXIT);
		}
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	signal_action(void)
{
	signal(SIGINT, signal_direction);
	signal(SIGQUIT, signal_direction);
}
