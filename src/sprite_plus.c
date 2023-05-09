/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 14:03:58 by yun               #+#    #+#             */
/*   Updated: 2020/09/28 17:32:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_sprite_x(int locate, t_param *ptr)
{
	int x;
	int y;

	y = 0;
	while (y < ptr->nb_line)
	{
		x = 0;
		while (ptr->map[y][x])
		{
			if (locate > 0 && ptr->map[y][x] == '2')
				locate--;
			else if (ptr->map[y][x] == '2')
				return (x);
			x++;
		}
		y++;
	}
	return (0);
}

int		ft_sprite_y(int locate, t_param *ptr)
{
	int x;
	int y;

	y = 0;
	while (y < ptr->nb_line)
	{
		x = 0;
		while (ptr->map[y][x])
		{
			if (locate > 0 && ptr->map[y][x] == '2')
				locate--;
			else if (ptr->map[y][x] == '2')
				return (y);
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_sprite_order(t_param *ptr)
{
	int		i;
	int		swap;
	float	swap2;

	i = 0;
	while (i < ptr->nb_sprite)
	{
		if ((i + 1) < ptr->nb_sprite &&
		ptr->spritedistance[i] < ptr->spritedistance[i + 1])
		{
			swap = ptr->spriteorder[i];
			ptr->spriteorder[i] = ptr->spriteorder[i + 1];
			ptr->spriteorder[i + 1] = swap;
			swap2 = ptr->spritedistance[i];
			ptr->spritedistance[i] = ptr->spritedistance[i + 1];
			ptr->spritedistance[i + 1] = swap2;
			i = 0;
		}
		i++;
	}
}

int		ft_pixel_black(t_param *ptr)
{
	if (ptr->draw6[0 + 4 * ptr->texx + (4 * 64 * ptr->texy)] == 0
	&& ptr->draw6[1 + 4 * ptr->texx + (4 * 64 * ptr->texy)] == 0
	&& ptr->draw6[2 + 4 * ptr->texx + (4 * 64 * ptr->texy)] == 0)
		return (-1);
	return (0);
}

int		ft_abs_int(int nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}
