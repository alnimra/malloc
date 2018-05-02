/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 17:22:56 by mray              #+#    #+#             */
/*   Updated: 2018/02/19 17:23:10 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*src_cpy;
	char	*dst_cpy;
	size_t	i;

	src_cpy = (char *)src;
	dst_cpy = (char *)dst;
	i = -1;
	while (++i < n)
		*(dst_cpy + i) = *(src_cpy + i);
	return (dst);
}
