/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:34:40 by ababouel          #+#    #+#             */
/*   Updated: 2022/10/11 06:19:41 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "parsing.h"
#include "draw.h" 
#include "events.h"
#include "tools.h"
#include "raycast.h"
#include<unistd.h>
#include <fcntl.h>
#include <sys/errno.h>

int	ft_init_vars(t_vars *vars)
{
	vars->ordr.dir1 = addvect(1, 1, add_color(255,0,0), 10);
	vars->ordr.minplane = addvect(cos(M_PI/6.0), sin(M_PI/6.0), add_color(255,0,0), 20);
	vars->ordr.maxplane = addvect(cos((M_PI/3.0)), sin((M_PI/3.0)), add_color(255,0,0), 20);	
	vars->ordr.dir1->angle = M_PI/50;
	vars->ordr.maxplane->angle = M_PI/50;
	vars->ordr.minplane->angle = M_PI/50;	
	vars->rect.color = add_color(0,0,255);
	vars->rect.x = 5;
	vars->rect.y = 5;
	int x;
	x = 0;
	while (x < 4)
	{
		generate_image(vars, vars->data->txtpath[x].path,vars->data->txtpath[x].nswe);
		x++;
	}
	return(0);
}

int    ft_init(t_vars *vars)
{
    vars->mlx = mlx_init();
	if (!vars->mlx)
		return (MLX_ERROR);
	vars->win = mlx_new_window(vars->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "vars");
	if (!vars->win)
	{
		free(vars);
		return (MLX_ERROR);
	}
	vars->iarg->img= mlx_new_image(vars->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	vars->iarg->addr = mlx_get_data_addr(vars->iarg->img,
			&vars->iarg->bpp, &vars->iarg->line_len, &vars->iarg->endian);
	return (0);
}

int render_next_frame(void *vars)
{
	t_vars	*v;
	
	v = (t_vars *)vars;
	climg(v->iarg->img);
	draw_ceil_floor(vars);
	draw_map(v);
	camera(v);
	mlx_put_image_to_window( v->mlx, v->win, v->iarg->img, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	int		check;
	if (argc == 2)
	{
		vars = allocate();
		check = ft_parse(argv[1], vars);
		if (check < 0)
		{
			//free all
			printf("Error.\n");
			return (1);
		}
		else
			printf("Valid map.\n");
		ft_init(vars);
		ft_init_vars(vars);
		mlx_loop_hook(vars->mlx, render_next_frame, (void *)vars);	
		mlx_key_hook(vars->win, esc_key, vars);
		mlx_hook(vars->win, 17, 0, close_game, vars);
		mlx_do_sync(vars->mlx);
		mlx_loop(vars->mlx);
	}
	else
		printf("Usage ./cub3d map_name \n");
	return (0);
}	
