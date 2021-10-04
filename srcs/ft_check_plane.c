/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:48:20 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 23:07:39 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_check_sq(t_obj *sq)
{
	ft_bzero(&sq->xyz3, sizeof(t_vect));
	if (sq->xyz.y != -1 && sq->xyz.y != 1)
		sq->xyz3.y = -1;
	else
		sq->xyz3.z = -1;
	sq->xyz2 = vect_mult(vect_norm(vect_cross(sq->xyz, sq->xyz3)), sq->r);
	sq->xyz3 = vect_mult(vect_norm(vect_cross(sq->xyz2, sq->xyz)), sq->r);
	sq->t1 = vect_sum(vect_sum(sq->xyz1, sq->xyz2), sq->xyz3);
	sq->t2 = vect_sub(vect_sum(sq->xyz1, sq->xyz2), sq->xyz3);
	sq->t3 = vect_sub(vect_sub(sq->xyz1, sq->xyz2), sq->xyz3);
	sq->t4 = vect_sum(vect_sub(sq->xyz1, sq->xyz2), sq->xyz3);
	sq->xyz3 = vect_norm(sq->xyz3);
	sq->xyz2 = vect_norm(sq->xyz2);
	return (0);
}

int			ft_re_check_sq(t_obj *sq)
{
	float		len;

	len = vect_len(vect_sub(sq->xyz3, sq->xyz));
	if (len > 0.001 && len < 1.999)
		sq->xyz2 = vect_mult(vect_norm(vect_cross(sq->xyz, sq->xyz3)), sq->r);
	sq->xyz3 = vect_mult(vect_norm(vect_cross(sq->xyz2, sq->xyz)), sq->r);
	if (len <= 0.001 || len >= 1.999)
		sq->xyz2 = vect_mult(vect_norm(vect_cross(sq->xyz, sq->xyz3)), sq->r);
	sq->t1 = vect_sum(vect_sum(sq->xyz1, sq->xyz2), sq->xyz3);
	sq->t2 = vect_sub(vect_sum(sq->xyz1, sq->xyz2), sq->xyz3);
	sq->t3 = vect_sub(vect_sub(sq->xyz1, sq->xyz2), sq->xyz3);
	sq->t4 = vect_sum(vect_sub(sq->xyz1, sq->xyz2), sq->xyz3);
	sq->xyz3 = vect_norm(sq->xyz3);
	sq->xyz2 = vect_norm(sq->xyz2);
	return (0);
}

int			ft_check_tr(t_obj *tr)
{
	tr->xyz.x = (tr->t2.y - tr->t1.y) * (tr->t3.z - tr->t1.z) - \
	(tr->t3.y - tr->t1.y) * (tr->t2.z - tr->t1.z);
	tr->xyz.y = (-1) * (tr->t2.x - tr->t1.x) * (tr->t3.z - tr->t1.z) + \
	(tr->t3.x - tr->t1.x) * (tr->t2.z - tr->t1.z);
	tr->xyz.z = (tr->t2.x - tr->t1.x) * (tr->t3.y - tr->t1.y) - \
	(tr->t3.x - tr->t1.x) * (tr->t2.y - tr->t1.y);
	if (vect_len(tr->xyz) != 0)
		tr->xyz = vect_norm(tr->xyz);
	return (0);
}

int			ft_check_obj_norm(t_rt *rt, t_obj *o)
{
	if (o->type != '0' && vect_len(o->xyz) == 0)
		ft_error_exit(-7, rt);
	if (o->type != '0' && (o->xyz.x > 1 || o->xyz.x < -1 || \
	o->xyz.y > 1 || o->xyz.y < -1 || o->xyz.z > 1 || o->xyz.z < -1))
		ft_error_exit(-8, rt);
	if (o->type != '0')
		o->xyz = vect_norm(o->xyz);
	if ((o->type == '0' || o->type == '2' || o->type == '4') && o->r <= 0)
		ft_error_exit(-15, rt);
	if (o->type == '4' && o->h <= 0)
		ft_error_exit(-15, rt);
	return (0);
}
