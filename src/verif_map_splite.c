/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map_splite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:35:30 by yun               #+#    #+#             */
/*   Updated: 2020/10/18 13:03:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	replace_zero_splite(t_param *ptr, int size, int y)
{
	int x;

	x = 0;
	while (x < size)
	{
		if (ptr->verif_map[y][x] != '1'
		&& ptr->verif_map[y][x] != '0' && ptr->verif_map[y][x] != '2')
		{
			if (x > 0 && ptr->verif_map[y][x - 1] != '1')
				ptr->verif_map[y][x - 1] = '3';
			if (x < (size - 1) && ptr->verif_map[y][x + 1] != '1')
				ptr->verif_map[y][x + 1] = '3';
			if (y > 0 && ptr->verif_map[y - 1][x] != '1')
				ptr->verif_map[y - 1][x] = '3';
			if (y < (ptr->nb_line - 1) && ptr->verif_map[y + 1][x] != '1')
				ptr->verif_map[y + 1][x] = '3';
		}
		x++;
	}
	return (y + 1);
}

int	replace_zero_next(t_param *ptr, int size, int y)
{
	int x;

	x = size - 1;
	while (x >= 0)
	{
		if (ptr->verif_map[y][x] != '1'
		&& ptr->verif_map[y][x] != '0' && ptr->verif_map[y][x] != '2')
		{
			ptr->verif_map[y][x] = '3';
			if (x > 0 && ptr->verif_map[y][x - 1] != '1')
				ptr->verif_map[y][x - 1] = '3';
			if (x < (size - 1) && ptr->verif_map[y][x + 1] != '1')
				ptr->verif_map[y][x + 1] = '3';
			if (y > 0 && ptr->verif_map[y - 1][x] != '1')
				ptr->verif_map[y - 1][x] = '3';
			if (y < (ptr->nb_line - 1) && ptr->verif_map[y + 1][x] != '1')
				ptr->verif_map[y + 1][x] = '3';
		}
		x--;
	}
	return (y - 1);
}

int	replace_zero(t_param *ptr)
{
	int y;
	int i;
	int size;

	size = ft_strlen(ptr->map[0]);
	i = 0;
	while (i < ptr->nb_line)
	{
		y = 0;
		while (y < ptr->nb_line)
			y = replace_zero_splite(ptr, size, y);
		y = ptr->nb_line - 1;
		while (y >= 0)
			y = replace_zero_next(ptr, size, y);
		i++;
	}
	return (0);
}

int	verif_contour(t_param *ptr)
{
	int y;
	int x;
	int size;

	size = ft_strlen(ptr->map[0]);
	x = 0;
	while (x < size)
	{
		if (ptr->verif_map[0][x] == '3'
		|| ptr->verif_map[ptr->nb_line - 1][x] == '3')
			return (-1);
		x++;
	}
	y = 0;
	while (y < ptr->nb_line)
	{
		if (ptr->verif_map[y][0] == '3' || ptr->verif_map[y][size - 1] == '3')
			return (-1);
		y++;
	}
	return (0);
}

int	count_sprite(t_param *ptr)
{
	int y;
	int x;

	ptr->nb_sprite = 0;
	y = 0;
	while (y < ptr->nb_line)
	{
		x = 0;
		while (ptr->map[y][x])
		{
			if (ptr->map[y][x] == '2')
				ptr->nb_sprite++;
			x++;
		}
		y++;
	}
	return (0);
}
