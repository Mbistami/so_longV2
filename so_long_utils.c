/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:46:53 by mbistami          #+#    #+#             */
/*   Updated: 2022/02/28 23:08:56 by mbistami         ###   ########.fr       */
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

void draw_game(t_game_data *data)
{
    char *string;
    char *moves;

    moves = ft_itoa(data->made_moves);
    string = ft_strjoin("Moves :", moves);
    mlx_clear_window(data->vars.mlx, data->vars.win);
    draw_map(data, 1);
    mlx_string_put(data->vars.mlx, data->vars.win, data->info.square_size / 2, 3, 0x00FF00, string);
    free(string);
    free(moves);
}

int	draw_animated_coin (t_game_data *data)
{
	
	int x = 0;
    int y = 0;
    int i = 0;
    
    if (data->in_game)
    {
        
        if (data->coin_data.count == data->coin_data.frames * 800)
        {
            draw_game(data);
        }
        if (data->coin_data.count == data->coin_data.frames * 800)
        {
            data->coin_data.frames++;
            data->portal_data.frames++;
        }
        if (data->coin_data.count++ >= 4800)
            data->coin_data.count = 0;
        if (data->coin_data.frames >= 6)
            data->coin_data.frames = 0;
        if (data->portal_data.frames >= 14)
            data->portal_data.frames = 0;
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
    int     portal_frames;

    map = data->map;
    portal_frames = 0;
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
        else if (map[i] == 'E')
        {
            if (data->portal_data.is_open)
            {
                mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.items.portal[data->portal_data.frames], point.x, point.y);
                if (data->player_won)
                {
                    mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.player, point.x, point.y);
                    data->player_won = 2;
                }
            }
            else
                mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.items.portal[13], point.x, point.y);
        }
        else if (map[i] == 'T')
            mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.items.trap[data->portal_data.frames], point.x, point.y);
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
        if (data->in_game)
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

int validate_move(t_game_data *data, int keycode)
{
    if (((data->map[data->player - (data->info.min_line_len + 1)] != '1' && keycode == 126) || (data->map[data->player + (data->info.min_line_len + 1)] != '1' && keycode == 125) || (data->map[data->player - 1] != '1' && keycode == 123) || (data->map[data->player + 1] != '1' && keycode == 124)))
    {
        if ((((data->map[data->player + (data->info.min_line_len + 1)] == 'E' && keycode == 125) || (data->map[data->player - (data->info.min_line_len + 1)] == 'E' && keycode == 126) || (data->map[data->player - 1] == 'E' && keycode == 123) || (data->map[data->player + 1] == 'E' && keycode == 124)) && data->info.collectible_count == 0))
        {
            data->made_moves++;
            return (2);
        }
        else if ((data->map[data->player - (data->info.min_line_len + 1)] == 'E' && keycode == 126) || (data->map[data->player + (data->info.min_line_len + 1)] == 'E' && keycode == 125) || ((data->map[data->player - 1] == 'E' && keycode == 123) || (data->map[data->player + 1] == 'E' && keycode == 124)))
            return (0);
        else if ((((data->map[data->player + (data->info.min_line_len + 1)] == 'T' && keycode == 125) || (data->map[data->player - (data->info.min_line_len + 1)] == 'T' && keycode == 126) || (data->map[data->player - 1] == 'T' && keycode == 123) || (data->map[data->player + 1] == 'T' && keycode == 124))))
            return (3);
        else
        {
            data->made_moves++;
            return (1);
        }
    }
    return (0);
}

void draw_winner_screen (t_game_data *data, int win)
{
    char *moves;
    char *string;
    char *tmp;

    moves = ft_itoa(data->made_moves);
    string = ft_strjoin("WITH ", moves);
    tmp = ft_strjoin(string, " MOVES");
    mlx_destroy_window(data->vars.mlx, data->vars.win);
    data->vars.win = mlx_new_window(data->vars.mlx, 500, 500, "./so_long/you_won");
    if (win == 1)
    {
        mlx_string_put(data->vars.mlx, data->vars.win, 215, 250, 0x00FF00, "YOU WON");
        mlx_string_put(data->vars.mlx, data->vars.win, 190, 268, 0x00FF00, tmp);
    }
    else
    {
        mlx_string_put(data->vars.mlx, data->vars.win, 215, 250, 0xFF0000, "YOU LOST");
        mlx_string_put(data->vars.mlx, data->vars.win, 190, 268, 0xFF0000, tmp);
    }
    free(moves);
    free(string);
    free(tmp);
}

void player_won (t_game_data *data)
{
    data->player_won = 1;
    data->map[data->player] = '0';
    data->in_game = 0;
    mlx_clear_window(data->vars.mlx, data->vars.win);
    draw_winner_screen(data, 1);
}

void player_lost (t_game_data *data)
{
    data->player_won = 1;
    data->map[data->player] = '0';
    data->in_game = 0;
    mlx_clear_window(data->vars.mlx, data->vars.win);
    draw_winner_screen(data, 2);
}

void up_down_moves(t_game_data *data, int keycode)
{
    if (keycode == 126 && validate_move(data, keycode) == 1)
    {
        data->map[data->player] = '0';
        data->map[data->player - (data->info.min_line_len + 1)] = 'P';
        data->player = data->player - (data->info.min_line_len + 1);
    }
    else if (keycode == 125 && validate_move(data,keycode) == 1)
    {
        data->map[data->player] = '0';
        data->map[data->player + (data->info.min_line_len + 1)] = 'P';
        data->player = data->player + (data->info.min_line_len + 1);
    }
    else if (validate_move(data, keycode) == 2)
        player_won(data);
    else if (validate_move(data, keycode) == 3)
        player_lost(data);
}

int get_heading(int keycode)
{
    if (keycode == 124)
        return (3);
    else if (keycode == 123)
        return (4);
    else if (keycode == 126)
        return (1);
    else
        return (2);
    return 0;
}

void make_moves(t_game_data *data, int keycode)
{
    if (keycode == 126 || keycode == 125)
        up_down_moves(data, keycode);
    else if (keycode == 124 && validate_move(data, keycode) == 1)
    {
        data->map[data->player] = '0';
        data->map[data->player + 1] = 'P';
        data->player++;
    }
    else if (keycode == 123 && validate_move(data, keycode) == 1)
    {
        data->map[data->player] = '0';
        data->map[data->player - 1] = 'P';
        data->player--;
    }
    else if (validate_move(data, keycode) == 2)
        player_won(data);
    else if (validate_move(data, keycode) == 3)
        player_lost(data);
    data->player_heading = get_heading(keycode);
    set_heading(data, 'P', new_point(0, 0));
}