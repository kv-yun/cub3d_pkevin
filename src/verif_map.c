/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:22:17 by yun               #+#    #+#             */
/*   Updated: 2020/10/16 13:36:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	replace_space(t_param *ptr)
{
	int x;
	int y;
	int size;

	size = ft_strlen(ptr->map[0]);
	y = 0;
	while (y < ptr->nb_line)
	{
		x = 0;
		while (x < size)
		{
			if (ptr->verif_map[y][x] == ' ')
				ptr->verif_map[y][x] = '0';
			x++;
		}
		y++;
	}
}

int		ft_strdup_splite(t_param *ptr)
{
	int i;
	int j;

	i = 0;
	while (i < ptr->nb_line)
	{
		j = 0;
		while (j < ft_strlen(ptr->map[0]))
		{
			ptr->verif_map[i][j] = ptr->map[i][j];
			j++;
		}
		ptr->verif_map[i][j] = '\0';
		i++;
	}
	return (0);
}

int		ft_strdup_c(t_param *ptr)
{
	int i;

	if (!(ptr->verif_map = malloc((ptr->nb_line + 1) * sizeof(char*))))
		return (exit_verif(ptr, 0));
	i = 0;
	while (i < ptr->nb_line)
	{
		if (!(ptr->verif_map[i] =
		malloc((ft_strlen(ptr->map[0]) + 1) * sizeof(char))))
			return (exit_verif(ptr, i));
		i++;
	}
	return (ft_strdup_splite(ptr));
}

int		ft_verif_map(t_param *ptr)
{
	ft_strdup_c(ptr);
	verif_last(ptr);
	if (ptr->error == 2)
		return (-1);
	if ((player_spawn(ptr) < 0))
		return (-1);
	replace_space(ptr);
	replace_zero(ptr);
	if ((verif_contour(ptr)) < 0)
		return (-1);
	if ((count_sprite(ptr)) < 0)
		return (-1);
	if (ft_strlen(ptr->verif_map[0]) < 3)
		return (-1);
	return (1);
}
