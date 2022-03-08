/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 19:23:04 by mbistami          #+#    #+#             */
/*   Updated: 2022/03/08 23:26:56 by mbistami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int	init(t_game_data *data, int argv, char **argc)
{
	data->info.error = 0;
	if (!handle_errors(data, argv, argc))
		return (0);
	data->vars.mlx = mlx_init();
	data->info.square_size = 32;
	data->info.window_width = data->info.square_size * data->info.min_line_len;
	data->vars.win = mlx_new_window(data->vars.mlx, 416, 160, "./so_long");
	data->in_game = 0;
	data->info.draw_coins = 0;
	data->player_won = 0;
	data->made_moves = 0;
	load_assets(data);
	mlx_loop_hook(data->vars.mlx, handle_auto_draw, data);
	mlx_string_put(data->vars.mlx, data->vars.win, (416 / 2) - (416 / 3),
		(160 / 2) - (160 / 8), 0x556E86, "PERESS ANY BUTTON TO START!");
	mlx_hook(data->vars.win, 2, 0, handle_click, data);
	mlx_hook(data->vars.win, 17, 0, handle_exit, data);
	return (1);
}

int	main(int argv, char **argc)
{
	t_game_data	data;

	if (!init(&data, argv, argc))
		return (1);
	mlx_loop(data.vars.mlx);
	return (0);
}
