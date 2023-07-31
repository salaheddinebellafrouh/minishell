/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:02 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/31 14:41:54 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_exit(char *exit_arg)
{
	int	exit_code;

	exit_code = 0;
	if (exit_arg != NULL)
		exit_code = ft_atoi(exit_arg);
	exit(exit_code);
}
