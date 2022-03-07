#include "./so_long.h"

int is_valide_move (t_game_data *data, int keycode)
{
    if (data->map[data->player - (data->info.min_line_len + 1)] != '1' && keycode == 126)
        return (1);
    else if (data->map[data->player + (data->info.min_line_len + 1)] != '1' && keycode == 125)
        return (1);
    else if (data->map[data->player - 1] != '1' && keycode == 123)
        return (1);
    else if (data->map[data->player + 1] != '1' && keycode == 124)
        return (1);
    else
        return (0);
}

int is_portal_move (t_game_data *data, int keycode)
{
    if (data->map[data->player + (data->info.min_line_len + 1)] == 'E' && keycode == 125)
        return (1);
    else if (data->map[data->player - (data->info.min_line_len + 1)] == 'E' && keycode == 126)
        return (1);
    else if (data->map[data->player - 1] == 'E' && keycode == 123)
        return (1);
    else if (data->map[data->player + 1] == 'E' && keycode == 124)
        return (1);
    else
        return (0);
}

int is_lose_move (t_game_data *data, int keycode)
{
    if (data->map[data->player + (data->info.min_line_len + 1)] == 'T' && keycode == 125)
        return (1);
    else if (data->map[data->player - (data->info.min_line_len + 1)] == 'T' && keycode == 126)
        return (1);
    else if (data->map[data->player - 1] == 'T' && keycode == 123)
        return (1);
    else if (data->map[data->player + 1] == 'T' && keycode == 124)
        return (1);
    else
        return (0);
}

int validate_move(t_game_data *data, int keycode)
{
    if (is_valide_move(data, keycode))
    {
        if (is_portal_move(data, keycode) && data->info.collectible_count == 0)
        {
            data->made_moves++;
            return (2);
        }
        else if (is_portal_move(data, keycode))
            return (0);
        else if (is_lose_move(data, keycode))
            return (3);
        else
        {
            data->made_moves++;
            return (1);
        }
    }
    return (0);
}

t_point new_point(int x, int y)
{
    t_point point;

    point.x = x;
    point.y = y;
    return (point);
}