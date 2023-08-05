/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:11:06 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/05 18:12:55 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_export_v2(t_builtins *builts)
{
	int	i;

	if (!builts->args_arr[1])
		print_export(builts);
	else
	{
		i = -1;
		while (builts->args_arr[++i])
			if (builts->args_arr[i + 1])
				my_export(builts, builts->args_arr[i + 1]);
	}
}

void	my_unset_v2(t_builtins *builts)
{
	int	i;

	i = -1;
	while (builts->args_arr[++i])
		if (builts->args_arr[i + 1])
			my_unset(builts, builts->args_arr[i + 1]);
}
