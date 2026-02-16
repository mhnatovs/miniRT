/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:42:09 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/16 15:44:20 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vector_length(t_vector a)
{
	float	length;

	length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (length);
}

t_vector	vector_normalize(t_vector a)
{
	t_vector	res;
	float		length;

	length = vector_length(a);
	if (length < 0.0001)
		return (a);
	res.x = a.x / length;
	res.y = a.y / length;
	res.z = a.z / length;
	return (res);
}
