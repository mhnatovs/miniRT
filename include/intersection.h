/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:01:15 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/21 09:48:09 by jiyawang         ###   ########.fr       */
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
void		hit_normal(t_object *obj, t_hit *hit);
t_vector	get_normal_sphere(t_vector hit_point, t_sphere sphere);
t_vector	get_normal_plane(t_plane plane);
t_vector	get_normal_cylinder(t_vector hit_point, t_cylinder c);
t_vector	project_perpend_axis(t_vector v, t_vector axis);

#endif