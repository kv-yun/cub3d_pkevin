/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:19:08 by yun               #+#    #+#             */
/*   Updated: 2020/10/16 15:46:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_dispstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int		free_texture(t_param *ptr)
{
	if (ptr->no)
		free(ptr->no);
	if (ptr->so)
		free(ptr->so);
	if (ptr->ea)
		free(ptr->ea);
	if (ptr->we)
		free(ptr->we);
	if (ptr->ss)
		free(ptr->ss);
	ptr->no = NULL;
	ptr->so = NULL;
	ptr->ea = NULL;
	ptr->we = NULL;
	ptr->ss = NULL;
	if (ft_verif_parsing(ptr) < 0)
		ptr->error = 0;
	return (0);
}

int		ft_verif_texture(t_param *ptr)
{
	int	endian;
	int	size;

	size = 64;
	ptr->sline = 4 * ptr->width;
	endian = 0;
	if (!(ptr->img2 = mlx_xpm_file_to_image(ptr->mlx, ptr->no, &size, &size)))
		return (-1);
	if (!(ptr->img3 = mlx_xpm_file_to_image(ptr->mlx, ptr->so, &size, &size)))
		return (-1);
	if (!(ptr->img4 = mlx_xpm_file_to_image(ptr->mlx, ptr->ea, &size, &size)))
		return (-1);
	if (!(ptr->img5 = mlx_xpm_file_to_image(ptr->mlx, ptr->we, &size, &size)))
		return (-1);
	if (!(ptr->img6 = mlx_xpm_file_to_image(ptr->mlx, ptr->ss, &size, &size)))
		return (-1);
	ptr->draw2 = mlx_get_data_addr(ptr->img2, &ptr->bpp, &ptr->line, &endian);
	ptr->draw3 = mlx_get_data_addr(ptr->img3, &ptr->bpp, &ptr->line, &endian);
	ptr->draw4 = mlx_get_data_addr(ptr->img4, &ptr->bpp, &ptr->line, &endian);
	ptr->draw5 = mlx_get_data_addr(ptr->img5, &ptr->bpp, &ptr->line, &endian);
	ptr->draw6 = mlx_get_data_addr(ptr->img6, &ptr->bpp, &ptr->line, &endian);
	return (free_texture(ptr));
}

int		ft_verif_parsing(t_param *ptr)
{
	if (ptr->pe == 0 || ptr->pw == 0 || ptr->ps == 0 || ptr->pc == 0
	|| ptr->pf == 0 || ptr->pso == 0 || ptr->pn == 0 || ptr->pm == 0
	|| ptr->pr == 0)
	{
		ptr->flag = 1;
		return (-1);
	}
	ptr->flag = 0;
	return (1);
}

int		ft_disp_error(t_param *ptr)
{
	free_gnl(ptr);
	if (ptr->error == 0 && (verif_double(ptr)) > 0 && ft_verif_parsing(ptr) < 0)
		ft_dispstr("Error\nLack of information in .cub file\n");
	if (ptr->error == 0 && (verif_double(ptr) < 0))
		ft_dispstr("Error\nFake same information in the file\n");
	if (ptr->error == 1)
		ft_dispstr("Error\nTexture not found\n");
	if (ptr->error == 2)
		ft_dispstr("Error\nInvalid Map\n");
	if (ptr->error == 3)
		ft_dispstr("Error\nInvalid resolution\n");
	if (ptr->error == 4)
		ft_dispstr("Error\nInvalid color\n");
	if (ptr->error == 5)
		ft_dispstr("Error\nError during creation map, please restart game\n");
	if (ptr->error == 6)
		ft_dispstr("Error\nWrong line in .cub file\n");
	if (ptr->error == 0 && ptr->flag == 0)
		return (0);
	free_texture(ptr);
	if (ptr->pm == 1)
		close_prog(ptr);
	free(ptr->mlx);
	exit(0);
	return (-1);
}
