#ifndef PARSER_H
# define PARSER_H

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}				t_color;

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
}				t_ambient;

typedef struct s_scene
{
	t_ambient	ambient;
}				t_scene;

t_color	parse_color(char *str);
void	ft_free_tab(char **tab);
float	ft_atof(const char *str);
int		init_parser(char *file, t_scene *scene);

#endif