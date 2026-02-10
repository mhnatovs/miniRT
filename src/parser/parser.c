/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:04:33 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/10 12:04:37 by jiyawang         ###   ########.fr       */
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
