/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twinters <twinters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:58:36 by twinters          #+#    #+#             */
/*   Updated: 2022/07/05 18:09:26 by twinters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	if (button == 4)
		mlx->zoom /= 1.25;
	if (button == 5 && mlx->zoom < 2)
		mlx->zoom *= 1.25;
	if (button == 1)
	{
		mlx->offset_x = get_px_coordinates(x, mlx->zoom, mlx->offset_x);
		mlx->offset_y = get_px_coordinates(y, mlx->zoom, mlx->offset_y);
	}
	if (button == 3 && mlx->c.x != 10)
	{
		mlx->c.x = get_px_coordinates(x, 1, mlx->offset_x);
		mlx->c.y = get_px_coordinates(y, 1, mlx->offset_y);
	}
	draw_fractal(*mlx);
	return (0);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == K_ESC)
		ft_close(mlx);
	if (keycode == 'c')
		mlx->color++;
	if (keycode == 'r')
	{
		mlx->zoom = 1;
		mlx->offset_y = 0;
		mlx->offset_x = 0;
	}
	if (keycode == 'p' || keycode == 'o')
	{
		if (keycode == 'p')
			mlx->iteri += 10;
		else if (mlx->iteri > 0)
			mlx->iteri -= 10;
	}
	draw_fractal(*mlx);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	print_errors(int index)
{
	if (index == HELP)
	{
		ft_printf("IMPLEMENTED FRACTALS :\n-mandelbrot_set\n-julia(1 - 4)");
		ft_printf("\n\nCOMMANDS :\nYou can use left click to center");
		ft_printf(" the image and the scroll up/down to zoom/dezoom.\nThe keys");
		ft_printf(" O and P allows you to increase/decrease iterations");
		ft_printf(" in the fractal\nThe key C changes the color pallet.\n");
		ft_printf("The key R resets the zoom and the offset\n");
	}
	if (index == INVALID_ARG)
		ft_printf("ERROR : INVALID ARGUMENT (-h to help)\n");
	if (index == INVALID_ARG_NUM)
		ft_printf("ERROR : INVALID NUMBER OF ARGUMENTS (-h to help)\n");
}

long double	get_px_coordinates(int px, float zoom, long double offset)
{
	long double	px_y;

	px_y = (((4 * (float)px) - 2000)) / 1000;
	px_y *= (long double)zoom;
	px_y += offset;
	return (px_y);
}
