/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:04:33 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/10 13:57:35 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_ambient(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || tokens[3])
		error_exit("Error: Invalid Ambient Light format");
	scene->ambient.ratio = ft_atof(tokens[1]);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		error_exit("Error: Ambient Light ratio must be in range [0.0, 1.0]");
	scene->ambient.color = parse_color(tokens[2]);
}

static void	parse_camera(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		error_exit("Error: Invalid Camera format");
	scene->camera.pos = parse_vector(tokens[1]);
	scene->camera.dir = parse_vector(tokens[2]);
	if (scene->camera.dir.x < -1.0 || scene->camera.dir.x > 1.0
		|| scene->camera.dir.y < -1.0 || scene->camera.dir.y > 1.0
		|| scene->camera.dir.z < -1.0 || scene->camera.dir.z > 1.0)
		error_exit("Error: Camera direction vector must be normalized");
	scene->camera.fov = ft_atoi(tokens[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		error_exit("Error: Camera FOV must be in range [0, 180]");
}

static void	parse_light(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		error_exit("Error: Invalid Light format");
	scene->light.pos = parse_vector(tokens[1]);
	scene->light.ratio = ft_atof(tokens[2]);
	if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
		error_exit("Error: Light ratio must be in range [0.0, 1.0]");
	scene->light.color = parse_color(tokens[3]);
}

static void	parse_line(char *line, t_scene *scene)
{
	char	**tokens;

	if (line[0] == '\n' || line[0] == '\0' || line[0] == '#')
		return ;
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		ft_free_tab(tokens);
		return ;
	}
	if (ft_strcmp(tokens[0], "A") == 0)
		parse_ambient(tokens, scene);
	else if (ft_strcmp(tokens[0], "C") == 0)
		parse_camera(tokens, scene);
	else if (ft_strcmp(tokens[0], "L") == 0)
		parse_light(tokens, scene);
	else if (ft_strcmp(tokens[0], "sp") == 0)
		parse_sphere(tokens, scene);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		parse_plane(tokens, scene);
	else if (ft_strcmp(tokens[0], "cy") == 0)
		parse_cylinder(tokens, scene);
	else
		error_exit("Error: Unknown identifier in scene file");
	ft_free_tab(tokens);
}

int	init_parser(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	char	*ext;

	ext = ft_strrchr(file, '.');
	if (!ext || ft_strcmp(ext, ".rt") != 0)
		error_exit("Error: Invalid file extension");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Could not open file");
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
