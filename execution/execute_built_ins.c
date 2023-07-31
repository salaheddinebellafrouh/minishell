/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:41:23 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/31 15:04:47 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(Node *lst)
{
	int		count;
	Node	*temp;

	count = 0;
	temp = (Node *)lst;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

void	fill_args_arr(t_builtins *builts, t_list *list)
{
	Node	*currentArg;
	int		i;

	currentArg = list->arg;
	i = 0;
	builts->args_arr = malloc((ft_lstsize(currentArg) + 1) * sizeof(char *));
	while (currentArg)
	{
		builts->args_arr[i] = strdup(currentArg->data);
		i++;
		currentArg = currentArg->next;
	}
	builts->args_arr[i] = NULL;
	builts->arg_len = i;
}

int	check_command(char *arg, char *str1, char *str2)
{
	if (arg && (!ft_strncmp(arg, str1, ft_strlen(str1)) ||
		!ft_strncmp(arg, str2, ft_strlen(str2))))
			return (1);
	return (0);
}

int	ft_pipe(t_builtins *builts, t_list *list)
{
	t_list	*c_list;
	int		fd[2];
	int		input;
	int		id[list->pipe + 1];
	int		i;
	int		j;
	int		pid;

	c_list = list;
	input = 0;
	i = 0;
	j = 0;
	
	// if (list->next == NULL)
	// {
	// 	fill_args_arr(builts, c_list);
	// 	_in = dup(0);
    //  _out = dup(1);
	// 	ft_redirection(builts, c_list);
	// 	ft_execution(builts);
	// 	dup2(0, _in);
	// 	dup2(1, _out);
	// 	free_double_demen(builts->args_arr);
	// 	return (0);
	// }
	while (c_list)
	{
		fill_args_arr(builts, c_list);
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(input, 0);
			if (c_list->has_pipe == 1)
			{
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
			ft_redirection(c_list);
			ft_execution(builts);
			exit(0);
		}
		else
		{
			input = fd[0];
			id[i] = pid;
			close(fd[1]);
			if (!input)
				close(input);
		}
		i++;
		c_list = c_list->next;
		free_double_demen(builts->args_arr);
	}
	while (j < i)
		waitpid(id[j++], NULL, 0);
	return (0);
}

void	ft_execution(t_builtins *builts)
{
	int i = 0;
	// int status = 0;

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
	else if (builts->args_arr[0])
		execute_externals(builts->args_arr, builts->env);
	// exit(status);
}