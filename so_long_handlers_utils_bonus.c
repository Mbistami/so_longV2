/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_handlers_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:37:20 by mbistami          #+#    #+#             */
/*   Updated: 2022/03/09 20:21:04 by mbistami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	update_game_data(t_game_data *data)
{
	int	i;

	i = 0;
	data->info.collectible_count = 0;
	data->info.exit_count = 0;
	while (data->map[i])
	{
		if (data->map[i] == 'C')
			data->info.collectible_count++;
		else if (data->map[i] == 'E')
			data->info.exit_count++;
		i++;
	}
	if (!data->info.collectible_count)
		data->portal_data.is_open = 1;
}

int	handle_click(int keycode, t_game_data *data)
{
	if (keycode == 53 || data->player_won == 4)
		handle_exit(data, 0);
	else if (data->in_game)
	{
		make_moves(data, keycode);
		update_game_data(data);
		draw_map(data);
		return (0);
	}
	else if (!data->player_won)
	{
		mlx_destroy_window(data->vars.mlx, data->vars.win);
		data->vars.win = mlx_new_window(data->vars.mlx, data->info.window_width,
				data->info.square_size * data->info.lines_count,
				"./so_long/in_game");
		draw_map(data);
		data->in_game = 1;
		mlx_hook(data->vars.win, 2, 0, handle_click, data);
		return (0);
	}
	if (data->player_won == 2)
		draw_winner_screen(data, 1);
	return (0);
}

int	handle_exit(t_game_data *data, int is_error)
{
	if (is_error)
		perror("Error");
	free(data->map);
	exit(1);
}

int	handle_errors(t_game_data *data, int argv, char **argc)
{
	int	fd;

	if (argv - 1 && is_valid_file(argc[1]))
	{
		fd = open(argc[1], O_RDONLY);
		if (fd < 0)
		{
			perror("error");
			return (0);
		}
		else if (!parse_map(data, fd))
		{
			perror("Error: wrong map format\n");
			return (0);
		}
		else if (!ft_strlen(data->map))
			perror("Error: empty map\n");
	}
	else
	{
		perror("Error");
		return (0);
	}
	return (1);
}

int	handle_auto_draw(t_game_data *data)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	if (data->in_game)
	{
		if (data->coin_data.count == data->coin_data.frames * 800)
			draw_game(data);
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
