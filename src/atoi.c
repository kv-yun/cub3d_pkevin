/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 17:54:11 by yun               #+#    #+#             */
/*   Updated: 2020/10/16 13:23:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi(char *str)
{
	int i;
	int nb;

	nb = 0;
	i = 0;
	while (str[i] == ' ' && str[i])
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	if (str[i] == '0' && str[i + 1] >= '0' && str[i + 1] <= '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

void	ft_resolution(char *line, t_param *ptr)
{
	int maxwidth;
	int maxheight;

	mlx_get_screen_size(ptr->mlx, &maxwidth, &maxheight);
	ptr->flag = 0;
	line++;
	ptr->width = ft_atoi(line);
	if (ptr->width == -1 || ptr->width <= 0)
	{
		ptr->width = 1;
		ptr->error = 3;
	}
	if (ptr->width >= maxwidth)
		ptr->width = maxwidth;
	while (*line == ' ' && line && ptr->flag == 0)
		line++;
	while (*line >= '0' && *line <= '9' && ptr->flag == 0)
		line++;
	resolution_next(ptr, line, maxheight);
}

void	convert_sky(t_param *ptr, int f, int s, int t)
{
	ptr->sky[0] = f;
	ptr->sky[1] = s;
	ptr->sky[2] = t;
	ptr->sky[3] = '0';
}

void	convert_floor(t_param *ptr, int f, int s, int t)
{
	ptr->floor[0] = f;
	ptr->floor[1] = s;
	ptr->floor[2] = t;
	ptr->floor[3] = '0';
}

void	ft_color(t_param *ptr, char *line, int type)
{
	int f;
	int s;
	int t;

	line++;
	f = ft_atoi(line);
	next_line(&line, ptr);
	if ((s = -1) == -1 && f >= 0)
		s = ft_atoi(line);
	if (f >= 0 && s >= 0)
		next_line(&line, ptr);
	if ((t = -1) == -1 && f >= 0 && s >= 0)
		t = ft_atoi(line);
	if (f >= 0 && s >= 0 && t >= 0 && type == 1)
		convert_floor(ptr, f, s, t);
	else if (f >= 0 && s >= 0 && t >= 0)
		convert_sky(ptr, f, s, t);
	if (f > 255 || s > 255 || t > 255 || f < 0 || s < 0 || t < 0)
		ptr->error = 4;
	if (verif_color(line, ptr) > 0 && verif_double(ptr) < 0)
		ptr->error = 0;
}
