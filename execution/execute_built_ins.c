/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:41:23 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/25 16:11:24 by nchaknan         ###   ########.fr       */
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

int ft_pipe(t_builtins *builts, t_list *list)
{
	t_list *c_list = list;
	int fd[2];
	int input = 0;
	int id[list->pipe + 1];
	int i = 0;
	int j = 0;
	
	if (list->next == NULL)
	{
		fill_args_arr(builts,c_list);
		execute_built_ins(builts, list);
		free_double_demen(builts->args_arr);
		return 0;
	}
	
	while(c_list)
	{
		fill_args_arr(builts,c_list);
		pipe(fd);
		int pid = fork();
		if (pid == 0)
		{
			dup2(input, 0);
			if(c_list->has_pipe == 1)
			{
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
			execute_built_ins(builts, list);
			exit(0);
		}
		else
		{
			input = fd[0];
			id[i] = pid;
			close(fd[1]);
		}
		i++;
		c_list = c_list->next;
		free_double_demen(builts->args_arr);
	}
	while(j < i)
		waitpid(id[j++], NULL, 0);
	return 0;
}

void	execute_built_ins(t_builtins *builts, t_list *list)
{
	int i = 0;
	// int status = 0;
	(void)list;
	
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
	{
		execute_externals(builts->args_arr, builts->env);
	}
	// exit(status);
} 