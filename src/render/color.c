/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:01:05 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/14 15:31:29 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.r * 255);
	g = (int)(color.g * 255);
	b = (int)(color.b * 255);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

t_color	apply_ambient(t_color obj_color, t_ambient ambient)
{
	t_color	result;

	result.r = ambient.ratio * ambient.color.r * obj_color.r;
	result.g = ambient.ratio * ambient.color.g * obj_color.g;
	result.b = ambient.ratio * ambient.color.b * obj_color.b;
	return (result);
}
