/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:31:35 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/02 15:31:11 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redirection(t_list *list)
{
	int fd_out;
	int fd_in;
	char *file_out;
	char *file_in;
	char *str;
	int fd[2];
	
	while(list->hairdoc)
	{
		pipe(fd);
	    while(1)
	    {
	        str = readline(">");
	        if(!str || !strcmp(str,list->hairdoc->data))
	        {
				if(str)
	            	free(str);
				else
					printf("\n");
	            break ;
	        }
	        write(fd[1] ,str, ft_strlen(str));
	        write(fd[1],"\n",1);
	        free(str);
	    }
		if(!list->hairdoc->next)
		{
			dup2 (fd[0], 0);
			close(fd[0]);
			close(fd[1]);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
		}
	    list->hairdoc = list->hairdoc->next;
	}

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
				dprintf(2, "minishell: %s: No such file or directory\n",
						file_in);
				exit(1);
			}
			dup2(fd_in, STDIN_FILENO);
		}
		list->infiles = list->infiles->next;
	}
}