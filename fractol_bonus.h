/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twinters <twinters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:13:31 by twinters          #+#    #+#             */
/*   Updated: 2022/06/28 23:06:25 by twinters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

# include "libft/libft.h"
# include "mlx_linux/mlx.h"
# include "mlx_linux/mlx_int.h"
# include <math.h>

// ERRORS ID

# define HELP 421
# define INVALID_ARG 422
# define INVALID_ARG_NUM 423

//	CONFIG

# define WIN_NAME "fractol_bonus"

//	KEYS

# define K_LEFT 65361
# define K_UP 65362
# define K_RIGHT 65363
# define K_DOWN 65364
# define K_ESC 65307
# define K_SPACE 32
# define K_A 97
# define EVA 6
# define K_S 115
# define K_R 114
# define K_G 103
# define K_B 98
# define K_W 119

//	COLORS

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_cvalues
{
	long double	y;
	long double	x;
}	t_cvalues;

typedef struct s_mlx
{
	void				*ptr;
	void				*win;
	int					x;
	int					y;
	int					yy;
	int					xx;
	int					iteri;
	int					color;
	int					opti;
	float				zoom;
	struct s_cvalues	offset;
	struct s_data		*img;
	struct s_cvalues	c;
}	t_mlx;

//	draw_bonus.c

int				fractal(t_mlx mlx);
int				mandelbrot_set(t_mlx mlx);
void			draw_fractal(t_mlx mlx);
t_cvalues		which_fractal(char *arg);
int				burning_ship(t_mlx mlx);

//	fractol_bonus.c

int				ft_close(t_mlx *mlx);
int				key_hook(int keycode, t_mlx *mlx);
int				trgb(int t, int r, int g, int b);
int				fractal_color(int color, int i);
t_cvalues		set_c(float x, float y);

// hooks_bonus.c

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				mouse_hook(int button, int x, int y, t_mlx *mlx);
void			print_errors(int index);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
long double		px_coo(int px, float zoom, long double offset);

#endif
