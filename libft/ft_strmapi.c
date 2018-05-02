/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:58:46 by mray              #+#    #+#             */
/*   Updated: 2018/02/22 17:58:46 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*n_str;
	unsigned int	i;

	i = -1;
	if (!f || !s || !(n_str = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (*(s + ++i))
		*(n_str + i) = f(i, *(s + i));
	return (n_str);
}
