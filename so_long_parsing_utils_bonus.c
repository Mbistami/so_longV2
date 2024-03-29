/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_parsing_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 19:54:11 by mbistami          #+#    #+#             */
/*   Updated: 2022/03/09 20:21:12 by mbistami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	save_game_data(char c, t_game_data *data, int col, int lines)
{
	if (lines >= 0)
	{
		if (c == 'C')
			data->info.collectible_count += 1;
		else if (c == 'E')
			data->info.exit_count += 1;
		else if (c == 'P')
		{
			data->info.starting_pos_count += 1;
			if (lines >= 0)
				data->player = lines * (data->info.min_line_len + 1) + col;
		}
		else if (!is_valid_character(c))
			data->info.error = 1;
	}
	else if (c == 'C')
		data->info.collectible_count--;
}

int	validate_char(char *readed_line, t_game_data *data, int col, int line)
{
	if (ft_strlen(readed_line) - 1 != (size_t)data->info.min_line_len)
	{
		if (readed_line[ft_strlen(readed_line) - 1] == '\n')
			return (0);
		else if (ft_strlen(readed_line) != (size_t)data->info.min_line_len)
			return (0);
	}
	if ((line == 0) || readed_line[ft_strlen(readed_line) - 1] != '\n')
	{
		if (((readed_line[col] != '1' && readed_line[col]
					!= 'T') && (readed_line[col] != 10)))
			return (0);
	}
	else
	{
		if ((readed_line[0] != '1')
			|| readed_line[ft_strlen(readed_line) - 2] != '1')
			return (0);
		save_game_data(readed_line[col], data, col, line);
	}
	return (1);
}

void	save_map(t_game_data *data, char *map, int lines)
{
	data->map = map;
	data->info.lines_count = lines;
	if (!data->info.starting_pos_count || !data->info.exit_count)
		data->info.error = 1;
}

void	init_parser(int fd, char **readed_line,
	char **container, t_game_data *data)
{
	*readed_line = get_next_line(fd);
	if (*readed_line)
		data->info.min_line_len = ft_strlen(*readed_line) - 1;
	*container = (char *)malloc(sizeof(char));
	*container[0] = '\0';
}

int	parse_map(t_game_data *data, int fd)
{
	char	*container;
	char	*readed_line;
	char	*tmp;
	int		line;
	int		col;

	init_parser(fd, &readed_line, &container, data);
	line = 0;
	while (readed_line && !data->info.error)
	{
		col = 0;
		while (readed_line[col])
			if (!validate_char(readed_line, data, col++, line))
				return (0);
		tmp = ft_strjoin(container, readed_line);
		free(container);
		container = tmp;
		free(readed_line);
		readed_line = get_next_line(fd);
		line++;
	}
	save_map(data, container, line);
	if (data->info.error)
		handle_exit(data, 1);
	return (1);
}
