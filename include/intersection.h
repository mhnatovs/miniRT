/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:01:15 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/15 14:57:21 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "minirt.h"

float	intersect_object(t_ray ray, t_object *obj);
float	intersect_sphere(t_ray ray, t_sphere sphere);
float	intersect_plane(t_ray ray, t_plane plane);

#endif