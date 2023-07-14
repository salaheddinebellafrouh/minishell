/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:46:32 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/14 17:23:51 by sbellafr         ###   ########.fr       */
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
    int         type;
	struct Node	*next;
	struct Node	*prev;
}				Node;

#define APPEND 16
#define REDIRECTION_SYLBOL 5
#define OUTFILE 15
#define HAIRDOC 18
#define infile 17



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
// parsing-------------------------------------------------------------
t_list    *ft_free_list(t_list *list);

#endif