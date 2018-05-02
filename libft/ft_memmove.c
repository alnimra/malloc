/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 18:20:52 by mray              #+#    #+#             */
/*   Updated: 2018/02/19 18:21:12 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	tmp_len;
	char	*src_cpy;
	char	*dst_cpy;

	src_cpy = (char *)src;
	dst_cpy = (char *)dst;
	if (src_cpy < dst_cpy)
	{
		while (len--)
			*(dst_cpy + len) = *(src_cpy + len);
	}
	else
	{
		tmp_len = len - 1;
		while (len--)
			*(dst_cpy + tmp_len - len) = *(src_cpy + tmp_len - len);
	}
	return (dst);
}
