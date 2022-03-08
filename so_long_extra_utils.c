/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_extra_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 01:46:41 by mbistami          #+#    #+#             */
/*   Updated: 2022/03/08 02:06:31 by mbistami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int	get_heading(int keycode)
{
	if (keycode == 124)
		return (3);
	else if (keycode == 123)
		return (4);
	else if (keycode == 126)
		return (1);
	else
		return (2);
	return (0);
}

void	make_moves(t_game_data *data, int keycode)
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

void	draw_screen(t_game_data *data, int win, char *string)
{
	if (win == 1)
	{
		mlx_string_put(data->vars.mlx, data->vars.win,
			215, 250, 0x00FF00, "YOU WON");
		mlx_string_put(data->vars.mlx, data->vars.win,
			190, 268, 0x00FF00, string);
	}
	else
	{
		mlx_string_put(data->vars.mlx, data->vars.win,
			215, 250, 0xFF0000, "YOU LOST");
		mlx_string_put(data->vars.mlx, data->vars.win,
			190, 268, 0xFF0000, string);
	}
}

void	draw_winner_screen(t_game_data *data, int win)
{
	char	*moves;
	char	*string;
	char	*tmp;

	moves = ft_itoa(data->made_moves);
	string = ft_strjoin("WITH ", moves);
	tmp = ft_strjoin(string, " MOVES");
	mlx_destroy_window(data->vars.mlx, data->vars.win);
	data->vars.win = mlx_new_window(data->vars.mlx, 500,
			500, "./so_long/you_won");
	draw_screen(data, win, tmp);
	mlx_hook(data->vars.win, 2, 0, handle_click, data);
	mlx_hook(data->vars.win, 17, 0, handle_exit, data);
	data->player_won = 4;
	data->in_game = 0;
	free(moves);
	free(string);
	free(tmp);
}
