/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aborter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoykan <bsoykan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:43:21 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/15 17:39:23 by bsoykan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator.h"
#include <stdlib.h>

/**
* frees all memory blocks which allocated by using safe_malloc 
* function but does not call abort functions.
*/
void	free_memory(void)
{
	t_memory_block	*memory_blocks;
	t_memory_block	*next;

	memory_blocks = get_memory_blocks()->next;
	while (memory_blocks != NULL)
	{
		next = memory_blocks->next;
		FREE_MEMORY(memory_blocks->ptr);
		FREE_MEMORY(memory_blocks);
		memory_blocks = next;
	}
	get_memory_blocks()->next = NULL;
}
