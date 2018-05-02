/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:35:41 by mray              #+#    #+#             */
/*   Updated: 2018/02/21 19:35:53 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *s_cpy;
	unsigned char cb;

	cb = c;
	s_cpy = (unsigned char *)s;
	while (n > 0)
	{
		if (*s_cpy == cb)
			return (s_cpy);
		s_cpy++;
		n--;
	}
	return (NULL);
}
