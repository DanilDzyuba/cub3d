/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:28:20 by clauren           #+#    #+#             */
/*   Updated: 2020/10/13 14:41:07 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void			draw_square(t_game *g, int size, int x, int y)
{
	int i;
	int k;
	int s;
	int color;

	if (size == g->res->map_s)
		color = 0x000000FF;
	else if (size == g->res->map_s / 2)
		color = 0x00FF0000;
	else if (size == g->res->map_s / 4)
		color = 0x00FFFF00;
	s = size;
	i = -1;
	while (++i < size && (k = -1))
		while (++k < size)
			my_pixel_put(g->image, k + x, i + y, color);
}

int				draw_map(t_game *g)
{
	int i;
	int k;

	i = -1;
	while (g->map[++i] && (k = -1))
	{
		while (g->map[i][++k])
		{
			if (g->map[i][k] == '1')
				draw_square(g, g->res->map_s, k * g->res->map_s,
				i * g->res->map_s);
			if (g->map[i][k] == '2')
				draw_square(g, g->res->map_s / 4, k * g->res->map_s,
				i * g->res->map_s);
		}
	}
	return (i * g->res->map_s);
}

static	char	*gen_xya(int p, char *x, char *y, char *a)
{
	char buffer[31];
	char *s1;
	char *s2;
	char *s3;

	s1 = "(x: ";
	s2 = " y: ";
	s3 = " a: ";
	while (*s1)
		buffer[p++] = *s1++;
	while (*x)
		buffer[p++] = *x++;
	while (*s2)
		buffer[p++] = *s2++;
	while (*y)
		buffer[p++] = *y++;
	while (*s3)
		buffer[p++] = *s3++;
	while (*a)
		buffer[p++] = *a++;
	buffer[p++] = ')';
	buffer[p++] = '\0';
	return (ft_strdup(buffer));
}

void			draw_coord(t_game *g, int mini)
{
	char *x;
	char *y;
	char *a;
	char *c;

	mlx_put_image_to_window(g->mlx, g->win, g->image->img, 0, 0);
	x = ft_itoa(g->p->x);
	y = ft_itoa(g->p->y);
	a = ft_itoa(g->p->a);
	c = gen_xya(0, x, y, a);
	mlx_string_put(g->mlx, g->win, 1, mini + 10, 0x00FF0000, c);
	free(x);
	free(y);
	free(a);
	free(c);
}

void			my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
