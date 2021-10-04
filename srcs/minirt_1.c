/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 20:55:18 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 22:31:11 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			main(int argc, char **argv)
{
	t_rt		*rt;

	rt = NULL;
	if (BUFFER_SIZE < 1)
		return (ft_error_exit_2(-13));
	if (argc < 2 || argc > 3 || ft_ext(argv[1], ".rt") || \
	(argc == 3 && ft_strcmp(argv[2], "--save")))
		return (ft_error_exit_2(-14));
	if (!(rt = (t_rt*)malloc(sizeof(t_rt))))
		return (ft_error_exit_2(-2));
	ft_setup_rt(rt);
	parser(rt, argv[1]);
	rt->c = rt->c1;
	if (rt->error == 0 && (rt->nc == 0 || rt->e_a == 0 || rt->e_r == 0))
		rt->error = -5;
	if (rt->error != 0)
		return (ft_error(rt));
	if (!(rt->name = ft_strdup(argv[1])))
		return (ft_error(rt));
	if (argc == 2)
		return (ft_do_screen(rt));
	else if (argc == 3)
		return (ft_do_bmp(rt));
	return (0);
}

int			ft_do_screen(t_rt *rt)
{
	if (!(rt->m_p = mlx_init()))
		return (ft_error_mlx(rt, 0));
	if (!(rt->img = mlx_new_image(rt->m_p, rt->rx, rt->ry)))
		return (ft_error_mlx(rt, -1));
	if (!(rt->addr = mlx_get_data_addr(rt->img, &rt->bits_per_pixel, \
	&rt->line_length, &rt->endian)))
		return (ft_error_mlx(rt, -2));
	if (!(rt->w_p = mlx_new_window(rt->m_p, rt->rx, rt->ry, "miniRT")))
		return (ft_error_mlx(rt, -3));
	mlx_loop_hook(rt->m_p, ft_change_c, rt);
	mlx_loop(rt->m_p);
	return (0);
}

int			ft_do_bmp(t_rt *rt)
{
	int		r;

	r = 0;
	if (!(rt->m_p = mlx_init()))
		return (ft_error_mlx(rt, 0));
	if (!(rt->img = mlx_new_image(rt->m_p, rt->rx, rt->ry)))
		return (ft_error_mlx(rt, -1));
	if (!(rt->addr = mlx_get_data_addr(rt->img, &rt->bits_per_pixel, \
	&rt->line_length, &rt->endian)))
		return (ft_error_mlx(rt, -2));
	ft_scene_new(rt);
	r = export_bmp(rt);
	free(rt->name);
	ft_free_rt(rt);
	return (r);
}

int			ft_change_c(t_rt *rt)
{
	mlx_hook(rt->w_p, 2, 1L << 0, ft_push, rt);
	mlx_hook(rt->w_p, 3, 1L << 1, ft_release, rt);
	mlx_hook(rt->w_p, 17, 1L << 17, ft_exit, rt);
	if (rt->nto > 0 && rt->nto <= rt->no && (rt->rot_up != 0 || \
	rt->rot_r != 0 || rt->rot_n != 0))
		obj_rotate(rt);
	else if (rt->nto > 0 && rt->nto <= rt->no && (rt->back != 0 || \
	rt->up != 0 || rt->right != 0))
		obj_move(rt);
	else if (rt->nto > 0 && rt->nto > rt->no && rt->nto <= rt->no + rt->nl && \
	(rt->back != 0 || rt->up != 0 || rt->right != 0))
		light_move(rt);
	else if (rt->nto == 0)
		cam_move(rt);
	ft_scene_new(rt);
	mlx_put_image_to_window(rt->m_p, rt->w_p, rt->img, 0, 0);
	mlx_do_sync(rt->m_p);
	return (0);
}

int			ft_exit(t_rt *rt)
{
	mlx_destroy_image(rt->m_p, rt->img);
	mlx_clear_window(rt->m_p, rt->w_p);
	mlx_destroy_window(rt->m_p, rt->w_p);
	free(rt->name);
	ft_free_rt(rt);
	exit(0);
}
