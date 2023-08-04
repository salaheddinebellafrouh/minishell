/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:31:35 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/03 17:48:36 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redirection(t_list *list)
{
	int fd_out;
	int fd_in;
	char *file_out;
	char *file_in;

	// while(list->hairdoc)
	// {
	//     fd = open("kk", O_CREAT | O_RDWR | O_TRUNC , 0664);
	//     while(1)
	//     {
	//         str = readline(">");
	//         if(!strcmp(str,list->hairdoc->data))
	//         {
	//             free(str);
	//             break ;
	//         }
	//         write(fd,str, ft_strlen(str));
	//         write(fd,"\n",1);
	//         free(str);
	//     }
	//     fd_in = open("kk",O_RDWR);
	//     list->hairdoc = list->hairdoc->next;
	// }
	// Node *out = list->outfiles;
	Node *tempin;
	tempin = NULL;
	while (list->outfiles)
	{
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
		// free(file_out);
		free(list->outfiles->data);
		free(list->outfiles);
		list->outfiles = tempin;
	}

	Node *tempout;
	tempout = NULL;
	while (list->infiles)
	{
		file_in = list->infiles->data;
		tempout = list->infiles->next;

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
		free(list->infiles->data);
		free(list->infiles);
		list->infiles = tempout;
	}
}