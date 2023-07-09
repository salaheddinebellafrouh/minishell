/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:12 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/09 16:15:14 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	my_unset(char *value, t_builtins *builts)
{
	int j = 0;
	int len;
	int check = 0;
	
	len = 0;
	while(value[len])
		len++;
	j = 0;
	while(builts->env[j])
	{
		if(!ft_strncmp(value, builts->env[j], len))
		{
			check = 1;
			break;
		}
		j++;
	}
	while(builts->env[j] && check == 1)
	{
		builts->env[j] = builts->env[j + 1];
		j++;
	}
}