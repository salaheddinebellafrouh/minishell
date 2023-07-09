/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:01 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/09 16:10:51 by nchaknan         ###   ########.fr       */
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
	builts->env = malloc(sizeof(char *) * (len + 1));
	j = -1;
	while(environ[++j])
		builts->env[j] = strdup(environ[j]);
	builts->env[j] = NULL;
}

void	my_env(t_builtins *builts)
{
	int j;

	j = -1;
	while(builts->env[++j] != NULL)
		printf("%s\n", builts->env[j]);
}