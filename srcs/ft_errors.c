/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:59:39 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 23:05:24 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_error(t_rt *rt)
{
	if (rt->error == -1 || rt->error <= -5)
		write(1, "Error\nMistake in *.rt\n", 22);
	else if (rt->error == -2)
		write(1, "Error\nFail: memory allocation\n", 30);
	else if (rt->error == -3)
		write(1, "Error\nFail: creation *.bmp\n", 27);
	else if (rt->error == -4)
		write(1, "Error\nFail: open *.rt\n", 22);
	if (rt->error == -5)
		write(1, "No camera in scene.\n", 20);
	if (rt->error == -6)
		write(1, "Misspelled color.\n", 18);
	if (rt->error == -7)
		write(1, "Length of orientation vector = 0.\n", 34);
	if (rt->error == -8)
		write(1, "Coordinate of orient. vector is not in right range\n", 51);
	if (rt->error == -9)
		write(1, "Extra line.\n", 12);
	if (rt->error == -10)
		write(1, "Invalid FOV of camera.\n", 23);
	if (rt->error == -15)
		write(1, "Size <= 0.\n", 11);
	ft_free_rt(rt);
	return (-1);
}

int			ft_error_re(t_rt *rt)
{
	if (rt->error == -1 || rt->error <= -5)
		write(1, "Error\nMistake in *.rt\n", 22);
	else if (rt->error == -2)
		write(1, "Error\nFail: memory allocation\n", 30);
	else if (rt->error == -3)
		write(1, "Error\nFail: creation *.bmp\n", 27);
	else if (rt->error == -4)
		write(1, "Error\nFail: open *.rt\n", 22);
	if (rt->error == -5)
		write(1, "No camera in scene.\n", 20);
	if (rt->error == -6)
		write(1, "Misspelled color.\n", 18);
	if (rt->error == -7)
		write(1, "Length of orientation vector = 0.\n", 34);
	if (rt->error == -8)
		write(1, "Coordinate of orient. vector is not in right range\n", 51);
	if (rt->error == -9)
		write(1, "Extra line.\n", 12);
	if (rt->error == -10)
		write(1, "Invalid FOV of camera.\n", 23);
	mlx_destroy_image(rt->m_p, rt->img);
	free(rt->name);
	ft_free_rt(rt);
	exit(-1);
	return (-1);
}

int			ft_error_exit_2(int err)
{
	if (err == -2)
		write(1, "Error\nFail: memory allocation\n", 30);
	else if (err == -3)
		write(1, "Error\nFail: creation *.bmp\n", 27);
	else if (err == -13)
		write(1, "Error\nWrong global variables.\n", 30);
	else if (err == -14)
		write(1, "Error\nWrong arguments.\n", 23);
	return (-1);
}

int			ft_check_cam(t_cam *c, t_rt *rt)
{
	if (rt->error != 0)
		return (0);
	if (vect_len(c->nor) == 0)
		ft_error_exit(-7, rt);
	if (c->fov >= 180 || c->fov <= 0)
		ft_error_exit(-10, rt);
	if (c->nor.x > 1 || c->nor.x < -1 || c->nor.y > 1 || \
	c->nor.y < -1 || c->nor.z > 1 || c->nor.z < -1)
		ft_error_exit(-8, rt);
	c->nor = vect_norm(c->nor);
	ft_bzero(&c->up, sizeof(t_vect));
	if (c->nor.y != -1)
		c->up.y = -1;
	else
		c->up.z = -1;
	return (0);
}

int			ft_error_mlx(t_rt *rt, int n)
{
	if (n == 0)
		write(1, "Error\nCouldn't do mlx_init.\n", 28);
	else if (n == -1)
		write(1, "Error\nCouldn't make the image.\n", 31);
	else if (n == -2)
		write(1, "Error\nCouldn't get an address of image.\n", 40);
	else if (n == -3)
		write(1, "Error\nCouldn't make a new window.\n", 34);
	free(rt->name);
	ft_free_rt(rt);
	return (-1);
}
