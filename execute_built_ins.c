/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:41:23 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/09 16:14:06 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_built_ins(char *read, t_builtins *builts)
{
	if (strcmp(read, "pwd") == 0)
		my_pwd();
	else if (strcmp(read, "cd") == 0)
		my_cd("..");
	else if (strcmp(read, "exit") == 0)
		my_exit(NULL);
	else if (strcmp(read, "echo") == 0)
		my_echo("8h f nhar", 1);
	else if (strcmp(read, "env") == 0)
		my_env(builts);
	else if (strcmp(read, "unset") == 0)
		my_unset("USER", builts);
}