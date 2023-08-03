/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:31:35 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/03 15:45:07 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redirection(t_list *list)
{
	int fd_out;
	int fd_in;
	char *file_out;
	char *file_in;

	while (list->outfiles)
	{
		file_out = list->outfiles->data;
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
		list->outfiles = list->outfiles->next;
		// free(file_out);
	}
	
	while (list->infiles)
	{
		file_in = list->infiles->data;
		if (list->infiles->type == INFILE)
		{
			if (fd_in > 2)
				(close(fd_in));
			fd_in = open(file_in, O_RDONLY);
			if (fd_in < 0)
			{
				dprintf(2, "minishell: %s: No such file or directory\n", file_in);
				exit(1);
			}
			dup2(fd_in, 0);
		}
		list->infiles = list->infiles->next;
		// free(file_in);
	}
}