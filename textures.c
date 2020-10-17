/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 00:50:23 by clauren           #+#    #+#             */
/*   Updated: 2020/10/16 14:27:40 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	find_text_x(t_game *g, t_ray *ray)
{
	float x;

	if (ray->wall == 0)
		x = ray->xx - floorf(ray->xx);
	else if (ray->wall == 1)
		x = 1 - (ray->xx - floorf(ray->xx));
	else if (ray->wall == 3)
		x = ray->yy - floorf(ray->yy);
	else
		x = 1 - (ray->yy - floorf(ray->yy));
	g->texts[ray->wall]->x = floorf(x * g->texts[ray->wall]->width);
}

void	draw_texture(t_game *g, t_ray *ray, t_line *line, int x)
{
	float	y_offset;
	float	pos;
	int		ty;
	int		color;

	y_offset = g->texts[ray->wall]->height / line->len;
	pos = (line->start - g->res->y / 2 + line->len / 2) * y_offset;
	while (line->start < line->end)
	{
		ty = (int)pos & (g->texts[ray->wall]->height - 1);
		pos += y_offset;
		color = get_texture_color(g->texts[ray->wall],
				g->texts[ray->wall]->x, ty);
		my_pixel_put(g->image, x, line->start, color);
		line->start++;
	}
	free(ray);
}

void	draw_floorsky(t_game *g, t_line *line, int i)
{
	int j;

	j = -1;
	while (++j < line->start)
		my_pixel_put(g->image, i, j, g->c);
	j = line->end - 1;
	while (++j < g->res->y)
		my_pixel_put(g->image, i, j, g->f);
}

void	load_texture(char **path, t_game *g)
{
	int i;

	i = 0;
	if (!(g->texts = (t_texture **)malloc(sizeof(t_texture *) * 5)))
		error("Malloc error", g);
	while (i < 5)
	{
		if (!(g->texts[i] = (t_texture*)malloc(sizeof(t_texture))))
			error("Malloc error", g);
		g->texts[i]->img = NULL;
		i++;
	}
	i = 0;
	while (i < 5)
	{
		g->texts[i]->img = mlx_xpm_file_to_image(g->mlx,
				path[i], &(g->texts[i]->width), &(g->texts[i]->height));
		if (NULL == g->texts[i]->img)
			error("Failed to load textures", g);
		g->texts[i]->addr = mlx_get_data_addr(g->texts[i]->img,
				&(g->texts[i]->bits_per_pixel), &(g->texts[i]->line_length),
				&(g->texts[i]->endian));
		i++;
	}
}

int		get_texture_color(t_texture *text, int x, int y)
{
	char	*dst;

	dst = text->addr + (y * text->line_length + x * (text->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}
