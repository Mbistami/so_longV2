/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 19:37:52 by mbistami          #+#    #+#             */
/*   Updated: 2022/03/08 23:26:17 by mbistami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H
#include "./mlx/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include "./get_next_line/get_next_line.h"

typedef struct s_point
{
	int x;
	int y;
} t_point;

typedef struct s_vars
{
	void *mlx;
	void *win;
} t_vars;

typedef struct s_assets_world
{
	void *ground;
	void *walls;
	void *inner_walls;
	void *water;
} t_assets_world;

typedef struct s_assets_items
{
	void **coin;
	void **portal;
	void **trap;
	void *enemy;
} t_assets_items;

typedef struct s_assets
{
	void *player;
	t_assets_world world;
	t_assets_items items;
} t_assets;

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

typedef struct s_game_info
{
	int exit_count;
	int collectible_count;
	int starting_pos_count;
	int error;
	int min_line_len;
	int lines_count;
	int square_size;
	int window_width;
	int draw_coins;
} t_game_info;

typedef struct s_game_data
{
	char *map;
	int player;
	int player_heading;
	int in_game;
	int player_won;
	int made_moves;
	t_vars vars;
	t_assets assets;
	t_game_info info;
	t_coin_data coin_data;
	t_portal_data portal_data;
} t_game_data;

typedef struct s_animated_coin
{
	int frames;
	int count;
	t_game_data data;
} t_animated_coin;

t_point new_point(int x, int y);
void draw_map(t_game_data *data);
void make_moves(t_game_data *data, int keycode);
void draw_winner_screen(t_game_data *data, int won);
void load_assets(t_game_data *data);
void set_heading(t_game_data *data, char type);
void draw_game(t_game_data *data);
void up_down_moves(t_game_data *data, int keycode);
void player_won(t_game_data *data);
void player_lost(t_game_data *data);
int parse_map(t_game_data *data, int fd);
int handle_auto_draw(t_game_data *data);
int validate_move(t_game_data *data, int keycode);
int handle_errors(t_game_data *data, int argv, char **argc);
int handle_click(int keycode, t_game_data *data);
int handle_exit(t_game_data *data, int is_error);
int get_heading(int keycode);
int is_valid_file(char *filename);
char *ft_itoa(int n);
char *ft_strjoin(const char *s1, const char *s2);
int is_valid_character(char c);
#endif