#include "minirt.h"

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

float	ft_atof(const char *str)
{
	float	res;
	float	decimal;
	int		sign;
	int		i;

	res = 0.0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
	{
		decimal = 0.1;
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			res += (str[i++] - '0') * decimal;
			decimal /= 10.0;
		}
	}
	return (res * sign);
}

t_color	parse_color(char *str)
{
	char	**rgb;
	t_color	color;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		error_exit("Error: Invalid color format (R,G,B)");
	color.r = ft_atoi(rgb[0]);
	color.g = ft_atoi(rgb[1]);
	color.b = ft_atoi(rgb[2]);
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
		error_exit("Error: Color values must be in range [0, 255]");
	color.r = (float)color.r / 255.0;
	color.g = (float)color.g / 255.0;
	color.b = (float)color.b / 255.0;	
	ft_free_tab(rgb);
	return (color);
}
