/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 19:23:04 by mbistami          #+#    #+#             */
/*   Updated: 2022/02/14 04:55:49 by mbistami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./so_long.h"

int handle_errors(t_game_data *data, int argv, char **argc)
{
	int fd;
	
	if (argv - 1)
	{
		fd = open(argc[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Error");
			return (0);
		}
		else if (!parse_map(data, fd))
		{
			printf("Error: wrong map format\n");
			return (0);
		}
		else if (!ft_strlen(data->map))
			printf("Error: empty map\n");
	}
	else
	{
		perror("Error");
		return (0);
	}
	return (1);
}

void load_assets (t_game_data *data)
{
	int     img_w;
    int     img_h;
    char    *relative_path;
	void	*img;
	char	*string;
	int		i;

	i = 0;
    relative_path = "/Users/mbistami/so_long/dirt.xpm";
    data->assets.world.walls = mlx_xpm_file_to_image(data->vars.mlx, relative_path, &img_w, &img_h);
    relative_path = "/Users/mbistami/so_long/grass.xpm";
    data->assets.world.ground = mlx_xpm_file_to_image(data->vars.mlx, relative_path, &img_w, &img_h);
    relative_path = "/Users/mbistami/so_long/water.xpm";
    data->assets.world.water = mlx_xpm_file_to_image(data->vars.mlx, relative_path, &img_w, &img_h);
    relative_path = "/Users/mbistami/so_long/Character.xpm";
    data->assets.player = mlx_xpm_file_to_image(data->vars.mlx, relative_path, &img_w, &img_h);
    string = ft_strdup("./assets/coin_frame_1.xpm");
	printf("collectible count on loading assets: %d\n", data->info.collectible_count);
	data->assets.items.coin = malloc(sizeof(void *) * 6);
	data->coin_data.count = 0;
	data->coin_data.frames = 0;
	// data->assets.items.coin[0] = mlx_xpm_file_to_image(data->vars.mlx, string, &img_w, &img_h);
	while(i != 6)
	{
		string[ft_strlen(string) - 5] = i + '1';
		printf("%d\n", i);
		data->assets.items.coin[i] = mlx_xpm_file_to_image(data->vars.mlx, string, &img_w, &img_h);
		mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->assets.items.coin[i], 0, 0);
		i++;
	}
	free(string);
	// data->assets.items.portal = malloc(sizeof(void *) * )
	
}

int key_hook(int keycode, t_game_data *data)
{
	if (data->in_game)
	{
		printf("%d\n", keycode);
		make_moves(data, keycode);
		mlx_clear_window(data->vars.mlx, data->vars.win);
		draw_map(data, 0);
	}
	else
	{
		mlx_destroy_window(data->vars.mlx, data->vars.win);
		data->vars.win = mlx_new_window(data->vars.mlx, data->info.window_width, data->info.square_size * data->info.lines_count, "./so_long");
		draw_map(data, 1);
		data->in_game = 1;
		mlx_hook(data->vars.win, 2, 0, key_hook, data);
	}
	printf("%d", data->in_game = 1);
	return (0);
}

int ft_exit(t_game_data *data)
{
	free(data->map);
    exit(0);
    return (0);
}

int main(int argv, char **argc)
{
	t_game_data data;
	if(!handle_errors(&data, argv, argc))
		return (1);
	data.vars.mlx = mlx_init();
	data.info.square_size = 32;
    data.info.window_width = data.info.square_size * data.info.min_line_len;
	data.vars.win = mlx_new_window(data.vars.mlx, 416, 160, "./so_long");
	printf("drawing %d %d\n", data.info.window_width, data.info.square_size * data.info.lines_count);
	data.in_game = 0;
	data.info.draw_coins = 0;
	load_assets(&data);
	// draw_map(&data, 1);
	mlx_loop_hook(data.vars.mlx, draw_animated_coin, &data);
	
	mlx_string_put(data.vars.mlx, data.vars.win, (416 / 2) - (416 / 3) , (160 / 2) - (160 / 8), 0x556E86, "PERESS ANY BUTTON TO START!");

	mlx_hook(data.vars.win, 2, 0, key_hook, &data);
	mlx_hook(data.vars.win, 17, 0, ft_exit, &data);
	system("leaks a.out");
	mlx_loop(data.vars.mlx);
}