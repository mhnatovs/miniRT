/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_colliding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 10:56:10 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/02 14:41:37 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define EPSILON 0.01f

// returns signed penetration depth: negative when
// intersecting, positive when separated
static float	cylinder_plane_depth(t_cylinder cyl,
		t_vector pos, t_plane plane)
{
	float		dist0;
	float		dist1;
	float		offset;
	t_vector	top;
	float		dot_dn;

	top = vector_add(pos, vector_scale(cyl.dir, cyl.height));
	dist0 = vector_dot(vector_substract(pos, plane.point), plane.normal);
	dist1 = vector_dot(vector_substract(top, plane.point), plane.normal);
	dot_dn = vector_dot(cyl.dir, plane.normal);
	offset = cyl.radius * sqrt(1.0f - dot_dn * dot_dn);
	return (fminf(dist0, dist1) - offset);
}

static bool	cylinder_plane_collision(t_cylinder cyl, t_vector next_pos,
		t_plane plane)
{
	return (cylinder_plane_depth(cyl, next_pos, plane) < -EPSILON);
}

static bool	check_collision(t_object *o, t_object *other, t_vector next_pos)
{
	float	dist;
	float	obj_dist;

	if (o->type == OBJ_SPHERE)
	{
		if (other->type == OBJ_PLANE)
		{
			dist = vector_dot(vector_substract(next_pos, other->data.plane.point),
					other->data.plane.normal);
			if (dist < -o->data.sphere.radius - EPSILON)
				return (true);
		}
		else if (other->type == OBJ_SPHERE)
		{
			obj_dist = vector_length(vector_substract(next_pos,
					other->data.sphere.center));
			if (obj_dist < o->data.sphere.radius + other->data.sphere.radius - EPSILON)
				return (true);
		}
		else if (other->type == OBJ_CYLINDER)
		{
			obj_dist = vector_length(vector_substract(next_pos,
					other->data.cylinder.base));
			if (obj_dist < o->data.sphere.radius + other->data.cylinder.radius - EPSILON)
				return (true);
		}
	}
	else if (o->type == OBJ_CYLINDER)
	{
		if (other->type == OBJ_PLANE)
		{
			if (cylinder_plane_collision(o->data.cylinder, next_pos,
					other->data.plane))
				return (true);
		}
		else if (other->type == OBJ_SPHERE)
		{
			obj_dist = vector_length(vector_substract(next_pos,
					other->data.sphere.center));
			if (obj_dist < o->data.cylinder.radius + other->data.sphere.radius - EPSILON)
				return (true);
		}
		else if (other->type == OBJ_CYLINDER)
		{
			obj_dist = vector_length(vector_substract(next_pos,
					other->data.cylinder.base));
			if (obj_dist < o->data.cylinder.radius + other->data.cylinder.radius - EPSILON)
				return (true);
		}
	}
	return (false);
}

bool	is_colliding(t_context *ctx, t_object *o, t_vector next_pos)
{
	t_list		*node;
	t_object	*other;
	t_vector	current_pos;
	float		curr_depth;
	float		next_depth;

	current_pos = get_obj_pos(o);
	node = ctx->scene.objects;
	while (node)
	{
		other = node->content;
		if (other != o && other->type == OBJ_PLANE)
		{
			if (o->type == OBJ_SPHERE)
			{
				curr_depth = vector_dot(vector_substract(current_pos,
					other->data.plane.point), other->data.plane.normal);
				next_depth = vector_dot(vector_substract(next_pos,
					other->data.plane.point), other->data.plane.normal);
				if (next_depth < curr_depth && next_depth < -o->data.sphere.radius - EPSILON)
					return (true);
			}
			else if (o->type == OBJ_CYLINDER)
			{
				curr_depth = cylinder_plane_depth(o->data.cylinder, current_pos,
					other->data.plane);
				next_depth = cylinder_plane_depth(o->data.cylinder, next_pos,
					other->data.plane);
				if (next_depth < curr_depth - EPSILON)
					return (true);
			}
		}
		else if (other != o && other->type != OBJ_PLANE)
		{
			if (check_collision(o, other, next_pos))
				return (true);
		}
		node = node->next;
	}
	return (false);
}


// static bool	sphere_hits_plane(t_object *sphere, t_object *plane,
// 	t_vector current_pos, t_vector next_pos)
// {
// 	float	curr_depth;
// 	float	next_depth;

// 	curr_depth = vector_dot(
// 		vector_substract(current_pos, plane->data.plane.point),
// 		plane->data.plane.normal);

// 	next_depth = vector_dot(
// 		vector_substract(next_pos, plane->data.plane.point),
// 		plane->data.plane.normal);

// 	if (next_depth < curr_depth
// 		&& next_depth < -sphere->data.sphere.radius - EPSILON)
// 		return (true);
// 	return (false);
// }
// static bool	cylinder_hits_plane(t_object *cyl, t_object *plane,
// 	t_vector current_pos, t_vector next_pos)
// {
// 	float	curr_depth;
// 	float	next_depth;

// 	curr_depth = cylinder_plane_depth(cyl->data.cylinder,
// 		current_pos, plane->data.plane);
// 	next_depth = cylinder_plane_depth(cyl->data.cylinder,
// 		next_pos, plane->data.plane);

// 	if (next_depth < curr_depth - EPSILON)
// 		return (true);
// 	return (false);
// }
// static bool	check_plane_collision(t_object *o, t_object *plane,
// 	t_vector current_pos, t_vector next_pos)
// {
// 	if (o->type == OBJ_SPHERE)
// 		return (sphere_hits_plane(o, plane, current_pos, next_pos));
// 	else if (o->type == OBJ_CYLINDER)
// 		return (cylinder_hits_plane(o, plane, current_pos, next_pos));
// 	return (false);
// }
// static bool	check_object_collision(t_object *o, t_object *other,
// 	t_vector next_pos)
// {
// 	if (other->type != OBJ_PLANE)
// 		return (check_collision(o, other, next_pos));
// 	return (false);
// }
// bool	is_colliding(t_context *ctx, t_object *o, t_vector next_pos)
// {
// 	t_list		*node;
// 	t_object	*other;
// 	t_vector	current_pos;

// 	current_pos = get_obj_pos(o);
// 	node = ctx->scene.objects;

// 	while (node)
// 	{
// 		other = node->content;

// 		if (other != o && other->type == OBJ_PLANE)
// 		{
// 			if (check_plane_collision(o, other, current_pos, next_pos))
// 				return (true);
// 		}
// 		else if (other != o)
// 		{
// 			if (check_object_collision(o, other, next_pos))
// 				return (true);
// 		}

// 		node = node->next;
// 	}
// 	return (false);
// }