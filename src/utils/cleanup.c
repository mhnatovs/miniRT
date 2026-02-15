/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:02:30 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/15 13:08:50 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_objects(t_list *objs)
{
	t_list	*current;
	t_list	*next;

	current = objs;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
}

void	free_scene(t_scene *scene)
{
	if (scene->objects)
		free_objects(scene->objects);
	scene->objects = NULL;
}
