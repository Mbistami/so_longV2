/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_draw_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:46:54 by mbistami          #+#    #+#             */
/*   Updated: 2022/03/08 02:17:01 by mbistami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	draw_portal(t_game_data *data, t_point point)
{
	if (data->portal_data.is_open)
	{
		mlx_put_image_to_window(data->vars.mlx, data->vars.win,
			data->assets.items.portal[data->portal_data.frames],
			point.x, point.y);
		if (data->player_won != 4 && data->player_won)
		{
			mlx_put_image_to_window(data->vars.mlx, data->vars.win,
				data->assets.player, point.x, point.y);
			data->player_won = 2;
		}
	}
	else
		mlx_put_image_to_window(data->vars.mlx, data->vars.win,
			data->assets.items.portal[13], point.x, point.y);
}

void	draw_items(t_game_data *data, int i, t_point point)
{
	if (data->map[i] == 'C')
	{
		mlx_put_image_to_window(data->vars.mlx, data->vars.win,
			data->assets.items.coin[data->coin_data.frames], point.x, point.y);
		data->info.draw_coins = 1;
	}
	else if (data->map[i] == 'E')
		draw_portal(data, point);
	else if (data->map[i] == 'T')
		mlx_put_image_to_window(data->vars.mlx, data->vars.win,
			data->assets.items.trap[data->portal_data.frames],
			point.x, point.y);
	else if (data->map[i] == 'P')
		mlx_put_image_to_window(data->vars.mlx, data->vars.win,
			data->assets.player, point.x, point.y);
}

void	draw_wall(t_game_data *data, int i, t_point point)
{
	if (((i + 1) % (data->info.min_line_len + 1) == 1 || (i + 1)
			% (data->info.min_line_len + 1) == data->info.min_line_len)
		|| (i < data->info.min_line_len)
		|| (size_t)(i + data->info.min_line_len)
		> ft_strlen(data->map))
		mlx_put_image_to_window(data->vars.mlx, data->vars.win,
			data->assets.world.walls, point.x, point.y);
	else
		mlx_put_image_to_window(data->vars.mlx, data->vars.win,
			data->assets.world.water, point.x, point.y);
}

void	draw_asset(t_point point, t_game_data *data, int i)
{
	char	*map;
	int		portal_frames;

	map = data->map;
	portal_frames = 0;
	if (map[i] == '1' && map[i] != 10)
	{
		mlx_put_image_to_window(data->vars.mlx, data->vars.win,
			data->assets.world.ground, point.x, point.y);
		draw_wall(data, i, point);
	}
	else
	{
		mlx_put_image_to_window(data->vars.mlx, data->vars.win,
			data->assets.world.ground, point.x, point.y);
		draw_items(data, i, point);
		set_heading(data, map[i]);
	}
}

void	draw_map(t_game_data *data)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	while (data->map[i])
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
