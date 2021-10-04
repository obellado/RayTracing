/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 05:54:56 by obellado          #+#    #+#             */
/*   Updated: 2021/01/24 20:29:29 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				ft_free(char **str, int r)
{
	if (*str && r != 1)
	{
		free(*str);
		*str = NULL;
	}
	return (r);
}

char			*ft_check_tail_create_p(char *tail, char **line)
{
	char			*p;
	int				i;

	p = NULL;
	i = -1;
	if (tail)
		if ((p = ft_strchr(tail, '\n')))
		{
			*p++ = '\0';
			*line = ft_strdup(tail);
			while (p[++i] != '\0')
				tail[i] = p[i];
			tail[i] = '\0';
		}
		else
		{
			*line = ft_strdup(tail);
			while (tail[++i] != '\0')
				tail[i] = '\0';
		}
	else
		*line = ft_strdup("");
	return (p);
}

int				gnl(int fd, char **line, char **tail)
{
	char			*buf;
	int				n;
	char			*p;
	char			*tmp;

	if (!(buf = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	n = 1;
	p = ft_check_tail_create_p(*tail, line);
	while (!p && (n = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[n] = '\0';
		if ((p = ft_strchr(buf, '\n')))
		{
			*p++ = '\0';
			ft_free(tail, 0);
			if (!(*tail = ft_strdup(p)))
				n = -1;
		}
		tmp = *line;
		*line = ft_strjoin(tmp, buf);
		free(tmp);
	}
	free(buf);
	return (n);
}

int				get_next_line(int fd, char **line)
{
	static char		*tail;
	int				n;

	if (fd < 0 || BUFFER_SIZE <= 0 || !(line))
		return (ft_free(&tail, -1));
	n = gnl(fd, line, &tail);
	if (!(*line) || n == -1)
		return (ft_free(&tail, -1));
	return (n > 0) ? 1 : ft_free(&tail, 0);
}
