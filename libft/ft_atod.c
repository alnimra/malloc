/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:51:51 by mray              #+#    #+#             */
/*   Updated: 2018/03/18 19:54:13 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double ft_atod(char *s)
{
	double rez = 0;
	double fact = 1;
	int	point_seen;

	point_seen = 0;
	if (*s == '-')
	{
		s++;
		fact = -1;
	};
	point_seen = 0;
	while (*s)
	{
		if (*s == '.')
		{
			point_seen = 1;
			s++;
			continue;
		}
		int d = *s - '0';
		if (d >= 0 && d <= 9)
		{
			if (point_seen)
				fact /= 10.0f;
			rez = rez * 10.0f + (double)d;
		}
		s++;
	}
	return (rez * fact);
};
