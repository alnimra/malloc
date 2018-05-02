/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 13:57:20 by mray              #+#    #+#             */
/*   Updated: 2018/03/07 13:57:23 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*make_uppercase(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

static int		ft_char_in_base(char c, int b)
{
	if (b <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= ('A' + b - 10)));
}

int				ft_atoi_base(char *str, int b)
{
	int res;
	int is_neg;

	str = make_uppercase(str);
	res = 0;
	if (b <= 1 || b >= 35)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' ||
			*str == '\r' || *str == '\v')
		str++;
	is_neg = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_char_in_base(*str, b))
	{
		if (*str - 'A' >= 0)
			res = res * b + (*str - 'A' + 10);
		else
			res = res * b + (*str - '0');
		str++;
	}
	return (res * is_neg);
}
