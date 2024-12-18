#include "../Include/cub3D.h"

int *valid_numbers(char *str,t_cub *game)
{
	int i;
	int *arr;
	char **split_spaces;
	char **split_commas;

	i = 0;
	arr = (int *)malloc(sizeof (int ) * 3);
	if (!arr)
		error_msg("Error allocated int\n",game);
	split_spaces = ft_split(str,' ');
	split_commas = ft_split(split_spaces[1],',');
	while(split_commas[i])
	{
		if (ft_atoi(split_commas[i]) > 255
			|| ft_atoi(split_commas[i]) < 0)
		{
			free_matrix(split_commas);
			free_matrix(split_spaces);
			error_msg("No valid number\n",game);
		}
		arr[i] = ft_atoi(split_commas[i]);
		i++;
	}
	free_matrix(split_commas);
	free_matrix(split_spaces);
	return(arr);
}

void valid_info(char *str,t_cub *game)
{
	int i;

	if(count_comma(str) != 2)
		error_msg("No valid data ceiling or floor\n",game);
	i = skip_spaces(str);
	while(str[i] && str[i] != '\n')
	{
		if(str[i] <= '9' && str[i] >= '0')
			i++;
		else if(str[i] == ',' && (str[i - 1] <= '9' && str[i - 1] >= '0'
			&& (str[i + 1] && str[i + 1] <= '9' && str[i + 1] >= '0')))
			i++;
		else
			error_msg("Character no valid\n",game);
	}
}
