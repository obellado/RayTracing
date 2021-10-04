/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:19:33 by obellado          #+#    #+#             */
/*   Updated: 2021/03/16 22:07:42 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect		vect_sum(t_vect v1, t_vect v2)
{
	t_vect		v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vect		vect_inverse(t_vect v)
{
	t_vect	d;

	d.x = -v.x;
	d.y = -v.y;
	d.z = -v.z;
	return (d);
}

float		vect_cos(t_vect v1, t_vect v2)
{
	float		cos;

	cos = vect_skal(v1, v2) / (vect_len(v1) * vect_len(v2));
	return (cos);
}

t_vect		vect_sub(t_vect v1, t_vect v2)
{
	t_vect		v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vect		vect_mult(t_vect v1, float n)
{
	t_vect		v;

	v.x = v1.x * n;
	v.y = v1.y * n;
	v.z = v1.z * n;
	return (v);
}
