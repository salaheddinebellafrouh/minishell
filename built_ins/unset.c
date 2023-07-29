/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:12 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/26 15:59:10 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_unset(t_builtins *builts, char *variable)
{
	int j = 0;
	int len;
	int exist;
	char **split;

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
	while (builts->env[j] && exist == 1)
	{
		free(builts->env[j]);
		builts->env[j] = builts->env[j + 1];
		j++;
	}
	if (exist == 1)
		builts->env_len--;
}