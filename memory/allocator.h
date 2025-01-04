/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoykan <bsoykan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:07:21 by bsoykan           #+#    #+#             */
/*   Updated: 2024/03/15 17:35:43 by bsoykan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_H
# define ALLOCATOR_H

# define ALLOCATE_MEMORY malloc
# define FREE_MEMORY free

/*
*	A struct to store memory blocks which allocated by using malloc function.
*/
typedef struct s_memory_block
{
	void					*ptr;
	struct s_memory_block	*next;
}	t_memory_block;

void			*safe_malloc(int size);
void			safe_free(void *ptr);
t_memory_block	*get_memory_blocks(void);
void			free_memory(void);

#endif
