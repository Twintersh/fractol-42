/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twinters <twinters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:21:10 by twinters          #+#    #+#             */
/*   Updated: 2023/02/15 19:19:09 by twinters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

static int	trans_flag(int i)
{
	i %= 5;
	if (i == 0)
		return (BLUE_TRANS);
	else if (i == 1)
		return (BLUE_TRANS);
	else if (i == 2)
		return (PINK_TRANS);
	else if (i == 3)
		return (WHITE);
	else if (i == 4)
		return (PINK_TRANS);
	return (0);
}

static int	lgbt_flag(int i)
{
	i %= 6;
	if (i == 0)
		return (PURPLE_LGBT);
	else if (i == 1)
		return (RED_LGBT);
	else if (i == 2)
		return (ORANGE_LGBT);
	else if (i == 3)
		return (YELLOW_LGBT);
	else if (i == 4)
		return (GREEN_LGBT);
	else if (i == 5)
		return (BLUE_LGBT);
	return (0);
}

int	other_colors(int color, int i)
{
	int mod;
	
	mod = color % 10;
	if (mod == 8)
		return (lgbt_flag(i));
	else if (mod == 9)
		return (trans_flag(i));
	return (0);
}