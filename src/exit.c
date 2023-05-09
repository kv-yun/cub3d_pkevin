/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 12:50:38 by yun               #+#    #+#             */
/*   Updated: 2020/10/18 11:29:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_leave(t_param *ptr)
{
	int i;

	i = 0;
	while (i < ptr->nb_line)
	{
		free(ptr->map[i]);
		free(ptr->verif_map[i]);
		i++;
	}
	free(ptr->map[ptr->nb_line]);
	free(ptr->map);
	free(ptr->verif_map);
	if (ptr->img2)
		mlx_destroy_image(ptr->mlx, ptr->img2);
	if (ptr->img3)
		mlx_destroy_image(ptr->mlx, ptr->img3);
	if (ptr->img4)
		mlx_destroy_image(ptr->mlx, ptr->img4);
	if (ptr->img5)
		mlx_destroy_image(ptr->mlx, ptr->img5);
	if (ptr->img6)
		mlx_destroy_image(ptr->mlx, ptr->img6);
	if (ptr->mlx)
		free(ptr->mlx);
	exit(0);
}

char	*leak_map(t_param *ptr, char *line)
{
	if (line)
		free(line);
	if (ptr->temp_map)
		free(ptr->temp_map);
	return (NULL);
}

int		leak_map_construct(t_param *ptr, int i)
{
	while (i > 0)
	{
		free(ptr->map[i - 1]);
		i--;
	}
	if (ptr->map)
		free(ptr->map);
	if (ptr->temp_map)
	{
		free(ptr->temp_map);
		ptr->temp_map = NULL;
	}
	return (-1);
}

int		exit_image(t_param *ptr)
{
	write(1, "Error\nImage failed please relaunch programme\n", 45);
	close_prog(ptr);
	return (1);
}

int		exit_verif(t_param *ptr, int i)
{
	while (i > 0)
	{
		free(ptr->verif_map[i - 1]);
		i--;
	}
	if (ptr->verif_map)
		free(ptr->verif_map);
	i = 0;
	while (i < ptr->nb_line)
	{
		free(ptr->map[i]);
		i++;
	}
	free(ptr->map);
	write(1, "Error\nMalloc failed\n", 20);
	free_texture(ptr);
	free(ptr->mlx);
	exit(0);
	return (-1);
}
