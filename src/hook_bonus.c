/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twinters <twinters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 22:28:18 by twinters          #+#    #+#             */
/*   Updated: 2022/07/08 17:42:59 by twinters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol_bonus.h"

int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	t_cvalues	bzoom;

	if (button == 4 || (button == 5 && mlx->zoom < 2))
	{
		bzoom.x = px_coo(x, mlx->zoom, mlx->offset.x);
		bzoom.y = px_coo(y, mlx->zoom, mlx->offset.y);
		if (button == 4)
			mlx->zoom /= 1.25;
		else
			mlx->zoom *= 1.25;
		mlx->offset.x += bzoom.x - px_coo(x, mlx->zoom, mlx->offset.x);
		mlx->offset.y += bzoom.y - px_coo(y, mlx->zoom, mlx->offset.y);
	}
	if (button == 1)
	{
		mlx->offset.x = px_coo(x, mlx->zoom, mlx->offset.x);
		mlx->offset.y = px_coo(y, mlx->zoom, mlx->offset.y);
	}
	if (button == 3 && mlx->c.x != 10 && mlx->c.y != 10)
	{
		mlx->c.x = px_coo(x, 1, mlx->offset.x);
		mlx->c.y = px_coo(y, 1, mlx->offset.y);
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
	if (keycode == K_A)
		mlx->zoom /= 1.25;
	if (keycode == K_S && mlx->zoom < 2)
		mlx->zoom *= 1.25;
	if (keycode == 'r')
	{
		mlx->zoom = 1;
		mlx->offset.y = 0;
		mlx->offset.x = 0;
	}
	if (keycode == K_RIGHT || keycode == K_LEFT)
		mlx->offset.x += ((float)keycode - K_UP) * mlx->zoom / 10;
	if (keycode == K_UP || keycode == K_DOWN)
		mlx->offset.y += ((float)keycode - K_RIGHT) * mlx->zoom / 10;
	if (keycode == 'p')
		mlx->iteri += 10;
	else if (keycode == 'o' && mlx->iteri > 0)
		mlx->iteri -= 10;
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
		ft_printf("IMPLEMENTED FRACTALS (BONUS) :\n-mandelbrot_set\n");
		ft_printf("-julia(1 - 4)\n-burning_ship");
		ft_printf("\n\nCOMMANDS :\nYou can use the arrows to change the offset\n");
		ft_printf("You can use left click to center");
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

long double	px_coo(int px, float zoom, long double offset)
{
	long double	px_y;

	px_y = (4 * (float)px - 2 * WIN_SIZE) / WIN_SIZE;
	px_y *= (long double)zoom;
	px_y += offset;
	return (px_y);
}
