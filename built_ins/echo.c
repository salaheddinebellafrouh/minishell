/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:58:58 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/17 15:24:54 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"






int n_flag(char *ptr, int *index)
{
	int i;

	i = 0;
	if (!ptr)
	return (0);
	if (ft_strlen (ptr) > 0 && ptr[i] == '-' && ptr[i + 1] == 'n')
	{
		while (ptr[i + 1] == 'n')
			i++;
			if (ptr[i + 1] == '\0')
			{
				(*index)++;
				return (1);
			}
			else 
				return (0);
	}
	else
		return (0);
}


int n_flag_ultra(char **ptr, int *index)
{
	int i;
	int flag;
	int yes;

	i = 0;
	yes = 0;
	flag = n_flag(ptr[*index], index);
	while (flag)
	{
		yes = 1;
		flag = n_flag(ptr[*index], index);
	}
	return (yes);
}


void	my_echo(t_builtins *builts)
{
	int i;
	int n;
	int flag_in;

	i = 0;
	flag_in = 0;
	n = 0;
	while (builts->args_arr[++i])
	{
		if (n == 0)
		{
			flag_in = n_flag_ultra(builts->args_arr, &i);
			n = 1;	
		}
		printf ("%s", builts->args_arr[i]);
		if(builts->args_arr[i + 1])
				printf(" ");
	}
	if (!flag_in)
		printf ("\n");
}