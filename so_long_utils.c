/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:46:53 by mbistami          #+#    #+#             */
/*   Updated: 2022/02/14 04:29:25 by mbistami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point new_point(int x, int y)
{
    t_point point;

    point.x = x;
    point.y = y;
    return (point);
}

// t_animated_coin *new_coin (t_game_data *data)
// {
// 	data->coin_data.count = 0;
//     data->coin_data.frames = 0;

// 	coin = (t_animated_coin *)malloc(sizeof(t_animated_coin));
// 	coin->frames = 0;
// 	coin->count = 0;
//     coin->data = *data;
// 	return (coin);
// }

void handle_coin (t_game_data *data, char type, t_point point)
{
    int		img_f;
    
    if (type == 'C')
    {
        // mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.world.ground, point.x, point.y);
        if (data->coin_data.count == data->coin_data.frames * 500)
        {
            if (data->coin_data.frames > data->info.collectible_count)
                data->info.collectible_count = 0;
                
            // printf("%d****\n", data->coin_data.frames);
            if (data->coin_data.frames == data->info.collectible_count)
                data->coin_data.frames = 0;
            mlx_clear_window(data->vars.mlx, data->vars.win);
            mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.items.coin[data->coin_data.frames], point.x, point.y);
            draw_map(data, 1);
        }
    }
}

int	draw_animated_coin (t_game_data *data)
{
	
	int x = 0;
    int y = 0;
    int i = 0;
    //printf("$$$$$$$$%s\n", data->map);
    if (data->in_game)
    {
        if (data->coin_data.count == data->coin_data.frames * 800)
        {
            mlx_clear_window(data->vars.mlx, data->vars.win);
            draw_map(data, 1);
        }
        if (data->coin_data.count == data->coin_data.frames * 800)
            data->coin_data.frames++;
        if (data->coin_data.count++ >= 4800)
            data->coin_data.count = 0;
        if (data->coin_data.frames >= 6)
            data->coin_data.frames = 0;
    }
	return (0);
}

void set_heading(t_game_data *data, char type, t_point point)
{
    int img_h;
    
    if (type == 'P')
    {
        if (data->player_heading == 1)
            data->assets.player = mlx_xpm_file_to_image(data->vars.mlx, "/Users/mbistami/so_long/CharacterHeadingUp.xpm", &img_h, &img_h);
        else if (data->player_heading == 3)
            data->assets.player = mlx_xpm_file_to_image(data->vars.mlx, "/Users/mbistami/so_long/CharacterHeadingRight.xpm", &img_h, &img_h);
        else if (data->player_heading == 4)
            data->assets.player = mlx_xpm_file_to_image(data->vars.mlx, "/Users/mbistami/so_long/CharacterHeadingLeft.xpm", &img_h, &img_h);
        else
            data->assets.player = mlx_xpm_file_to_image(data->vars.mlx, "/Users/mbistami/so_long/Character.xpm", &img_h, &img_h);
        mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.player, point.x, point.y);
    }
}

void draw_asset (t_point point, t_game_data *data, int i)
{
    char    *map;
    int     img_h;
    int     img_w;

    map = data->map;
    if (map[i] == '1' && map[i] != 10)
    {
        if (((i + 1) % (data->info.min_line_len + 1) == 1 || (i + 1) % (data->info.min_line_len + 1) == data->info.min_line_len)
            || (i < data->info.min_line_len) || i + data->info.min_line_len > ft_strlen(data->map))
            mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.world.walls, point.x, point.y);
        else
            mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.world.water, point.x, point.y);
    }
    else
    {
        mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.world.ground, point.x, point.y);
        if (map[i] == 'C')
        {
            mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.items.coin[data->coin_data.frames], point.x, point.y);
            data->info.draw_coins = 1;
        }
        else if (map[i] == 'E' && data->info.collectible_count)
            mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.world.walls, point.x, point.y);
        else if (map[i] == 'E' && !data->info.collectible_count)
            mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.items.coin[data->coin_data.frames], point.x, point.y);
        printf("%d\n", data->info.collectible_count);
        set_heading(data, map[i], point);
    }
}

void draw_map (t_game_data *data, int ignore_collectibles)
{
    int x = 0;
    int y = 0;
    int i = 0;
    int line;
    int img_h;
    int square_size;
    void *imge;
	char *map;

    t_point point; 
    square_size = data->info.square_size;
	map = data->map;
        
    while(map[i])
    {
        draw_asset(new_point(x, y), data, i);
        if (map[i] != 10)
            x += square_size;
        else 
        {
            x = 0;
            y += square_size;
        }
        i++;
    }
}

void up_down_moves(t_game_data *data, int keycode)
{
   
    {
        if (keycode == 126 && data->map[data->player - (data->info.min_line_len + 1)] != '1')
        {
            data->map[data->player] = '0';
            data->map[data->player - (data->info.min_line_len + 1)] = 'P';
            data->player = data->player - (data->info.min_line_len + 1);
            data->player_heading = 1;
        }
        else if (keycode == 125 && data->map[data->player + (data->info.min_line_len + 1)] != '1')
        {
            data->map[data->player] = '0';
            data->map[data->player + (data->info.min_line_len + 1)] = 'P';
            data->player = data->player + (data->info.min_line_len + 1);
            data->player_heading = 2;
        }
    }
}

void make_moves(t_game_data *data, int keycode)
{
    if (keycode == 126 || keycode == 125)
        up_down_moves(data, keycode);
    else if (keycode == 124 && data->map[data->player + 1] != '1')
    {
        data->map[data->player] = '0';
        data->map[data->player + 1] = 'P';
        data->player++;
        data->player_heading = 3;
    }
    else if (keycode == 123 && data->map[data->player - 1] != '1')
    {
        data->map[data->player] = '0';
        data->map[data->player - 1] = 'P';
        data->player--;
        data->player_heading = 4;
    }
}