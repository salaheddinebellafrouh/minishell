/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:41:23 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/05 18:54:57 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_one_arg(t_builtins *builts, t_list *c_list)
{
	if (c_list->next == NULL)
	{
		fill_args_arr(builts, c_list);
		ft_redirection(c_list);
		ft_execution(builts);
		free_double_demen(builts->args_arr);
		return (1);
	}
	return (0);
}

void	pid_success(t_builtins *builts, t_list *c_list, int fd[2], int input)
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

// void	pid_unsuccess(int fd[2], int input, int id, int pid)
// {
// 	input = fd[0];
// 	id[i] = pid;
// 	close(fd[1]);
// 	if (!input)
// 		close(input);
// }

int	ft_pipe(t_builtins *builts, t_list *list)
{
	t_list	*c_list;
	int		fd[2];
	int		input;
	int		*id;
	int		i;
	int		j;
	int		pid;

	c_list = list;
	input = 0;
	i = 0;
	j = 0;
	id = malloc(sizeof(int) * list->pipe + 1);
	if (if_one_arg(builts, c_list))
		return (0);
	while (c_list)
	{
		fill_args_arr(builts, c_list);
		pipe(fd);
		pid = fork();
		if (pid == 0)
			pid_success(builts, c_list, fd, input);
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
	free(id);
	return (0);
}

void	ft_execution(t_builtins *builts)
{
	int	i;

	i = 0;
	if (check_command(builts->args_arr[0], "pwd"))
		my_pwd(1);
	else if (check_command(builts->args_arr[0], "cd"))
		my_cd(builts, builts->args_arr[1]);
	else if (check_command(builts->args_arr[0], "exit"))
		my_exit(builts->args_arr[1]);
	else if (check_command(builts->args_arr[0], "echo"))
		my_echo(builts);
	else if (check_command(builts->args_arr[0], "env"))
		my_env(builts);
	else if (check_command(builts->args_arr[0], "unset"))
		my_unset_v2(builts);
	else if (check_command(builts->args_arr[0], "export"))
		my_export_v2(builts);
	else if (builts->args_arr[0])
		execute_externals(builts->args_arr, builts->env);
}
