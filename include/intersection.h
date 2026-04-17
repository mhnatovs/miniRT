/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:03:31 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/04/14 12:17:14 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H
# include "minirt.h"

float		intersect_object(t_ray ray, t_object *obj);
float		intersect_sphere(t_ray ray, t_sphere sphere);
float		intersect_plane(t_ray ray, t_plane plane);
float		intersect_cyl_side(t_ray ray, t_cylinder c);
float		intersect_cylinder(t_ray ray, t_cylinder c);
void		hit_normal(t_object *obj, t_hit *hit, t_ray ray);
t_vector	get_normal_sphere(t_vector hit_point, t_sphere sphere);
t_vector	get_normal_plane(t_plane plane, t_ray ray);
t_vector	get_normal_cylinder(t_vector hit_point, t_cylinder c);
t_vector	project_perpend_axis(t_vector v, t_vector axis);

#endif