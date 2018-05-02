/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 17:42:41 by mray              #+#    #+#             */
/*   Updated: 2018/02/19 17:42:58 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*src_cpy;
	unsigned char	*dst_cpy;

	i = 0;
	src_cpy = (unsigned char*)src;
	dst_cpy = (unsigned char*)dst;
	while (i < n)
	{
		*(dst_cpy + i) = *(src_cpy + i);
		if (*(src_cpy + i++) == (unsigned char)c)
			return (dst_cpy + i);
	}
	return (NULL);
}
