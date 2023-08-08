/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:02 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/08 16:07:35 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(char **exit_arg)
{
	int	i;

	i = 1;
	while (exit_arg[i])
	{
		i++;
	}
	if (i > 2)
	{
		print_error("exit", "too many arguments");
		return (0);
	}
	return (1);
}

int	check_numberic(char *a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		if (!ft_isdigit(a[i]))
		{
			print_error("exit", "numeric argument required");
			return (0);
		}
		i++;
	}
	return (1);
}

void	my_exit(char **exit_arg)
{
	int	exit_code;

	exit_code = 0;
	if (exit_arg[1] != NULL)
	{
		if (!check_numberic(exit_arg[1]))
			exit(255);
		if (!count_args(exit_arg))
		{
			g_global = 1;
			return ;
		}
		exit_code = ft_atoi(exit_arg[1]);
	}
	exit(exit_code);
}
