/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:30:28 by yun               #+#    #+#             */
/*   Updated: 2020/10/17 16:24:01 by yun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_utile_map(t_param *ptr, char **new, int nb_line, int size)
{
	int i;
	int x;
	int j;

	x = 0;
	i = 0;
	while (nb_line > 0)
	{
		j = 0;
		while (j < ptr->last_size && ptr->temp_map)
		{
			new[0][x] = ptr->temp_map[i];
			x++;
			i++;
			j++;
		}
		while (j < size)
		{
			new[0][x] = ' ';
			j++;
			x++;
		}
		nb_line--;
	}
	return (x);
}

int		ft_utile_map_next(char **new, char *line, t_param *ptr, int size)
{
	int i;
	int x;

	x = ft_utile_map(ptr, new, ptr->nb_line, size);
	if (line[0] == '\0')
		ptr->error = 8;
	i = 0;
	while (line[i])
	{
		new[0][x] = line[i];
		x++;
		i++;
	}
	while (i < ptr->last_size)
	{
		new[0][x] = ' ';
		i++;
		x++;
	}
	new[0][x] = '\0';
	return (0);
}

char	*ft_add_map(t_param *ptr, char *line, int size, int nb_line)
{
	char	*new;

	if (size > ptr->last_size)
	{
		if (!(new = malloc((((nb_line + 1) * size) + 1) * sizeof(char))))
			return (leak_map(ptr, line));
	}
	else
	{
		if (!(new = malloc((((nb_line + 1)
		* ptr->last_size) + 1) * sizeof(char))))
			return (leak_map(ptr, line));
	}
	if ((ft_utile_map_next(&new, line, ptr, size)) < 0)
	{
		free(new);
		free(line);
		new = NULL;
	}
	if (size > ptr->last_size)
		ptr->last_size = size;
	if (ptr->temp_map)
		free(ptr->temp_map);
	return (new);
}

int		ft_cpy_line(t_param *ptr, char *line)
{
	int i;

	if (!(ptr->temp_map = malloc((ft_strlen(line) + 1) * sizeof(char))))
	{
		ptr->error = 2;
		return (-1);
	}
	i = 0;
	while (line[i])
	{
		ptr->temp_map[i] = line[i];
		i++;
	}
	ptr->temp_map[i] = '\0';
	return (0);
}

int		ft_map(t_param *ptr, char **line)
{
	int		size;

	if ((ft_cpy_line(ptr, line[0])) < 0)
		return (-1);
	ptr->last_size = ft_strlen(ptr->temp_map);
	while ((size = get_next_line(ptr->fd, &line[0])) > 0)
	{
		ptr->temp_map = ft_add_map(ptr, *line, ft_strlen(*line), ptr->nb_line);
		if (!ptr->temp_map)
		{
			ptr->error = 2;
			return (-1);
		}
		ptr->nb_line++;
	}
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	if ((ft_map_construct(ptr) < 0) && (ptr->error = 2) == 2)
		return (-1);
	return (0);
}
