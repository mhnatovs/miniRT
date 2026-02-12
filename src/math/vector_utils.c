/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:42:09 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/12 13:48:22 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vector_length(t_vector a)
{
	float	length;

	length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (length);
}

t_vector	vec_normalize(t_vector a)
{
	float	length;

	length = vector_length(a);
	
}
