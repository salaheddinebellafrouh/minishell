/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:41:23 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/07 19:03:34 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_one_arg(t_builtins *builts, t_list *c_list)
{
	if (c_list->next == NULL)
	{
		fill_args_arr(builts, c_list);
		ft_redirection(c_list);
		if (c_list->check_infile == 1)
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

void	pipe_loop(t_builtins *b, t_list *c_list, int *fd, int *i)
{
	while (c_list)
	{
		fill_args_arr(b, c_list);
		pipe(fd);
		b->pid_p = fork();
		if (b->pid_p == 0)
			pid_success(b, c_list, fd, b->input_p);
		else
		{
			b->input_p = fd[0];
			b->id_p[i[0]] = b->pid_p;
			close(fd[1]);
			if (!b->input_p)
				close(b->input_p);
		}
		i[0]++;
		c_list = c_list->next;
		free_double_demen(b->args_arr);
	}
}

int	ft_pipe(t_builtins *b, t_list *list)
{
	t_list	*c_list;
	int		fd[2];
	int		i;
	int		j;

	c_list = list;
	c_list->check_infile = 1;
	b->input_p = 0;
	i = 0;
	j = 0;
	b->id_p = malloc(sizeof(int) * list->pipe + 1);
	if (if_one_arg(b, c_list))
	{
		free(b->id_p);
		return (0);
	}
	pipe_loop(b, c_list, fd, &i);
	while (j < i)
		waitpid(b->id_p[j++], NULL, 0);
	free(b->id_p);
	return (0);
}

void	ft_execution(t_builtins *builts)
{
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
