/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:46:32 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/12 19:06:27 by sbellafr         ###   ########.fr       */
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

typedef struct Node
{
	char		*data;
	struct Node	*next;
}				Node;

typedef struct arg_list {
    char *arg;
    struct arg_list *next;
} arg_list;

typedef struct redirect_file {
    char *filename;
    struct redirect_file *next;
} redirect_file;

typedef struct redirect_list {
    char *redirect;
    struct redirect_list *next;
} redirect_list;

typedef struct t_list {
    Node *arg;
    struct t_list *next;
    struct t_list *prev;
    Node *redirect;
    Node *infiles;
    Node *outfiles;
    Node *hairdoc;

} t_list;


typedef struct s_builtins
{
    char **env;
    int env_len;
} t_builtins;


// libft ------------------------------------------------------
char	*ft_substr(char const *s, unsigned int start, int len);
int		ft_strlen(const char *str);
int		ft_atoi(char *str);
char	*ft_strdup(const char *s1);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin(char const *s1, char const *s2);
// built in ---------------------------------------------------
void    execute_built_ins(char *read, t_builtins *builts, t_list *list);
void	my_cd(char *path);
void	my_pwd();
void	my_exit(char *exit_arg);
void	my_echo(char *str, int flag);
void	fill_env(char **environ, t_builtins *builts);
void	my_env(t_builtins *builts);
void	my_unset(char *variable, t_builtins *builts);
void	my_export(t_builtins *builts, char *variable, char *value);
//-------------------------------------------------------------

#endif