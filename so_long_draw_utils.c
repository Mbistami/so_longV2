#include "./so_long.h"

void draw_items (t_game_data *data, int i, t_point point)
{
    if (data->map[i] == 'C')
    {
        mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.items.coin[data->coin_data.frames], point.x, point.y);
        data->info.draw_coins = 1;
    }
    else if (data->map[i] == 'E')
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
    else if (data->map[i] == 'T')
        mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.items.trap[data->portal_data.frames], point.x, point.y);
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
        mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.world.ground, point.x, point.y);
        if (((i + 1) % (data->info.min_line_len + 1) == 1 || (i + 1) % (data->info.min_line_len + 1) == data->info.min_line_len)
            || (i < data->info.min_line_len) || i + data->info.min_line_len > ft_strlen(data->map))
            mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.world.walls, point.x, point.y);
        else
            mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.world.water, point.x, point.y);
    }
    else
    {
        mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.world.ground, point.x, point.y);
        draw_items(data, i, point);
        set_heading(data, map[i], point);
    }
}

void draw_map (t_game_data *data, int ignore_collectibles)
{
    int x = 0;
    int y = 0;
    int i = 0;
        
    while(data->map[i])
    {
        if (data->in_game)
            draw_asset(new_point(x, y), data, i);
        if (data->map[i] != 10)
            x += data->info.square_size;
        else 
        {
            x = 0;
            y += data->info.square_size;
        }
        i++;
    }
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
    mlx_hook(data->vars.win, 2, 0, handle_click, data);
    data->player_won = 4;
    free(moves);
    free(string);
    free(tmp);
}