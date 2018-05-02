/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 20:14:00 by mray              #+#    #+#             */
/*   Updated: 2018/02/22 20:14:00 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *fresh_str;

	if (!s1 || !s2 || !(fresh_str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	fresh_str = ft_strcpy(fresh_str, (char *)s1);
	return (ft_strcat(fresh_str, (char *)s2));
}
