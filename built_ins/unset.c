/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:12 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/14 19:47:06 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_unset(t_builtins *builts, char *variable)
{
	int j = 0;
	int len;
	int exist;

	len = 0;
	while (variable[len])
		len++;
	exist = 0;
	j = 0;
	while (builts->env[j])
	{
		if (!ft_strncmp(variable, builts->env[j], len))
		{
			exist = 1;
			break ;
		}
		j++;
	}
	while (builts->env[j] && exist == 1)
	{
		builts->env[j] = builts->env[j + 1];
		j++;
	}
	if (exist == 1)
		builts->env_len--;
}