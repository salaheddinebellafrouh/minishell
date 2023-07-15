/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:01 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/14 19:25:02 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	fill_env(char **environ, t_builtins *builts)
{
	int len;
	int j;
	
	len = 0;
	while(environ[len] != NULL)
		len++;
	builts->env_len = len;
	builts->env = malloc(sizeof(char *) * (len + 1));
	j = -1;
	while(environ[++j])
		builts->env[j] = strdup(environ[j]);
	builts->env[j] = NULL;
}

int if_equal_exist(char *str)
{
	int i;
	
	i = -1;
	while(str[++i])
	{
		if(str[i] == '=')
			return(1);
	}
	return(0);
}

void	my_env(t_builtins *builts)
{
	int j;
	
	j = -1;
	while(builts->env[++j] != NULL)
	{
		if(if_equal_exist(builts->env[j]))
			printf("%s\n", builts->env[j]);
	}
}