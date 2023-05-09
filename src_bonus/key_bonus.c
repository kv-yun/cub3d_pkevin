/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkevin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 15:07:47 by pkevin            #+#    #+#             */
/*   Updated: 2020/10/16 11:47:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"

int		ft_key_press(int keycode, t_param *ptr)
{
	if (keycode == W_KEY)
		ptr->w = 1;
	if (keycode == D_KEY)
		ptr->d = 1;
	if (keycode == A_KEY)
		ptr->a = 1;
	if (keycode == S_KEY)
		ptr->s = 1;
	if (keycode == RIGHT_KEY)
		ptr->right = 1;
	if (keycode == LEFT_KEY)
		ptr->left = 1;
	if (keycode == ESC_KEY)
		ptr->stop = 1;
	return (1);
}

int		ft_key_unpress(int keycode, t_param *ptr)
{
	if (keycode == W_KEY)
		ptr->w = 0;
	if (keycode == D_KEY)
		ptr->d = 0;
	if (keycode == A_KEY)
		ptr->a = 0;
	if (keycode == S_KEY)
		ptr->s = 0;
	if (keycode == RIGHT_KEY)
		ptr->right = 0;
	if (keycode == LEFT_KEY)
		ptr->left = 0;
	if (keycode == ESC_KEY)
		ptr->stop = 1;
	return (1);
}

void	ft_move_xy(t_param *ptr, int x, int y, int fl)
{
	if (fl == 0)
	{
		ptr->posx += ptr->dirx * 0.005 * x;
		ptr->posy += ptr->diry * 0.005 * y;
	}
	else
	{
		ptr->posy += ptr->dirx * 0.005 * y;
		ptr->posx += ptr->diry * 0.005 * x;
	}
}

void	ft_move_cam(t_param *ptr, float signe)
{
	float rot;

	rot = 0.005 * signe;
	ptr->olddirx = ptr->dirx;
	ptr->dirx = ptr->dirx * cos(rot) - ptr->diry * sin(rot);
	ptr->diry = ptr->olddirx * sin(rot) + ptr->diry * cos(rot);
	ptr->oldplanex = ptr->planex;
	ptr->planex = ptr->planex * cos(rot) - ptr->planey * sin(rot);
	ptr->planey = ptr->oldplanex * sin(rot) + ptr->planey * cos(rot);
}

int		ft_draw(t_param *ptr)
{
	if (ptr->w
	&& (ptr->map[(int)(ptr->posy + (ptr->diry * 0.005))]
	[(int)(ptr->posx + (ptr->dirx * 0.005))] != '1'))
		ft_move_xy(ptr, 1, 1, 0);
	if (ptr->s &&
	ptr->map[(int)(ptr->posy - (ptr->diry * 0.005))]
	[(int)(ptr->posx - (ptr->dirx * 0.005))] != '1')
		ft_move_xy(ptr, -1, -1, 0);
	if (ptr->d && (ptr->map[(int)(ptr->posy - (ptr->dirx * 0.005))]
	[(int)(ptr->posx + (ptr->diry * 0.005))] != '1'))
		ft_move_xy(ptr, 1, -1, 1);
	if (ptr->a &&
	(ptr->map[(int)(ptr->posy + (ptr->dirx * 0.005))]
	[(int)(ptr->posx - (ptr->diry * 0.005))] != '1'))
		ft_move_xy(ptr, -1, 1, 1);
	if (ptr->right)
		ft_move_cam(ptr, -1.0);
	if (ptr->left)
		ft_move_cam(ptr, 1.0);
	if (ptr->stop == 0)
		ft_image_create(ptr);
	else
		close_prog(ptr);
	return (1);
}
