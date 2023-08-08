/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:31:35 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/08 16:31:29 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *str, char *message)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

void	run_heredoc(t_list *list)
{
	int		fd[2];
	t_list	*temp;
	t_node	*heredoc;

	temp = list;
	heredoc = list->hairdoc;
	while (temp)
	{
		while (heredoc)
		{
			pipe(fd);
			heredoc_loop(heredoc, fd);
			if (!heredoc->next)
			{
				dup2(fd[0], 0);
				close_fds(fd);
			}
			else
				close_fds(fd);
			heredoc = heredoc->next;
		}
		temp = temp->next;
	}
}

void	outfiles_loop(t_list *list, int fd_out)
{
	char	*file_out;
	t_node	*tempin;

	file_out = list->outfiles->data;
	tempin = list->outfiles->next;
	if (list->outfiles->type == OUTFILE)
	{
		if (fd_out > 2)
			(close(fd_out));
		fd_out = open(file_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(fd_out, 1);
	}
	else if (list->outfiles->type == APPEND)
	{
		if (fd_out > 2)
			(close(fd_out));
		fd_out = open(file_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		dup2(fd_out, 1);
	}
	close(fd_out);
	free(list->outfiles->data);
	free(list->outfiles);
	list->outfiles = tempin;
}

void	infiles_loop(t_list *list, int fd_in)
{
	char	*file_in;
	t_node	*tempout;

	file_in = list->infiles->data;
	tempout = list->infiles->next;
	if (list->infiles->type == INFILE)
	{
		if (fd_in > 2)
			(close(fd_in));
		fd_in = open(file_in, O_RDONLY);
		if (fd_in < 0)
		{
			print_error(file_in, "No such file or directory");
			list->check_infile = 0;
		}
		dup2(fd_in, 0);
	}
	close(fd_in);
	free(list->infiles->data);
	free(list->infiles);
	list->infiles = tempout;
}

void	ft_redirection(t_list *list)
{
	int		fd_in;
	int		fd_out;

	fd_out = 0;
	while (list->outfiles)
		outfiles_loop(list, fd_out);
	fd_in = 0;
	while (list->infiles)
		infiles_loop(list, fd_in);
}
