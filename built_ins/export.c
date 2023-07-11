/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:04 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/11 13:00:51 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	my_export(t_builtins *builts, char *variable, char *value)
{
	int j;
	int len;
	int exist;
	char *new_vrbl;
	char **new_env;

	j = -1;
	if(!variable && !value)
	{
		while(builts->env[++j])
			printf("declare -x %s\n", builts->env[j]);
	}
	else
	{
		len = 0;
		while(variable[len])
			len++;
	
			
		exist = 0;
		j = -1;
		while(builts->env[++j])
		{
			if(!ft_strncmp(variable, builts->env[j], len))
			{
				exist = 1;
				break;
			}
		}
	
		
		if(exist)
		{
			variable = ft_strjoin(variable, "=");
			new_vrbl = variable;
			variable = ft_strjoin(new_vrbl, value);
			free(new_vrbl);
			free(builts->env[j]);
			builts->env[j] = variable;
		}
	
		
		else if(!exist)
		{
			builts->env_len++;
			new_env = malloc(sizeof(char *) * (builts->env_len + 1));
			j = -1;
			while(builts->env[++j])
				new_env[j] = builts->env[j];
			variable = ft_strjoin(variable, "=");
			new_vrbl = variable;
			variable = ft_strjoin(new_vrbl, value);
			free(new_vrbl);
			new_env[j] = variable;
			new_env[++j] = NULL;
			free(builts->env);
			builts->env = new_env;
		}
	}	
}