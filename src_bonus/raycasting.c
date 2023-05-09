/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkevin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 11:41:22 by pkevin            #+#    #+#             */
/*   Updated: 2020/09/28 17:56:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_abs(float nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

void	ft_texture_choice(t_param *ptr)
{
	if (ptr->side == 0 && ptr->posx < ptr->mx)
		ptr->c_choice = 0;
	else if (ptr->side == 1 && ptr->posy < ptr->my)
		ptr->c_choice = 1;
	else if (ptr->side == 0 && ptr->posx > ptr->mx)
		ptr->c_choice = 2;
	else
		ptr->c_choice = 3;
}

void	ft_init_ray(t_param *ptr, int x)
{
	ptr->camerax = 2 * x / (float)(ptr->width) - 1;
	ptr->raydx = ptr->dirx + ptr->planex * ptr->camerax;
	ptr->raydy = ptr->diry + ptr->planey * ptr->camerax;
	ptr->mx = (int)(ptr->posx);
	ptr->my = (int)(ptr->posy);
	if (ptr->raydy == 0)
	{
		ptr->ddistx = 0;
		ptr->ddisty = 1;
	}
	else if (ptr->raydx == 0)
	{
		ptr->ddistx = 1;
		ptr->ddisty = 0;
	}
	else
	{
		ptr->ddistx = ft_abs(1 / ptr->raydx);
		ptr->ddisty = ft_abs(1 / ptr->raydy);
	}
	ptr->hit = 0;
	ptr->c_choice = 0;
}

void	ft_raydir_choice(t_param *ptr, int x)
{
	ft_init_ray(ptr, x);
	if (ptr->raydx < 0)
	{
		ptr->stepx = -1;
		ptr->sidedistx = (ptr->posx - ptr->mx) * ptr->ddistx;
	}
	else
	{
		ptr->stepx = 1;
		ptr->sidedistx = (ptr->mx + 1.0 - ptr->posx) * ptr->ddistx;
	}
	if (ptr->raydy < 0)
	{
		ptr->stepy = -1;
		ptr->sidedisty = (ptr->posy - ptr->my) * ptr->ddisty;
	}
	else
	{
		ptr->stepy = 1;
		ptr->sidedisty = (ptr->my + 1.0 - ptr->posy) * ptr->ddisty;
	}
}

int		ft_raycasting(t_param *ptr, int x)
{
	ft_raydir_choice(ptr, x);
	while (ptr->hit == 0)
	{
		if (ptr->sidedistx < ptr->sidedisty)
		{
			if (ray_distx(ptr, x) < 0)
				return (0);
		}
		else
		{
			if (ray_disty(ptr, x) < 0)
				return (0);
		}
		if (ptr->map[ptr->my][ptr->mx] == '1')
			ptr->hit = 1;
	}
	if (ptr->side == 0)
		ptr->pwdist = (ptr->mx - ptr->posx + (1 - ptr->stepx) / 2) / ptr->raydx;
	else
		ptr->pwdist = (ptr->my - ptr->posy + (1 - ptr->stepy) / 2) / ptr->raydy;
	ft_texture_choice(ptr);
	ptr->zbuffer[x] = ptr->pwdist;
	return (((int)ptr->height / ptr->pwdist));
}
