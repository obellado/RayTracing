/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:43:28 by obellado          #+#    #+#             */
/*   Updated: 2021/03/10 22:43:50 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect		rotate_x(t_vect norm, float ax)
{
	t_vect		new;

	new.z = norm.y * sin(ax * 0.0174533) + norm.z * cos(ax * 0.0174533);
	new.y = norm.y * cos(ax * 0.0174533) - norm.z * sin(ax * 0.0174533);
	new.x = norm.x;
	return (new);
}

t_vect		rotate_y(t_vect norm, float ax)
{
	t_vect		new;

	new.x = norm.x * cos(ax * 0.0174533) + norm.z * sin(ax * 0.0174533);
	new.z = -norm.x * sin(ax * 0.0174533) + norm.z * cos(ax * 0.0174533);
	new.y = norm.y;
	return (new);
}

t_vect		rotate_z(t_vect norm, float ax)
{
	t_vect		new;

	new.x = norm.x * cos(ax * 0.0174533) - norm.y * sin(ax * 0.0174533);
	new.y = norm.x * sin(ax * 0.0174533) + norm.y * cos(ax * 0.0174533);
	new.z = norm.z;
	return (new);
}
