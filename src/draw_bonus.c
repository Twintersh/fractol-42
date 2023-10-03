/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twinters <twinters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:56:21 by twinters          #+#    #+#             */
/*   Updated: 2022/07/05 18:55:16 by twinters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol_bonus.h"

int	fractal(t_mlx mlx)
{
	long double	x;
	long double	y;
	long double	x_tmp;
	long double	y_tmp;
	int			i;

	i = -1;
	x = px_coo(mlx.xx, mlx.zoom, mlx.offset.x);
	y = px_coo(mlx.yy, mlx.zoom, mlx.offset.y);
	while (++i < mlx.iteri && x * x + y * y < 4)
	{
		x_tmp = x;
		y_tmp = y;
		x = x_tmp * x_tmp - y_tmp * y_tmp + mlx.c.x;
		y = 2 * x_tmp * y_tmp + mlx.c.y;
	}
	if (i == mlx.iteri)
		return (BLACK);
	return (fractal_color(mlx.color, i));
}

int	mandelbrot_set(t_mlx mlx)
{
	long double	x;
	long double	y;
	long double	x_tmp;
	int			i;

	i = -1;
	x = 0;
	y = 0;
	mlx.c.x = px_coo(mlx.xx, mlx.zoom, mlx.offset.x);
	mlx.c.y = px_coo(mlx.yy, mlx.zoom, mlx.offset.y);
	while (++i < mlx.iteri && x * x + y * y < 4)
	{
		x_tmp = x;
		x = x * x - y * y + mlx.c.x;
		y = 2 * x_tmp * y + mlx.c.y;
	}
	if (i == mlx.iteri)
		return (BLACK);
	return (fractal_color(mlx.color, i));
}

void	draw_fractal(t_mlx mlx)
{
	int		color;
	t_data	img;

	img.img = mlx_new_image(mlx.ptr, mlx.x, mlx.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	mlx.xx = 0;
	while (mlx.xx < mlx.x)
	{
		mlx.yy = 0;
		while (mlx.yy < mlx.y)
		{
			if (mlx.c.x == 10)
				color = mandelbrot_set(mlx);
			else if (mlx.c.y == 10)
				color = burning_ship(mlx);
			else
				color = fractal(mlx);
			my_mlx_pixel_put(&img, mlx.xx, mlx.yy, color);
			mlx.yy++;
		}
		mlx.xx++;
	}
	mlx_put_image_to_window(mlx.ptr, mlx.win, img.img, 0, 0);
	mlx_destroy_image(mlx.ptr, img.img);
}

t_cvalues	which_fractal(char *arg)
{
	t_cvalues	c;

	if (!strncmp(arg, "julia1", 7))
		c = set_c(-0.75, 0);
	else if (!strncmp(arg, "julia2", 7))
		c = set_c(0, 1.0);
	else if (!strncmp(arg, "julia3", 7))
		c = set_c(-0.12, 0.75);
	else if (!ft_strncmp(arg, "julia4", 7))
		c = set_c(-0.39, -0.59);
	else if (!strncmp(arg, "mandelbrot_set", 15))
		c = set_c(10, 0);
	else if (!strncmp(arg, "burning_ship", 13))
		c = set_c(0, 10);
	else if (!strncmp(arg, "-h", 3))
	{
		print_errors(HELP);
		exit(EXIT_SUCCESS);
	}
	else
	{
		print_errors(INVALID_ARG);
		exit(EXIT_SUCCESS);
	}
	return (c);
}

int	burning_ship(t_mlx mlx)
{
	int			i;
	long double	x;
	long double	y;
	long double	x_tmp;
	long double	abs;

	x = px_coo(mlx.xx, mlx.zoom, mlx.offset.x);
	y = px_coo(mlx.yy, mlx.zoom, mlx.offset.y);
	mlx.offset.x = x;
	mlx.offset.y = y;
	i = -1;
	while (++i < mlx.iteri && x * x + y * y < 4)
	{
		x_tmp = x * x - y * y + mlx.offset.x;
		abs = 2 * x * y;
		if (abs < 0)
			abs *= -1;
		y = abs + mlx.offset.y;
		x = x_tmp;
	}
	if (i == mlx.iteri)
		return (BLACK);
	return (fractal_color(mlx.color, i));
}
