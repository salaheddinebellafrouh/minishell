/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:41:23 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/23 17:05:58 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

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

int		check_command(char *arg, char *str1, char *str2)
{
	if(!ft_strncmp(arg, str1, ft_strlen(str1)) ||
		!ft_strncmp(arg, str2, ft_strlen(str2)))
		return (1);
	return (0);
}




// int ft_pipe(t_builtins *builts, t_list *list)
// {
// 	int i = -1;
// 	t_list *zamal = list;
// 	int pipes = zamal->pipe;
// 	int fd[pipes][2];
// 	int pid[pipes];
// 	while(++i < pipes)
// 	{
// 		if(pipe(fd[i]) < 0)
// 			return 1;
// 	}
// 	i = 0;
// 	while (zamal)
// 	{
// 		fill_args_arr(builts,zamal);
// 		int id = fork();
// 		if (id == 0)
// 		{
// 			if(i == 0)
// 			{
// 				dup2(fd[0][1],1);
// 				for (size_t k = 0; k < 2; k++)
// 				{
// 					close(fd[k][0]);
// 					close(fd[k][1]);
// 				}	
// 			}
// 			else
// 			{
// 				dup2(fd[0][0],0);
// 				for (size_t k = 0; k < 2; k++)
// 				{
// 					close(fd[k][0]);
// 					close(fd[k][1]);
// 				}	
// 			}
// 			execute_built_ins(builts,zamal);
// 			exit(0);
// 		}
// 		else
// 			pid[i] = id;
// 		zamal = zamal->next;
// 		i++;
// 	}
// 	for (size_t k = 0; k < pipes; k++)
// 	{
// 		close(fd[k][0]);
// 		close(fd[k][1]);
// 	}	
// 	for (size_t i = 0; i < pipes; i++)
// 	{
// 		waitpid(pid[i],NULL,0);
// 	}
	
// 	return 1;
// }

void	execute_built_ins(t_builtins *builts, t_list *list)
{
	int i = 0;

	(void)list;
	fill_args_arr(builts,list);
	
	if (check_command(builts->args_arr[0], "pwd", "PWD"))
		my_pwd(1);
		
	else if (check_command(builts->args_arr[0], "cd", "CD"))
		my_cd(builts, builts->args_arr[1]);

	else if (check_command(builts->args_arr[0], "exit", "EXIT"))
		my_exit(builts->args_arr[1]);
		
	else if (check_command(builts->args_arr[0], "echo", "ECHO"))
		my_echo(builts);

	else if (check_command(builts->args_arr[0], "env", "ENV"))
		my_env(builts);

	else if (check_command(builts->args_arr[0], "unset", "UNSET"))
		my_unset(builts, builts->args_arr[1]);
		
	else if (check_command(builts->args_arr[0], "export", "EXPORT"))
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
	else
		execute_externals(builts->args_arr, builts->env);

	free_double_demen(builts->args_arr);
} 