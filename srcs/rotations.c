/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 19:23:42 by obellado          #+#    #+#             */
/*   Updated: 2021/03/20 23:03:45 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			parser_rotate(t_rt *rt, char *name)
{
	int		fd;
	char	*line;
	int		n;

	n = 0;
	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (ft_error_exit(-4, rt));
	while (get_next_line(fd, &line) && rt->error == 0)
	{
		parser_roto(rt, line);
		n++;
		free(line);
	}
	parser_roto(rt, line);
	n++;
	free(line);
	close(fd);
	ft_scene_new(rt);
	return (0);
}

int			parser_roto(t_rt *rt, char *l)
{
	float		n;

	if (l[0] == 'r' && l[1] == 'o')
	{
		l++;
		l++;
		while (*l == ' ' || *l == '\t')
			l++;
		n = parce_float(l, rt);
		while (ft_isdigit(*l) || *l == ',' || *l == '.' || *l == '-')
			l++;
		while (*l == ' ' || *l == '\t')
			l++;
		rt->rot = parce_vect(l, rt);
		if (rt->error != 0 || n <= 0 || n > rt->no)
		{
			write(1, "Error\nMistake in *.rt: can't rotate the object\n", 46);
			rt->error = 0;
			return (0);
		}
		ft_rotate_o(rt, n);
	}
	if (l[0] == 'r' && l[1] == 'c')
		ft_rotate_c(rt, l);
	return (0);
}

int			ft_rotate_o(t_rt *rt, int n)
{
	t_list		*tmp;

	tmp = rt->o1;
	while (n != rt->o1->o->n && rt->o1->next)
		rt->o1 = rt->o1->next;
	if (rt->o1->o->type == '0' || rt->o1->o->type == '3' || \
	rt->o1->o->type > '4')
	{
		rt->o1 = tmp;
		write(1, "Error\nObject cannot be rotated\n", 31);
		return (0);
	}
	if (rt->rot.x != 0 && rt->rot.y == 0 && rt->rot.z == 0)
		rt->o1->o->xyz = rotate_x(rt->o1->o->xyz, rt->rot.x);
	else if (rt->rot.z != 0 && rt->rot.x == 0 && rt->rot.y == 0)
		rt->o1->o->xyz = rotate_z(rt->o1->o->xyz, rt->rot.z);
	else if (rt->rot.y != 0 && rt->rot.x == 0 && rt->rot.z == 0)
		rt->o1->o->xyz = rotate_y(rt->o1->o->xyz, rt->rot.y);
	else
		write(1, "Error\nRotate around the one axis per apply\n", 43);
	rt->o1->o->xyz = vect_norm(rt->o1->o->xyz);
	rt->o1 = tmp;
	return (0);
}

int			ft_rotate_c(t_rt *rt, char *line)
{
	line++;
	line++;
	while (*line == ' ' || *line == '\t')
		line++;
	rt->rot = parce_vect(line, rt);
	if (rt->error != 0)
	{
		write(1, "Error\nMistake in *.rt: can't rotate the camera\n", 47);
		rt->error = 0;
		return (0);
	}
	if (rt->rot.x != 0 && rt->rot.y == 0 && rt->rot.z == 0)
		rt->c1->c->nor = rotate_x(rt->c1->c->nor, rt->rot.x);
	else if (rt->rot.z != 0 && rt->rot.x == 0 && rt->rot.y == 0)
		rt->c1->c->nor = rotate_z(rt->c1->c->nor, rt->rot.z);
	else if (rt->rot.y != 0 && rt->rot.x == 0 && rt->rot.z == 0)
		rt->c1->c->nor = rotate_y(rt->c1->c->nor, rt->rot.y);
	else
		write(1, "Error\nRotate around the one axis per apply\n", 42);
	rt->c1->c->nor = vect_norm(rt->c1->c->nor);
	return (0);
}
