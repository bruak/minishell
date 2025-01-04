/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:29:34 by mkocaman          #+#    #+#             */
/*   Updated: 2024/02/29 18:29:34 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../memory/allocator.h"
#include "../library/minishell.h"
#include <stdio.h>
#include <readline/readline.h>

int	heredoc(int fd, char *limiter)
{
	char	*line;

	g_signal = IF_HEREDOC_SIGNAL;
	while (1)
	{
		line = NULL;
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			close(fd);
			safe_free(line);
			exit (0);
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		safe_free(line);
	}
	close(fd);
	return (0);
}
