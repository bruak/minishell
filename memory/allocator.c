/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:43:14 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/18 12:46:35 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "allocator.h"
#define GOOD_EXIT 1
#define BAD_EXIT  0

/*
* This function returns head of memory blocks list.
*/
t_memory_block	*get_memory_blocks(void)
{
	static t_memory_block	memory_blocks = {NULL, NULL};

	return (&memory_blocks);
}

/**
* This function basically adds new element to the our memory blocks list.
*/
int	append_memory_block(void *ptr)
{
	t_memory_block	*memory_blocks;
	t_memory_block	*new;

	if (!ptr)
		return (BAD_EXIT);
	new = ALLOCATE_MEMORY(sizeof(t_memory_block));
	if (!new)
		return (BAD_EXIT);
	*new = (t_memory_block){.ptr = ptr, .next = NULL};
	memory_blocks = get_memory_blocks();
	while (memory_blocks->next != NULL)
		memory_blocks = memory_blocks->next;
	memory_blocks->next = new;
	return (GOOD_EXIT);
}

/**
* This function basically scans memory 
* blocks to find pointer given and removes it.
*/
int	remove_memory_block(void *ptr)
{
	t_memory_block	*cur;
	t_memory_block	*prev;

	if (!ptr)
		return (BAD_EXIT);
	cur = get_memory_blocks();
	while (cur != NULL)
	{
		if (cur->ptr == ptr)
		{
			prev->next = cur->next;
			FREE_MEMORY(cur);
			return (GOOD_EXIT);
		}
		prev = cur;
		cur = cur->next;
	}
	return (BAD_EXIT);
}

/**
* if success, returns allocated memory block.
* otherwise, frees ALL memory blocks and returns null pointer.
*/
void	*safe_malloc(int size)
{
	void	*ptr;

	ptr = ALLOCATE_MEMORY(size);
	if (!ptr)
	{
		free_memory();
		return (NULL);
	}
	if (!append_memory_block(ptr))
	{
		FREE_MEMORY(ptr);
		free_memory();
		return (NULL);
	}
	return (ptr);
}

/**
* frees memory block which allocated by using safe_malloc function.
*/
void	safe_free(void *ptr)
{
	if (!ptr)
		return ;
	remove_memory_block(ptr);
	FREE_MEMORY(ptr);
}
