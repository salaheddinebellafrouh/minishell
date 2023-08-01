/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:12 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/01 18:32:32 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_unset(t_builtins *builts, char *variable)
{
	int		j;
	int		len;
	int		exist;
	char	**split;
	// char 	**new_env;

	len = 0;
	while (variable[len])
		len++;
	exist = 0;
	j = 0;
	while (builts->env[j])
	{
		split = ft_split(builts->env[j], '=');
		if (ft_strlen(split[0]) == len)
		{
			if (!ft_strncmp(variable, builts->env[j], len))
			{
				free_double_demen(split);
				exist = 1;
				break ;
			}
		}
		free_double_demen(split);
		j++;
	}
	if (exist)
		free(builts->env[j]);
	while (builts->env[j] && exist == 1)
	{
		builts->env[j] = builts->env[j + 1];
		j++;
	}
	if (exist == 1)
		builts->env_len--;

	
	// if(exist == 1)
	// {
	// 	builts->env_len--;
	// 	new_env = malloc(sizeof(char *) * (builts->env_len + 2));
	// 	int a = 0;
	// 	int b = 0;
	// 	while (builts->env[a] && exist == 1)
	// 	{
	// 		// free(builts->env[j]);
	// 		if(a == j)
	// 			a++;
	// 		new_env[b] = builts->env[a];
	// 		b++;
	// 		a++;
	// 	}
	// 	new_env[b] = NULL;
	// 	free(builts->env);
	// 		builts->env = new_env;	
	// }
}
