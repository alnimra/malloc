/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:56:25 by mray              #+#    #+#             */
/*   Updated: 2018/02/22 19:56:25 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*fresh_str;
	size_t	i;

	if (!s || !(fresh_str = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (++i < len)
		*(fresh_str + i) = *(s + start + i);
	return (fresh_str);
}
