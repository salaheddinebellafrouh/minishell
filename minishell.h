/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:46:32 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/08 16:25:26 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_redirection
{
    char **input_file;
    char **output_file;
    char **append_file;
} t_redirection;

typedef struct s_list
{
    char    *cmd;
    char    **arg;
    int     flag;
    int     pipe;
    t_redirection redirect;
    struct s_list *next;
    struct s_list *prev;
    int           data_size;
} t_list;

// libft ------------------------------------------------------
char	*ft_substr(char const *s, unsigned int start, int len);
int     ft_strlen(const char *str);
int	    ft_atoi(char *str);
// built in ---------------------------------------------------
void	execute_built_ins(char *read, char **environ);
void	my_cd(char *path);
void    my_pwd();
void    my_exit(char *exit_arg);
void	my_echo(char *str, int flag);
void	my_env(char **environ);
//-------------------------------------------------------------

#endif