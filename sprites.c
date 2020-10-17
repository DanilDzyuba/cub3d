/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 23:14:35 by clauren           #+#    #+#             */
/*   Updated: 2020/10/12 20:08:54 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void			find_sprites(char **map, t_game *g)
{
	int x;
	int y;
	int i;

	if (!(g->sprites = malloc(sizeof(t_sprite) * g->sp_num)))
		error("Sprites memory allocation failed", g);
	y = -1;
	i = 0;
	while (map[++y] && (x = -1))
	{
		if (!ft_strpos(map[y], '2'))
			continue ;
		while (map[y][++x])
		{
			if (map[y][x] == '2')
			{
				g->sprites[i].x = x;
				g->sprites[i].y = y;
				i++;
			}
		}
	}
}

static	void	sort_sprites(t_sprite *sprite, int count)
{
	t_sprite	temp;
	int			i;

	i = 0;
	while (++i < count)
	{
		if (sprite[i].dist > sprite[i - 1].dist)
		{
			temp = sprite[i];
			sprite[i] = sprite[i - 1];
			sprite[i - 1] = temp;
			i = 1;
		}
	}
}

static	void	get_sprite_preferences(t_game *g, t_sprite *s)
{
	float			da;
	float			dx;
	float			dy;

	dx = s->x - g->p->x * 1.0f + 0.5f;
	dy = s->y - g->p->y * 1.0f + 0.5f;
	da = FT_TO_DEG(atan2f(dy, dx)) - g->p->a;
	if ((dx >= 0 && 180 <= g->p->a && g->p->a <= 360)
		|| (dx < 0 && dy < 0))
		da += 360;
	s->d_rays = da / (FOV * 1.0f / g->res->x);
	s->size = g->res->y / s->dist;
	s->v_off = (g->res->y - s->size) / 2;
	s->h_off = (g->res->x - s->size) / 2 + s->d_rays;
}

static	void	draw_sprite_line(t_game *g, t_sprite *s, int i)
{
	int j;
	int	color;

	j = -1;
	while (++j < s->size)
		if (j + s->v_off >= 0 && j + s->v_off < g->res->y)
		{
			color = get_texture_color(g->texts[4],
				(g->texts[4]->width * 1.0f / s->size) * i,
				(g->texts[4]->height * 1.0f / s->size) * j);
			if (color)
				my_pixel_put(g->image, i + s->h_off, j + s->v_off, color);
		}
}

void			draw_sprites(t_game *g, float *zbuff)
{
	int i;
	int j;

	i = -1;
	while (++i < g->sp_num)
		g->sprites[i].dist = sqrtf(powf(g->p->x - g->sprites[i].x - 0.25f, 2)
					+ powf(g->p->y - g->sprites[i].y - 0.25f, 2));
	i = -1;
	sort_sprites(g->sprites, g->sp_num);
	while (++i < g->sp_num && (j = -1))
	{
		get_sprite_preferences(g, &(g->sprites[i]));
		while (++j < g->sprites[i].size)
		{
			if (j + g->sprites[i].h_off >= 0
			&& j + g->sprites[i].h_off < g->res->x
			&& zbuff[j + g->sprites[i].h_off] > g->sprites[i].dist)
			{
				draw_sprite_line(g, &g->sprites[i], j);
			}
		}
	}
}
