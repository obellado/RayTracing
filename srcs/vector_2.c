/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:49:59 by obellado          #+#    #+#             */
/*   Updated: 2021/03/20 19:16:30 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		vect_len(t_vect v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

t_vect		vect_norm(t_vect v)
{
	t_vect		n;
	double		len;

	len = vect_len(v);
	n.x = v.x / len;
	n.y = v.y / len;
	n.z = v.z / len;
	return (n);
}

t_vect		vect_cross(t_vect v1, t_vect v2)
{
	t_vect		v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

double		vect_skal(t_vect v, t_vect w)
{
	double		t;

	t = (v.x * w.x) + (v.y * w.y) + (v.z * w.z);
	return (t);
}
