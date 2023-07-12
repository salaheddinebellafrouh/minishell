/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:41:23 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/12 16:09:45 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_built_ins(char *read, t_builtins *builts, t_list *list)
{
	Node *currentArg = list->arg;
	// while(currentArg)
	if (strcmp(read, "pwd") == 0)
		my_pwd();
	else if (strcmp(currentArg->data, "cd") == 0)
		my_cd(currentArg->next->data);
	else if (strcmp(currentArg->data, "exit") == 0)
		my_exit(NULL);
	else if (strcmp(currentArg->data, "echo") == 0)
		my_echo(currentArg->next->data, 1);
	else if (strcmp(currentArg->data, "env") == 0)
		my_env(builts);
	else if (strcmp(currentArg->data, "unset") == 0)
		my_unset(currentArg->next->data, builts);
	else if (strcmp(read, "export") == 0)
	{
		my_export(builts, "USER", "lharba");
	}
}