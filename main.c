/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:41:16 by clauren           #+#    #+#             */
/*   Updated: 2020/10/16 18:11:38 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static	void	move_player(t_game *g, float dx, float dy)
{
	if (!is_wall(g, g->p->x + dx, g->p->y))
		g->p->x += dx;
	if (!is_wall(g, g->p->x, g->p->y + dy))
		g->p->y += dy;
}

int				key_handler(int code, t_game *g)
{
	float dx;
	float dy;

	if (code == KEY_ESC)
		quit_game(g);
	if (code == KEY_W || code == KEY_S)
	{
		dx = (code == KEY_W ? MOVE_SPEED * 1.0f : MOVE_SPEED * -1.0f)
				* cosf(FT_TO_RAD(g->p->a));
		dy = (code == KEY_W ? MOVE_SPEED * 1.0f : MOVE_SPEED * -1.0f)
				* sinf(FT_TO_RAD(g->p->a));
	}
	if (code == KEY_A || code == KEY_D)
	{
		dx = (code == KEY_A ? MOVE_SPEED * 1.0f : MOVE_SPEED * -1.0f)
				* cosf(FT_TO_RAD((g->p->a - 90)));
		dy = (code == KEY_A ? MOVE_SPEED * 1.0f : MOVE_SPEED * -1.0f)
				* sinf(FT_TO_RAD((g->p->a - 90)));
	}
	if (code == KEY_LEFT || code == KEY_RIGHT)
		change_deg(g, (code == KEY_LEFT ? -1 : 1) * ROTATE_SPEED);
	move_player(g, dx, dy);
	draw_lines(g);
	draw_coord(g, draw_map(g));
	return (1);
}

static	void	*init(t_game **g, char **path)
{
	int i;

	i = 0;
	while (i < 5)
		path[i++] = NULL;
	if (!((*g = malloc(sizeof(t_game)))))
		error("Malloc error", NULL);
	(*g)->win = NULL;
	if (!((*g)->p = malloc(sizeof(t_player))))
		error("Malloc error", NULL);
	if (!((*g)->image = malloc(sizeof(t_img))))
		error("Malloc error", NULL);
	if (!((*g)->res = malloc(sizeof(t_res))))
		error("Malloc error", NULL);
	if (!((*g)->mlx = mlx_init()))
		error("Malloc error", NULL);
	return (NULL);
}

static	void	start_game(t_game *g, char **map, int screenshot)
{
	g->map = map;
	get_map_size(g);
	check_map(map, g);
	find_sprites(map, g);
	g->win = mlx_new_window(g->mlx, g->res->x, g->res->y, PROGRAM_NAME);
	g->image->img = mlx_new_image(g->mlx, g->res->x, g->res->y);
	g->image->addr = mlx_get_data_addr(g->image->img, &g->image->bits_per_pixel,
									&g->image->line_length, &g->image->endian);
	if (!screenshot)
	{
		key_handler(0, g);
		mlx_hook(g->win, 2, 1L << 0, key_handler, g);
		mlx_hook(g->win, 17, 0, &quit_game, g);
		mlx_loop(g->mlx);
	}
	else
	{
		draw_lines(g);
		draw_map(g);
		mlx_put_image_to_window(g->mlx, g->win, g->image->img, 0, 0);
		save_screenshot(g);
	}
}

int				main(int argc, char **argv)
{
	int		fd;
	t_list	*map;
	t_game	*g;
	char	*path[5];
	int		screenshot;

	if (argc == 1 || argc > 3)
		error("Wrong number of argc", NULL);
	if (((fd = open(argv[1], O_RDONLY)) == -1) ||
			((ft_strncmp(".cub", argv[1] + (ft_strlen(argv[1]) - 4), 4))
			|| ft_strnstr(argv[1], "/.cub", ft_strlen(argv[1])) != NULL))
		error("Wrong .cub file", NULL);
	if (argc == 3 || (screenshot = 0))
	{
		if (!ft_strncmp("--save", argv[2], ft_strlen(argv[2])))
			screenshot = 1;
		else
			error("Wrong second argument", NULL);
	}
	map = init(&g, path);
	parse_lines(g, fd, (char **)&path, &map);
	load_texture(path, g);
	start_game(g, make_map(&map, ft_lstsize(map)), screenshot);
	return (0);
}
