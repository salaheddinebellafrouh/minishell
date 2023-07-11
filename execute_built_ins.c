/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:41:23 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/11 16:51:16 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_built_ins(char *read, t_builtins *builts, t_list *list)
{
	arg_list *currentArg = list->arg;
	// while(currentArg)
	if (strcmp(read, "pwd") == 0)
		my_pwd();
	else if (strcmp(currentArg->arg, "cd") == 0)
		my_cd(currentArg->next->arg);
	else if (strcmp(currentArg->arg, "exit") == 0)
		my_exit(NULL);
	else if (strcmp(currentArg->arg, "echo") == 0)
		my_echo(currentArg->next->arg, 1);
	else if (strcmp(currentArg->arg, "env") == 0)
		my_env(builts);
	else if (strcmp(currentArg->arg, "unset") == 0)
		my_unset(currentArg->next->arg, builts);
	else if (strcmp(read, "export") == 0)
	{
		my_export(builts, "USER", "lharba");
	}
}