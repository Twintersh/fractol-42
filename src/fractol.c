/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twinters <twinters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:11:48 by twinters          #+#    #+#             */
/*   Updated: 2022/06/27 16:44:14 by twinters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	main(int argc, char **argv)
{
	t_mlx		mlx;

	if (argc != 2)
		return (print_errors(INVALID_ARG_NUM), 0);
	mlx.c = which_fractal(argv[1]);
	mlx.ptr = mlx_init();
	mlx.x = 1000;
	mlx.y = 1000;
	mlx.iteri = 50;
	mlx.zoom = 1;
	mlx.offset_x = 0;
	mlx.offset_y = 0;
	mlx.color = 0;
	mlx.win = mlx_new_window(mlx.ptr, mlx.x, mlx.y, WIN_NAME);
	draw_fractal(mlx);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_hook(mlx.win, 17, 0, ft_close, &mlx);
	mlx_hook(mlx.win, 4, (1L << 2), mouse_hook, &mlx);
	mlx_loop(mlx.ptr);
}

int	fractal_color(int color, int i)
{
	int	mod;

	mod = color % 7;
	if (mod == 0)
		return (trgb(0, i * 10, i * 2, i * 5));
	else if (mod == 1)
		return (trgb(0, i * 10, i * 10, i * 10));
	else if (mod == 2)
		return (trgb(0, i * 10, 0, 0));
	else if (mod == 3)
		return (trgb(0, 0, i * 10, 0));
	else if (mod == 4)
		return (trgb(0, 0, 0, i * 10));
	else if (mod == 5)
		return (trgb(0, i * 74, i * 156, i * 82));
	else if (mod == EVA)
		return (trgb(0, i * 5, i * 28, i * 35));
	else
		return (0);
}

int	ft_close(t_mlx *mlx)
{
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(EXIT_SUCCESS);
}

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
