/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 19:37:52 by mbistami          #+#    #+#             */
/*   Updated: 2022/02/24 03:56:11 by mbistami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <fcntl.h>
#include "./get_next_line/get_next_line.h"

typedef struct  s_point {
    int	x;
    int	y;
}   	t_point;

typedef struct	s_vars
{
    void    	*mlx;
    void    	*win;
}   			t_vars;

typedef struct 	s_assets_world
{
	void		*ground;
	void		*walls;
	void		*inner_walls;
	void		*water;
}				t_assets_world;

typedef struct 	s_assets_items
{
	void		**coin;
	void		**portal;
	void		*enemy;
}				t_assets_items;

typedef struct 		s_assets
{
	t_assets_world	world;
	t_assets_items	items;
	void			*player;
} 					t_assets;

typedef struct s_coin_data
{
	int count;
	int frames;
} t_coin_data;

typedef struct s_portal_data
{
	int count;
	int frames;
	int is_open;
} t_portal_data;


typedef struct	s_game_info
{
	int     	exit_count;
    int     	collectible_count;
    int     	starting_pos_count;
    int     	error;
    int     	min_line_len;
    int     	lines_count;
    int     	square_size;
	int     	window_width;
	int			draw_coins;
} 				t_game_info;


typedef struct	s_game_data
{
	int			player;
    int     	player_heading;
    char    	*map;
	int			in_game;
	t_vars 		vars;
	t_assets	assets;
	t_game_info	info;
	t_coin_data coin_data;
	t_portal_data portal_data;
}				t_game_data;

typedef struct	s_animated_coin
{
	int			frames;
	int			count;
	t_game_data data;
} 				t_animated_coin;




int		parse_map(t_game_data *data, int fd);
void 	draw_map (t_game_data *data, int ignore_collectibles);
void	make_moves(t_game_data *data, int keycode);
int		draw_animated_coin (t_game_data *data);