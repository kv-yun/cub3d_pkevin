/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segfault.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 17:29:54 by yun               #+#    #+#             */
/*   Updated: 2020/10/16 15:40:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	verif_segfault(t_param *ptr, int x, int y)
{
	ptr->posx += (ptr->diry * 0.005) * x;
	if (ptr->posx <= 0.5)
		ptr->posx = 0.5;
	if (ptr->posx > (ft_strlen(ptr->map[0]) - 0.5))
		ptr->posx = ft_strlen(ptr->map[0]) - 0.5;
	ptr->posy += (ptr->dirx * 0.005) * y;
	if (ptr->posy <= 0.5)
		ptr->posy = 0.5;
	if (ptr->posy >= (ptr->nb_line - 0.5))
		ptr->posy = ptr->nb_line - 0.5;
	return (1);
}

int	close_prog(t_param *ptr)
{
	if (ptr->win)
		mlx_destroy_window(ptr->mlx, ptr->win);
	if (ptr->img)
		mlx_destroy_image(ptr->mlx, ptr->img);
	ft_leave(ptr);
	return (0);
}

int	verif_arg_next(char *str)
{
	int i;

	i = ft_strlen(str);
	if (i < 5)
		return (-1);
	if (str[i - 1] != 'b')
		return (-1);
	if (str[i - 2] != 'u')
		return (-1);
	if (str[i - 3] != 'c')
		return (-1);
	if (str[i - 4] != '.')
		return (-1);
	return (1);
}

int	verif_arg(char *str)
{
	int i;
	int fd;

	fd = -1;
	i = 0;
	if ((fd = open(str, O_DIRECTORY)) > 0)
	{
		write(1, "Error\n.cub file is directory\n", 29);
		close(fd);
		exit(0);
	}
	fd = verif_arg_next(str);
	if (fd == -1)
	{
		write(1, "Error\nIs not .cub file\n", 23);
		exit(0);
	}
	return (1);
}

int	verif_last(t_param *ptr)
{
	int		i;
	char	c;
	int		verif;

	verif = 0;
	c = '\0';
	i = 0;
	while (i < ft_strlen(ptr->map[0]) && verif == 0)
	{
		c = ptr->map[ptr->nb_line - 1][i];
		if (c != ' ' && c != '1' && c != 'N' && c != 'S'
		&& c != '0' && c != '2' && c != 'E' && c != 'W')
			verif = -1;
		i++;
	}
	if (ptr->error == 8 || verif == -1 || ptr->map[ptr->nb_line - 1][0] == '\0')
	{
		free_texture(ptr);
		write(1, "Error\nMap is not at the end of the file\n", 40);
		close_prog(ptr);
	}
	return (1);
}
