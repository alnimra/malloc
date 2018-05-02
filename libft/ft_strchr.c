/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:37:40 by mray              #+#    #+#             */
/*   Updated: 2018/02/22 13:37:40 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*s_cpy;

	i = -1;
	s_cpy = (char *)s;
	while (++i < ft_strlen(s) + 1)
	{
		if (s_cpy[i] == c)
			return (s_cpy + i);
	}
	return (NULL);
}
