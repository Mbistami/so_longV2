/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_parsing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbistami <mbistami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 19:54:11 by mbistami          #+#    #+#             */
/*   Updated: 2022/02/24 04:13:13 by mbistami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void save_game_data (char c, t_game_data *data, int col, int lines)
{
    if (lines >= 0)
    {
        if (c == 'C')
        data->info.collectible_count += 1;
        else if (c == 'E')
            data->info.exit_count += 1;
        else if (c == 'P')
        {
            data->info.starting_pos_count+= 1;
            if (lines >= 0)
                data->player = lines * (data->info.min_line_len + 1) + col;
            printf("player pos :%d\n", data->player);
        }
        else if ((c != '0' && c != '1') && (c != 10 && c != 'X')) // replace 13 && 10 with 13 (NEW LINE WINDOWS/MAC)
            data->info.error = 1;
    }
    else if (c == 'C')
        data->info.collectible_count--;
}

int validate_char(char* readed_line, t_game_data *data, int col, int line)
{
    if (ft_strlen(readed_line) - 1 != data->info.min_line_len) //
    {
        if (readed_line[ft_strlen(readed_line) - 1] == '\n')
            return 0;
        else if (ft_strlen(readed_line) != data->info.min_line_len)
            return 0;
    }
            
    if ((line == 0) || readed_line[ft_strlen(readed_line) - 1] != '\n')
    {
        if ((readed_line[col] != '1' && (readed_line[col] != 10)))
            return 0;
    }
    else
    {
        if (readed_line[0] != '1' || readed_line[ft_strlen(readed_line) - 2] != '1') 
            return 0;
        save_game_data(readed_line[col], data, col, line);
    }
    return (1);
}

void save_map (t_game_data *data, char *map, int lines)
{
	data->map = map;
	data->info.lines_count = lines;
}

int parse_map(t_game_data *data, int fd)
{
    char    *container;
    char    *readed_line;
    char    *tmp;
    int     line;
    int     col;

    readed_line = get_next_line(fd);
	if (readed_line)
    	data->info.min_line_len = ft_strlen(readed_line) - 1;
    container = (char *)malloc(sizeof(char));
    line = 0;
    container[0] = '\0';
    printf("[%s]%d\n", readed_line, data->info.error);
    while (readed_line && !data->info.error)
    {
        printf("%s\n", readed_line);
        col = 0;
        while (readed_line[col])
        {
            if (!validate_char(readed_line, data, col++, line))
                return (0);
        }   
        tmp = ft_strjoin(container, readed_line);
        free(container);
        container = tmp;
        // free(tmp);
        free(readed_line);
        readed_line = get_next_line(fd);
        line++;
    }
    // free(readed_line);
    save_map(data, container, line);
    return (1);
}