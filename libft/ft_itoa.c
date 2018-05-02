/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 14:00:45 by mray              #+#    #+#             */
/*   Updated: 2018/02/23 14:00:45 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int n)
{
	char *str;

	if (!(str = (char *)ft_memalloc(sizeof(*str) + (get_num_digi(n)))))
		return (NULL);
	put_base(n, str, get_num_digi(n) - 1);
	str[get_num_digi(n)] = '\0';
	return (str);
}
