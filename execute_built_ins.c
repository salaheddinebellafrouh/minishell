/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:41:23 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/07 19:44:51 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_built_ins(char *read)
{
	if (strcmp(read, "pwd") == 0) 
        my_pwd();
	else if (strcmp(read, "cd") == 0) 
        my_cd("..");
	else if (strcmp(read, "exit") == 0)
        my_exit(NULL);
}