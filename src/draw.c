/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twinters <twinters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:56:21 by twinters          #+#    #+#             */
/*   Updated: 2022/07/06 20:26:04 by twinters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	fractal(t_mlx mlx)
{
	long double	x;
	long double	y;
	long double	x_tmp;
	long double	y_tmp;
	int			i;

	i = -1;
	x = get_px_coordinates(mlx.xx, mlx.zoom, mlx.offset_x);
	y = get_px_coordinates(mlx.yy, mlx.zoom, mlx.offset_y);
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
	mlx.c.x = get_px_coordinates(mlx.xx, mlx.zoom, mlx.offset_x);
	mlx.c.y = get_px_coordinates(mlx.yy, mlx.zoom, mlx.offset_y);
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

t_cvalues	set_c(float x, float y)
{
	t_cvalues	c;

	c.x = x;
	c.y = y;
	return (c);
}

t_cvalues	which_fractal(char *arg)
{
	t_cvalues	c;

	if (!ft_strncmp(arg, "julia1", 7))
		c = set_c(-0.75, 0);
	else if (!ft_strncmp(arg, "julia2", 7))
		c = set_c(0, 1.0);
	else if (!ft_strncmp(arg, "julia3", 7))
		c = set_c(-0.12, 0.75);
	else if (!ft_strncmp(arg, "julia4", 11))
		c = set_c(-0.39, -0.59);
	else if (!ft_strncmp(arg, "mandelbrot_set", 14))
		c = set_c(10, 0);
	else if (!ft_strncmp(arg, "-h", 2))
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
