/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obellado <obellado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:34:19 by obellado          #+#    #+#             */
/*   Updated: 2021/03/22 23:09:00 by obellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int			parser_pl(t_rt *rt, char *line)
{
	t_obj		*sp;

	if (!(sp = (t_obj*)malloc(sizeof(t_obj))))
		return (ft_error_exit(-2, rt));
	ft_bzero(sp, sizeof(t_obj));
	while (*line == ' ' || *line == '\t')
		line++;
	sp->type = '1';
	while (*line == ' ' || *line == '\t')
		line++;
	sp->xyz1 = parce_vect(line, rt);
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->xyz = parce_vect(line, rt);
	parser_pl_2(rt, line, sp);
	ft_check_obj_norm(rt, sp);
	ft_listadd_back(&rt->o1, ft_listnew(sp));
	rt->no += 1;
	sp->n = rt->no;
	return (0);
}

int			parser_pl_2(t_rt *rt, char *line, t_obj *sp)
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

int			parser_sq(t_rt *rt, char *line)
{
	t_obj		*sp;

	if (!(sp = (t_obj*)malloc(sizeof(t_obj))))
		return (ft_error_exit(-2, rt));
	ft_bzero(sp, sizeof(t_obj));
	while (*line == ' ' || *line == '\t')
		line++;
	sp->type = '2';
	while (*line == ' ' || *line == '\t')
		line++;
	sp->xyz1 = parce_vect(line, rt);
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->xyz = parce_vect(line, rt);
	parser_sq_2(rt, line, sp);
	ft_check_obj_norm(rt, sp);
	ft_check_sq(sp);
	ft_listadd_back(&rt->o1, ft_listnew(sp));
	rt->no += 1;
	sp->n = rt->no;
	return (0);
}

int			parser_sq_2(t_rt *rt, char *line, t_obj *sp)
{
	while (ft_isdigit(*line) || *line == ',' || *line == '.' || *line == '-')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	sp->r = parce_float(line, rt) / 2;
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
