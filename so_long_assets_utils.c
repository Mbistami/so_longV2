/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_assets_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:38:47 by mbistami          #+#    #+#             */
/*   Updated: 2022/03/08 02:12:40 by mbistami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	load_coin_assets(t_game_data *data)
{
	int		img_w;
	int		img_h;
	char	*string;
	int		i;

	string = ft_strdup("./assets/coin_frame_1.xpm");
	data->assets.items.coin = malloc(sizeof(void *) * 6);
	data->coin_data.count = 0;
	data->coin_data.frames = 0;
	i = 0;
	while (i != 6)
	{
		string[ft_strlen(string) - 5] = i + '1';
		data->assets.items.coin[i]
			= mlx_xpm_file_to_image(data->vars.mlx, string, &img_w, &img_h);
		mlx_put_image_to_window(data->vars.mlx,
			data->vars.win, data->assets.items.coin[i], 0, 0);
		i++;
	}
	free(string);
	i = 0;
}

void	load_portal_assets(t_game_data *data)
{
	int		img_w;
	int		img_h;
	char	*string;
	int		i;
	int		j;

	string = ft_strdup("./assets/portal_frame_1.xpm");
	data->assets.items.portal = malloc(sizeof(void *) * 15);
	i = 0;
	j = 0;
	while (i != 14)
	{
		if (i == 9)
		{
			free(string);
			string = ft_strdup("./assets/portal_frame_10.xpm");
			j = 0;
		}
		string[ft_strlen(string) - 5] = j++ + '1';
		data->assets.items.portal[i] = mlx_xpm_file_to_image(data->vars.mlx,
				string, &img_w, &img_h);
		mlx_put_image_to_window(data->vars.mlx, data->vars.win,
			data->assets.items.portal[i++], 0, 32);
	}
	free(string);
}

void	load_main_assets(t_game_data *data)
{
	int		img_w;
	int		img_h;
	char	*relative_path;

	relative_path = "./assets/cobblestone.xpm";
	data->assets.world.walls
		= mlx_xpm_file_to_image(data->vars.mlx, relative_path, &img_w, &img_h);
	relative_path = "./assets/stone.xpm";
	data->assets.world.ground
		= mlx_xpm_file_to_image(data->vars.mlx, relative_path, &img_w, &img_h);
	relative_path = "./assets/bush.xpm";
	data->assets.world.water
		= mlx_xpm_file_to_image(data->vars.mlx, relative_path, &img_w, &img_h);
	relative_path = "./assets/Character.xpm";
	data->assets.player
		= mlx_xpm_file_to_image(data->vars.mlx, relative_path, &img_w, &img_h);
}

void	load_traps_assets(t_game_data *data)
{
	int		img_w;
	int		img_h;
	char	*string;
	int		i;
	int		j;

	string = ft_strdup("./assets/trap_frame_1.xpm");
	data->assets.items.trap = malloc(sizeof(void *) * 15);
	i = 0;
	j = 0;
	while (i != 14)
	{
		if (i == 9)
		{
			free(string);
			string = ft_strdup("./assets/trap_frame_10.xpm");
			j = 0;
		}
		string[ft_strlen(string) - 5] = j++ + '1';
		data->assets.items.trap[i]
			= mlx_xpm_file_to_image(data->vars.mlx, string, &img_w, &img_h);
		mlx_put_image_to_window(data->vars.mlx,
			data->vars.win, data->assets.items.trap[i++], 0, 64);
	}
	free(string);
}

void	load_assets(t_game_data *data)
{
	data->portal_data.is_open = 0;
	load_main_assets(data);
	load_portal_assets(data);
	load_traps_assets(data);
	load_coin_assets(data);
}
