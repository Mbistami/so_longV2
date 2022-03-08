/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:46:53 by mbistami          #+#    #+#             */
/*   Updated: 2022/03/08 00:46:27 by mbistami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_game(t_game_data *data)
{
	char	*string;
	char	*moves;

	moves = ft_itoa(data->made_moves);
	string = ft_strjoin("Moves :", moves);
	mlx_clear_window(data->vars.mlx, data->vars.win);
	draw_map(data, 1);
	mlx_string_put(data->vars.mlx, data->vars.win,
		data->info.square_size / 2, 3, 0x00FF00, string);
	free(string);
	free(moves);
}

void	set_heading(t_game_data *data, char type, t_point point)
{
	int	img_h;

	if (type == 'P')
	{
		if (data->player_heading == 1)
			data->assets.player = mlx_xpm_file_to_image(data->vars.mlx,
					"./assets/CharacterHeadingUp.xpm", &img_h, &img_h);
		else if (data->player_heading == 3)
			data->assets.player = mlx_xpm_file_to_image(data->vars.mlx,
					"./assets/CharacterHeadingRight.xpm", &img_h, &img_h);
		else if (data->player_heading == 4)
			data->assets.player = mlx_xpm_file_to_image(data->vars.mlx,
					"./assets/CharacterHeadingLeft.xpm", &img_h, &img_h);
		else
			data->assets.player = mlx_xpm_file_to_image(data->vars.mlx,
					"./assets/Character.xpm", &img_h, &img_h);
		mlx_put_image_to_window(data->vars.mlx, data->vars.win,
			data->assets.player, point.x, point.y);
	}
}

void	player_won(t_game_data *data)
{
	data->player_won = 1;
	data->map[data->player] = '0';
	data->in_game = 0;
	mlx_clear_window(data->vars.mlx, data->vars.win);
	draw_winner_screen(data, 1);
}

void	player_lost(t_game_data *data)
{
	data->player_won = 1;
	data->map[data->player] = '0';
	data->in_game = 0;
	mlx_clear_window(data->vars.mlx, data->vars.win);
	draw_winner_screen(data, 2);
}

void	up_down_moves(t_game_data *data, int keycode)
{
	if (keycode == 126 && validate_move(data, keycode) == 1)
	{
		data->map[data->player] = '0';
		data->map[data->player - (data->info.min_line_len + 1)] = 'P';
		data->player = data->player - (data->info.min_line_len + 1);
	}
	else if (keycode == 125 && validate_move(data, keycode) == 1)
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
