/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yun <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 12:41:41 by yun               #+#    #+#             */
/*   Updated: 2020/10/16 11:58:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"

void	ft_init_next(t_param *ptr, int ac, char **av)
{
	ptr->width = 10;
	ptr->height = 10;
	ptr->pr = 0;
	ptr->pf = 0;
	ptr->pc = 0;
	ptr->pe = 0;
	ptr->pw = 0;
	ptr->nb_line = 1;
	ptr->bpp = 32;
	ptr->size = 64;
	ptr->line = 4 * 64;
	ptr->img = NULL;
	ptr->img3 = NULL;
	ptr->img4 = NULL;
	ptr->img5 = NULL;
	ptr->img6 = NULL;
	ptr->draw = NULL;
	ptr->map = NULL;
	ptr->verif_map = NULL;
	ptr->temp_map = NULL;
	if (ac < 2 || verif_arg(av[1]) < 0)
	{
		write(1, "Error\nWrong argument\n", 21);
		exit(0);
	}
}

void	ft_init_var(t_param *ptr, int ac, char **av)
{
	ptr->img2 = 0;
	ptr->posx = 0;
	ptr->posy = 0;
	ptr->w = 0;
	ptr->s = 0;
	ptr->right = 0;
	ptr->left = 0;
	ptr->d = 0;
	ptr->a = 0;
	ptr->stop = 0;
	ptr->error = 0;
	ptr->pm = 0;
	ptr->pn = 0;
	ptr->ps = 0;
	ptr->pso = 0;
	ptr->no = NULL;
	ptr->so = NULL;
	ptr->ea = NULL;
	ptr->we = NULL;
	ptr->ss = NULL;
	ptr->win = NULL;
	ft_init_next(ptr, ac, av);
}

int		ft_verif_av(char *av, int ac, t_param *ptr)
{
	if (ft_strlen(av) != 6)
	{
		write(1, "Error\nWrong argument\n", 21);
		close_prog(ptr);
	}
	if (av[0] != '-' || av[1] != '-' || av[2] != 's'
	|| av[3] != 'a' || av[4] != 'v' || av[5] != 'e')
	{
		write(1, "Error\nWrong argument\n", 21);
		close_prog(ptr);
	}
	if (ac > 3)
	{
		write(1, "Error\nWrong argument\n", 21);
		close_prog(ptr);
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_param ptr;

	if (!(ptr.mlx = mlx_init()))
		return (-1);
	ft_init_var(&ptr, ac, av);
	ptr.fd = open(av[1], O_RDONLY);
	if ((ft_parsing(&ptr)) < 0)
		return (-1);
	if (ac == 2 &&
	!(ptr.win = mlx_new_window(ptr.mlx, ptr.width, ptr.height, "cub3d")))
		return (-1);
	if (ac >= 3)
	{
		if ((ft_verif_av(av[2], ac, &ptr)) < 0)
			return (0);
		if (ft_screen(&ptr) < 0)
			write(1, "Error\nFile descriptor failed\n", 29);
		ft_leave(&ptr);
	}
	mlx_hook(ptr.win, 2, (1L << 0), ft_key_press, &ptr);
	mlx_hook(ptr.win, 3, (1L << 1), ft_key_unpress, &ptr);
	mlx_hook(ptr.win, 33, (1L << 2), close_prog, &ptr);
	mlx_loop_hook(ptr.mlx, ft_draw, &ptr);
	mlx_loop(ptr.mlx);
	return (0);
}
