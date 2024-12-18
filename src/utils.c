#include "../Include/cub3D.h"

char *ft_joinfree(char *s1, char *s2)
{
	char *temp;
	if(!s1 && s2)
		return(ft_strdup(s2));
	temp = ft_strjoin(s1,s2);
	if (s1)
		free(s1);
	return(temp);
}

int	skip_spaces(char *str)
{
	int i;

	i = 1;
	while(str[i] && str[i] == ' ')
		i++;
	return(i);
}
int count_comma(char *str)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while(str[i] && str[i] != '\n')
	{
		if (str[i] == ',')
			c++;
		i++;
	}
	return(c);
}

void free_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
int rgb(int r,int g,int b, int a)
{
	return(r << 24 | g << 16 | b << 8 | a);
}