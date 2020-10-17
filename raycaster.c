/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:13:56 by clauren           #+#    #+#             */
/*   Updated: 2020/10/16 14:39:20 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static t_ray	*find_wall(t_game *g, t_ray *ray)
{
	while (1)
	{
		if (ray->yy < 0 || ray->xx < 0 || (int)ray->yy >= g->res->map_y
			|| (int)ray->xx >= g->res->map_x || is_wall(g, ray->xx, ray->yy))
			break ;
		ray->xx += ray->xo;
		ray->yy += ray->yo;
	}
	ray->len = sqrtf(powf(g->p->x - ray->xx, 2) + powf(g->p->y - ray->yy, 2));
	return (ray);
}

static t_ray	*calc_ray_len_hor(t_game *g, float dir)
{
	t_ray	*ray;

	if (!(ray = malloc(sizeof(t_ray))))
		error("Malloc error", g);
	if ((dir == 0 || dir == 180) && (ray->len = MAXFLOAT))
		return (ray);
	if (dir > 180)
	{
		ray->yy = floorf(g->p->y) - PRECISION;
		ray->xx = g->p->x + (g->p->y - ray->yy) / -tanf(FT_TO_RAD(dir));
		ray->yo = -1;
		ray->xo = ray->yo / tanf(FT_TO_RAD(dir));
		ray->wall = 0;
	}
	if (dir < 180)
	{
		ray->yy = floorf(g->p->y) + 1.0f;
		ray->xx = g->p->x + (g->p->y - ray->yy) / -tanf(FT_TO_RAD(dir));
		ray->yo = 1;
		ray->xo = ray->yo / tanf(FT_TO_RAD(dir));
		ray->wall = 1;
	}
	return (find_wall(g, ray));
}

static t_ray	*calc_ray_len_ver(t_game *g, float dir)
{
	t_ray	*ray;

	if (!(ray = malloc(sizeof(t_ray))))
		error("Malloc error", g);
	if ((dir == 90 || dir == 270) && (ray->len = MAXFLOAT))
		return (ray);
	if (dir > 90 && dir < 270)
	{
		ray->xx = floorf(g->p->x) - PRECISION;
		ray->yy = g->p->y + (g->p->x - ray->xx) * -tanf(FT_TO_RAD(dir));
		ray->xo = -1;
		ray->yo = -tanf(FT_TO_RAD(dir));
		ray->wall = 2;
	}
	if (dir < 90 || dir > 270)
	{
		ray->xx = floorf(g->p->x) + 1.0f;
		ray->yy = g->p->y + (g->p->x - ray->xx) * -tanf(FT_TO_RAD(dir));
		ray->xo = 1;
		ray->yo = tanf(FT_TO_RAD(dir));
		ray->wall = 3;
	}
	return (find_wall(g, ray));
}

static t_ray	*calc_ray(t_game *g, float *dir)
{
	t_ray *ray1;
	t_ray *ray2;

	if (*dir >= 360)
		*dir -= 360;
	if (*dir < 0)
		*dir += 360;
	ray1 = calc_ray_len_ver(g, *dir);
	ray2 = calc_ray_len_hor(g, *dir);
	if (ray1->len > 0 && ray1->len < ray2->len)
	{
		free(ray2);
		return (ray1);
	}
	else
	{
		free(ray1);
		return (ray2);
	}
}

void			draw_lines(t_game *g)
{
	float	dir;
	float	zbuff[g->res->x];
	int		i;
	t_ray	*ray;
	t_line	line;

	dir = g->p->a - FOV / 2;
	i = 0;
	while (i < g->res->x)
	{
		ray = calc_ray(g, &dir);
		line.len = g->res->y / (ray->len * cosf(FT_TO_RAD((dir - g->p->a))));
		line.start = 0.5f * (-line.len + g->res->y);
		line.start = (line.start < 0) ? 0 : line.start;
		line.end = 0.5f * (line.len + g->res->y);
		line.end = (line.end >= g->res->y) ? g->res->y - 1 : line.end;
		find_text_x(g, ray);
		draw_floorsky(g, &line, i);
		draw_texture(g, ray, &line, i);
		zbuff[i++] = ray->len;
		dir += FOV / (float)(g->res->x);
	}
	draw_sprites(g, zbuff);
	draw_square(g, g->res->map_s / 2, g->p->x * g->res->map_s,
				g->p->y * g->res->map_s);
}
