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

#ifndef _RTV1_H
# define _RTV1_H
# include "libft.h"
# include <math.h>
# include <unistd.h>
# define TINY 16
# define SMALL 512
# define LARGE 4000
# define STATUS_FREE 0
# define STATUS_INUSE 1

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

typedef struct s_mlist
{
	void	*ptr_start;
	int		length;
	int		status;
}				t_mlist;

typedef struct s_hippocampus
{
	int		is_hippocampus_created;
	t_mlist *tiny;
	t_mlist *small;
	t_mlist *large;
}				t_hippocampus;

t_hippocampus *true_hippocampus;
#endif
