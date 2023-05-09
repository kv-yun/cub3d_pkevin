/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkevin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:22:52 by pkevin            #+#    #+#             */
/*   Updated: 2020/10/12 12:18:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_free_sprite(t_param *ptr)
{
	if (ptr->spriteorder)
	{
		free(ptr->spriteorder);
		ptr->spriteorder = NULL;
	}
	if (ptr->spritedistance)
	{
		free(ptr->spritedistance);
		ptr->spritedistance = NULL;
	}
	return (1);
}

int		ray_distx(t_param *ptr, int x)
{
	ptr->sidedistx += ptr->ddistx;
	ptr->mx += ptr->stepx;
	ptr->side = 0;
	if (ptr->mx < 0 || ptr->mx > (ft_strlen(ptr->map[0]) - 1))
	{
		ptr->pwdist = 0;
		ptr->zbuffer[x] = 0;
		return (-1);
	}
	return (1);
}

int		ray_disty(t_param *ptr, int x)
{
	ptr->sidedisty += ptr->ddisty;
	ptr->my += ptr->stepy;
	ptr->side = 1;
	if (ptr->my < 0 || ptr->my > (ptr->nb_line - 1))
	{
		ptr->pwdist = 0;
		ptr->zbuffer[x] = 0;
		return (-1);
	}
	return (1);
}

int		resolution_next(t_param *ptr, char *line, int maxheight)
{
	if (ptr->flag == 0)
	{
		ptr->height = ft_atoi(line);
		if (ptr->height <= 0)
		{
			ptr->height = 10;
			ptr->error = 3;
		}
		if (ptr->height >= maxheight)
			ptr->height = maxheight;
	}
	if (verif_double(ptr) < 0)
		ptr->error = 0;
	return (1);
}
