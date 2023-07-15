/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:04 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/15 13:01:35 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	free_double_demen(char **split)
{
	int j;
	
	j = -1;
	while(split[++j])
		free(split[j]);
	free(split);	
}

int	check_arg(char *arg)
{
	if(arg[0] == '_' ||
		(arg[0] >= 65 && arg[0] <= 90) ||
		(arg[0] >= 97 && arg[0] <= 122))
			return(1);
	else
		return(0);		
}

void	print_export(t_builtins *builts)
{
	char **split;
	char *variable;
	char *value;
	int j;

	j = -1;
	while(builts->env[++j])
	{
		split = ft_split(builts->env[j], '=');
		variable = split[0];
		value = split[1];
		printf("declare -x %s", variable);
		if(if_equal_exist(builts->env[j]))
			printf("=");
		if(value)
			printf("\"%s\"", value);	
		printf("\n");
		free_double_demen(split);
	}
}

void	my_export(t_builtins *builts, char *arg)
{
	int j;
	int len;
	int exist;
	char **split;
	char *variable;
	char *value;
	char *new_vrbl;
	char **new_env;

	if(!arg)
	{
		j = -1;
		while(builts->env[++j])
		{
			split = ft_split(builts->env[j], '=');
			variable = split[0];
			value = split[1];

			printf("declare -x %s", variable);
			if(if_equal_exist(builts->env[j]))
				printf("=");
			if(value)
				printf("\"%s\"", value);	
			printf("\n");
			free_double_demen(split);
		}
	}

	else if(arg && !check_arg(arg))
		printf("export: `%s': not a valid identifier\n", arg);
	
	else
	{
		split = ft_split(arg, '=');
		variable = split[0];
		value = split[1];
		
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
			if(if_equal_exist(arg) && value)
			{
				variable = ft_strjoin(variable, "=");
				new_vrbl = variable;
				variable = ft_strjoin(new_vrbl, value);
				free(new_vrbl);
				builts->env[j] = variable;
			}
			else if(if_equal_exist(arg))
			{
				variable = ft_strjoin(variable, "=");
				builts->env[j] = variable;
			}
		}
	
		
		else if(!exist)
		{
			builts->env_len++;
			new_env = malloc(sizeof(char *) * (builts->env_len + 1));
			j = -1;
			while(builts->env[++j])
				new_env[j] = builts->env[j];
			new_env[j] = ft_strdup(arg);
			new_env[++j] = NULL;
			free(builts->env);
			builts->env = new_env;
		}
		free_double_demen(split);
	}	
}