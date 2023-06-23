/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:46:32 by sbellafr          #+#    #+#             */
/*   Updated: 2023/06/23 22:47:30 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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
} t_list;


char	*ft_substr(char const *s, unsigned int start, int len);
int     ft_strlen(const char *str);
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

#endif