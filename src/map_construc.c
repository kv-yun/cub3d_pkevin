/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_construc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:28:40 by yun               #+#    #+#             */
/*   Updated: 2020/10/17 16:17:34 by yun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	inv_line(t_param *ptr, int i)
{
	int		size;
	char	temp;
	int		j;

	size = ft_strlen(ptr->map[i]);
	j = 0;
	while (j < size / 2)
	{
		temp = ptr->map[i][size - 1 - j];
		ptr->map[i][size - 1 - j] = ptr->map[i][j];
		ptr->map[i][j] = temp;
		j++;
	}
	return (1);
}

int	ft_verif_l(t_param *ptr, int i)
{
	int		j;
	char	c;
	int		x;
	int		fl;

	fl = 0;
	x = 0;
	j = 0;
	while (j < ptr->last_size)
	{
		c = ptr->temp_map[j + (i * ptr->last_size)];
		if (c != ' ' && c != '1' && c != '0' && c != 'N'
		&& c != 'S' && c != 'W' && c != 'E' && c != '2'
		&& ptr->error != 8)
			ptr->error = 2;
		ptr->map[i][x] = c;
		x++;
		c = '\0';
		j++;
	}
	ptr->map[i][x] = '\0';
	return (inv_line(ptr, i));
}

int	ft_map_construct(t_param *ptr)
{
	int i;

	i = 0;
	if (!(ptr->map = malloc((ptr->nb_line + 1) * sizeof(char*))))
		return (leak_map_construct(ptr, 0));
	while (i < ptr->nb_line + 1)
	{
		if (!(ptr->map[i] = malloc((((ptr->last_size) + 1))
		* sizeof(char))))
			return (leak_map_construct(ptr, i));
		i++;
	}
	i = 0;
	while (i < ptr->nb_line)
	{
		if ((ft_verif_l(ptr, i)) == -1)
			return (-1);
		i++;
	}
	ptr->map[i][0] = '\0';
	free(ptr->temp_map);
	return (ft_verif_map(ptr));
}
