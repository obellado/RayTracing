/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:00:44 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 22:45:35 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_save_bmp(t_rt *rt, int fd, int p_size)
{
	int			j;
	int			x;
	int			y;
	int			i;

	x = 0;
	y = rt->ry - 1;
	while (y >= 0)
	{
		while (x < rt->rx)
		{
			j = *(int *)(rt->addr + (y * rt->line_length + \
			x * (rt->bits_per_pixel / 8)));
			write(fd, &j, 3);
			x++;
		}
		i = 0;
		while (i++ < p_size)
			write(fd, 0, 1);
		y--;
		x = 0;
	}
	return (0);
}

void		header_bmp(int size, t_rt *rt, int fd)
{
	char			data[54];

	ft_memset(data, 0, 54);
	ft_memcpy(data + 4, &size, 4);
	ft_memcpy(data + 18, &rt->rx, 4);
	ft_memcpy(data + 22, &rt->ry, 4);
	data[0] = 'B';
	data[1] = 'M';
	data[10] = 54;
	data[14] = 40;
	data[26] = 1;
	data[28] = 24;
	write(fd, data, 54);
}

int			export_bmp(t_rt *rt)
{
	int				fd;
	int				size;
	int				p_size;

	p_size = (4 - (rt->rx * 3) % 4) % 4;
	size = (rt->rx + p_size) * rt->ry * 3 + 54;
	if ((fd = open("rt.bmp\0", O_CREAT | O_TRUNC | O_RDWR, 0644)) < 0)
		return (ft_error_exit(-3, rt));
	header_bmp(size, rt, fd);
	ft_save_bmp(rt, fd, p_size);
	close(fd);
	return (0);
}
