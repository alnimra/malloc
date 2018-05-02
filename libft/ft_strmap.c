/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:10:21 by mray              #+#    #+#             */
/*   Updated: 2018/02/22 17:10:21 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*n_str;
	int		i;

	i = -1;
	if (!f || !s || !(n_str = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (*(s + ++i))
		*(n_str + i) = f(*(s + i));
	return (n_str);
}
