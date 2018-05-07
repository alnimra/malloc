/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:03:03 by mray              #+#    #+#             */
/*   Updated: 2018/02/26 14:03:03 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MALLOC_H
# define _MALLOC_H
# include "libft.h"
# include <unistd.h>
# include <sys/mman.h>
# include <stdint.h>
# include <inttypes.h>
# define TINY 128
# define SMALL 1024
# define LARGE 1025
# define STATUS_FREE 0
# define STATUS_INUSE 1

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();

typedef struct	s_mlist
{
	void			*ptr_start;
	int				length;
	int				status;
	struct s_mlist	*page_start;
	struct s_mlist	*next;
}				t_mlist;

typedef struct	s_hippocampus
{
	int		page_size;
	t_mlist *tiny_head;
	t_mlist *tiny_last;
	t_mlist *small_head;
	t_mlist *small_last;
	t_mlist *large_head;
	t_mlist *large_last;
}				t_hippocampus;

t_hippocampus *true_hippocampus;
#endif
