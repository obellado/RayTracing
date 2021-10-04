/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 19:42:29 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 23:09:38 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float		parce_float(char *line, t_rt *rt)
{
	float		x;
	float		n;
	int			flag;

	n = 0.1;
	x = 0;
	flag = 1;
	if (*line == '-')
	{
		flag = -1;
		line++;
	}
	if (!(ft_isdigit(*line)))
		rt->error = -1;
	while (ft_isdigit(*line))
		x = x * 10 + *line++ - 48;
	if (*line == '.')
		line++;
	while (ft_isdigit(*line))
	{
		x = x + (*line++ - 48) * n;
		n = n * 0.1;
	}
	return (x * flag);
}

t_color		parce_color(char *line, t_rt *rt)
{
	t_color		v;

	ft_bzero(&v, sizeof(t_color));
	while (*line == ' ')
		line++;
	if (!(ft_isdigit(*line)))
		rt->error = -6;
	while (ft_isdigit(*line))
		v.r = v.r * 10 + *line++ - 48;
	if (*line == ',')
		line++;
	if (!(ft_isdigit(*line)))
		rt->error = -6;
	while (ft_isdigit(*line))
		v.g = v.g * 10 + *line++ - 48;
	if (*line == ',')
		line++;
	if (!(ft_isdigit(*line)))
		rt->error = -6;
	while (ft_isdigit(*line))
		v.b = v.b * 10 + *line++ - 48;
	if ((*line != ' ' && *line != '\0') || v.r > 255 || v.g > 255 || v.b > 255)
		rt->error = -6;
	v = color_norm(v);
	return (v);
}

t_vect		parce_vect(char *line, t_rt *rt)
{
	t_vect		v;

	ft_bzero(&v, sizeof(t_vect));
	v.x = parce_float(line, rt);
	while (ft_isdigit(*line) || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == ',')
		line++;
	v.y = parce_float(line, rt);
	while (ft_isdigit(*line) || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == ',')
		line++;
	v.z = parce_float(line, rt);
	return (v);
}

int			parser_sp(t_rt *rt, char *line)
{
	t_obj		*sp;

	if (!(sp = (t_obj*)malloc(sizeof(t_obj))))
		return (ft_error_exit(-2, rt));
	ft_bzero(sp, sizeof(t_obj));
	sp->type = '0';
	while (*line == ' ' || *line == '\t')
		line++;
	sp->xyz = parce_vect(line, rt);
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->r = parce_float(line, rt) / 2;
	parser_sp_2(rt, line, sp);
	ft_check_obj_norm(rt, sp);
	ft_listadd_back(&rt->o1, ft_listnew(sp));
	rt->no += 1;
	sp->n = rt->no;
	return (0);
}

int			parser_sp_2(t_rt *rt, char *line, t_obj *sp)
{
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->color = parce_color(line, rt);
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->refl = parce_float(line, rt);
	return (0);
}
