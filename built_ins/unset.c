/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:12 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/08 13:05:44 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	srch_unset_var_exist(t_builtins *builts, char *variable, int len)
{
	int		exist;
	int		j;
	char	**split;

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
				builts->uns_var_place = j;
				break ;
			}
		}
		free_double_demen(split);
		j++;
	}
	return (exist);
}

void	my_unset(t_builtins *b, char *variable)
{
	int		len;
	int		exist;

	if (variable && !check_arg(variable))
	{
		print_error(variable, "not a valid identifier");
		g_global = 1;
		return ;
	}
	len = 0;
	while (variable[len])
		len++;
	exist = srch_unset_var_exist(b, variable, len);
	if (exist)
		free(b->env[b->uns_var_place]);
	while (b->env[b->uns_var_place] && exist == 1)
	{
		b->env[b->uns_var_place] = b->env[b->uns_var_place + 1];
		b->uns_var_place++;
	}
	if (exist == 1)
		b->env_len--;
}
