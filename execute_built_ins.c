/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:41:23 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/15 13:29:47 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_lstsize(Node *lst)
{
	int		count;
	Node	*temp;

	count = 0;
	temp = (Node*)lst;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

void	fill_args_arr(t_builtins *builts, t_list *list)
{
	Node *currentArg = list->arg;
	int i = 0;

	builts->args_arr = malloc((ft_lstsize(currentArg) + 1) * sizeof(char *));
	while(currentArg)
	{
		builts->args_arr[i] = strdup(currentArg->data);
		i++;
		currentArg = currentArg->next;
	}
	builts->args_arr[i] = NULL;
	builts->arg_len = i;
}

void	execute_built_ins(t_builtins *builts, t_list *list)
{
	int i = 0;

	fill_args_arr(builts,list);
	if (strcmp(builts->args_arr[0], "pwd") == 0)
		my_pwd();
		
	else if (strcmp(builts->args_arr[0], "cd") == 0)
		my_cd(builts->args_arr[1]);

	else if (strcmp(builts->args_arr[0], "exit") == 0)
		my_exit(NULL);
		
	else if (strcmp(builts->args_arr[0], "echo") == 0)
	{
		my_echo(builts->args_arr[1], 1);
	}

	else if (strcmp(builts->args_arr[0], "env") == 0)
		my_env(builts);

	else if (strcmp(builts->args_arr[0], "unset") == 0)
		my_unset(builts, builts->args_arr[1]);
		
	else if (strcmp(builts->args_arr[0], "export") == 0)
	{
		if(!builts->args_arr[1])
			print_export(builts);
		else
		{
			i = -1;
			while(builts->args_arr[++i])
			{
				if(builts->args_arr[i + 1])
					my_export(builts, builts->args_arr[i + 1]);
			}
		}
	}
	free_double_demen(builts->args_arr);
}

