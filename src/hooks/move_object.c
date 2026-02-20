
#include "minirt.h"

static void	update_pos(t_object *o, t_vector move)
{
	if (o->type == OBJ_SPHERE)
		o->data.sphere.center = vector_add(o->data.sphere.center, move);
	else if (o->type == OBJ_PLANE)
		o->data.plane.point = vector_add(o->data.plane.point, move);
	else if (o->type == OBJ_CYLINDER)
		o->data.cylinder.base = vector_add(o->data.cylinder.base, move);
}

static t_vector	get_obj_pos(t_object *o)
{
	if (o->type == OBJ_SPHERE)
		return (o->data.sphere.center);
	if (o->type == OBJ_PLANE)
		return (o->data.plane.point);
	if (o->type == OBJ_CYLINDER)
		return (o->data.cylinder.base);
	return ((t_vector){0, 0, 0});
}

static bool	cylinder_plane_collision(t_cylinder cyl, t_vector next_pos,
		t_plane plane)
{
	float		dist0;
	float		dist1;
	float		offset;
	t_vector	top;
	float		dot_dn;

	top = vector_add(next_pos, vector_scale(cyl.dir, cyl.height));
	dist0 = vector_dot(vector_substract(next_pos, plane.point), plane.normal);
	dist1 = vector_dot(vector_substract(top, plane.point), plane.normal);
	dot_dn = vector_dot(cyl.dir, plane.normal);
	offset = cyl.radius * sqrt(1.0f - dot_dn * dot_dn);
	if ((dist0 - offset) * (dist0 + offset) <= 0)
		return (true);
	if ((dist1 - offset) * (dist1 + offset) <= 0)
		return (true);
	if (dist0 * dist1 <= 0)
		return (true);
	return (false);
}

static bool	is_colliding(t_context *ctx, t_object *o, t_vector next_pos)
{
	t_list		*node;
	t_object	*other;
	float		dist;

	node = ctx->scene.objects;
	while (node)
	{
		other = node->content;
		if (other != o && other->type == OBJ_PLANE)
		{
			if (o->type == OBJ_SPHERE)
			{
				dist = vector_dot(vector_substract(next_pos,
							other->data.plane.point), other->data.plane.normal);
				if (fabs(dist) < o->data.sphere.radius)
					return (true);
			}
			else if (o->type == OBJ_CYLINDER)
			{
				if (cylinder_plane_collision(o->data.cylinder, next_pos,
						other->data.plane))
					return (true);
			}
		}
		node = node->next;
	}
	return (false);
}

void	move_object_drag(t_context *ctx, double dx, double dy)
{
	t_viewport	vp;
	t_vector	move;
	t_vector	next_pos;
	float		dist;
	float		sx;
	float		sy;

	if (!ctx->selected_obj || ctx->selected_obj->type == OBJ_PLANE)
		return ;
	vp = init_viewport(ctx->scene.camera);
	dist = vector_length(vector_substract(get_obj_pos(ctx->selected_obj),
				ctx->scene.camera.pos));
	sx = (2.0f * vp.fov_scale * vp.aspect_ratio * dist) / WIDTH;
	sy = (2.0f * vp.fov_scale * dist) / HEIGHT;
	move = vector_add(vector_scale(vp.right, dx * sx),
			vector_scale(vp.up, -dy * sy));
	next_pos = vector_add(get_obj_pos(ctx->selected_obj), move);
	if (!is_colliding(ctx, ctx->selected_obj, next_pos))
	{
		update_pos(ctx->selected_obj, move);
		re_render(ctx);
	}
}

