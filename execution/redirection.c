/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:31:35 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/26 16:11:50 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void    ft_redirection(t_builtins *builts, t_list *list)
{
    int fd;
    int old;
    char *file;
    
    
    file = list->outfiles->data;
    // printf("->%s\n", file);
    old = dup(1);
    fd = open(file, O_CREAT | O_RDWR | O_TRUNC , 0777);
    // fd = open("test.txt", O_CREAT | O_RDWR | O_APPEND , 0777);
    dup2(fd, 1);
    ft_pipe(builts, list);
    close(fd);
    dup2(old, 1);
}