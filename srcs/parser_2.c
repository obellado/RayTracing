/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:32:40 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 16:55:33 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			parser_light(t_rt *rt, char *line)
{
	t_light		*sp;

	if (!(sp = (t_light*)malloc(sizeof(t_light))))
		return (ft_error_exit(-2, rt));
	ft_bzero(sp, sizeof(t_light));
	while (*line == ' ' || *line == '\t')
		line++;
	sp->xyz = parce_vect(line, rt);
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->li = parce_float(line, rt);
	while (ft_isdigit(*line) || *line == '.')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->color = parce_color(line, rt);
	ft_llistadd_back(&rt->l, ft_llistnew(sp));
	rt->nl += 1;
	sp->n = rt->nl;
	return (0);
}

int			parser_tr(t_rt *rt, char *line)
{
	t_obj		*sp;

	if (!(sp = (t_obj*)malloc(sizeof(t_obj))))
		return (ft_error_exit(-2, rt));
	ft_bzero(sp, sizeof(t_obj));
	while (*line == ' ' || *line == '\t')
		line++;
	sp->type = '3';
	sp->t1 = parce_vect(line, rt);
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->t2 = parce_vect(line, rt);
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	parser_tr_2(rt, line, sp);
	ft_check_tr(sp);
	ft_check_obj_norm(rt, sp);
	ft_listadd_back(&rt->o1, ft_listnew(sp));
	rt->no += 1;
	sp->n = rt->no;
	return (0);
}

int			parser_tr_2(t_rt *rt, char *line, t_obj *sp)
{
	sp->t3 = parce_vect(line, rt);
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

int			parser_cy(t_rt *rt, char *line)
{
	t_obj		*sp;

	if (!(sp = (t_obj*)malloc(sizeof(t_obj))))
		return (ft_error_exit(-2, rt));
	ft_bzero(sp, sizeof(t_obj));
	while (*line == ' ' || *line == '\t')
		line++;
	sp->type = '4';
	while (*line == ' ' || *line == '\t')
		line++;
	sp->xyz1 = parce_vect(line, rt);
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->xyz = parce_vect(line, rt);
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	parser_cy_2(rt, line, sp);
	ft_check_obj_norm(rt, sp);
	ft_listadd_back(&rt->o1, ft_listnew(sp));
	rt->no += 1;
	sp->n = rt->no;
	return (0);
}

int			parser_cy_2(t_rt *rt, char *line, t_obj *sp)
{
	while (*line == ' ' || *line == '\t')
		line++;
	sp->r = parce_float(line, rt) / 2;
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->h = parce_float(line, rt);
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
