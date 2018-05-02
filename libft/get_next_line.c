/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 03:51:40 by mray              #+#    #+#             */
/*   Updated: 2018/02/25 03:51:40 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		take_newline_out(char **str, char **line)
{
	char *tmp;

	if (!(tmp = ft_fst_strchr(*str, '\n')))
		return (0);
	*line = ft_strsub(*str, 0, tmp - *str);
	ft_memmove(*str, tmp + 1, ft_strlen(tmp));
	return (1);
}

int		read_buffsize_till_newline(int const fd, char *file_dt[FD_LIMIT],
							char **line)
{
	int		byte_size;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

	if (!(file_dt[fd]))
		if (!(file_dt[fd] = ft_strnew(1)) || (read(fd, buf, 0) < 0))
			return (-1);
	while ((byte_size = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[byte_size] = '\0';
		tmp = file_dt[fd];
		if (!(file_dt[fd] = ft_strjoin(file_dt[fd], buf)))
			return (-1);
		ft_memdel((void **)&tmp);
		if (take_newline_out(&file_dt[fd], line))
			return (1);
	}
	if (file_dt[fd] && !(file_dt[fd][0] == '\0'))
	{
		*line = file_dt[fd];
		file_dt[fd] = NULL;
		return (1);
	}
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	static char	*file_data[FD_LIMIT];
	int			error_check;

	if (!line || fd < 0 || fd > FD_LIMIT)
		return (-1);
	if (file_data[fd] && take_newline_out(&file_data[fd], line))
		return (1);
	error_check = read_buffsize_till_newline(fd, file_data, line);
	return (error_check);
}
