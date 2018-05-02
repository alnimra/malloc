/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 21:23:47 by mray              #+#    #+#             */
/*   Updated: 2018/02/22 21:23:47 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		num_words;
	int		in_word;
	int		i;
	int		s_i;

	if (!s || !c || !(ret = (char **)ft_memalloc(sizeof(char*) * (g_n(s, c)))))
		return (NULL);
	i = -1;
	in_word = 0;
	num_words = 0;
	while (*(s + make_zero_from_neg(i++)))
	{
		if (!in_word && s[i] != c)
		{
			s_i = i;
			in_word = 1;
		}
		else if (in_word && (s[i] == c || s[i] == '\0'))
		{
			ret[num_words++] = ft_strsub(s, s_i, i - s_i);
			in_word = 0;
		}
	}
	return (ret);
}
