/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:46:32 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/15 12:45:01 by nchaknan         ###   ########.fr       */
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
    int         token;
	struct Node	*next;
	struct Node	*prev;
}				Node;

#define REDIRECTION_SYMBOL 5
#define OUTFILE 15
#define APPEND 16
#define infile 17
#define HAIRDOC 18

/**********************/
#define DQUOTES 19
#define SQUOTES 20
#define NQUOTES 21




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
    char **args_arr;
    int arg_len;
} t_builtins;


// libft ------------------------------------------------------
char	*ft_substr(char const *s, unsigned int start, int len);
int		ft_strlen(const char *str);
int		ft_atoi(char *str);
char	*ft_strdup(const char *s1);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(const char *s, char c);
// built in ---------------------------------------------------
void	execute_built_ins(t_builtins *builts, t_list *list);
void	my_cd(char *path);
void	my_pwd();
void	my_exit(char *exit_arg);
void	my_echo(char *str, int flag);
void	fill_env(char **environ, t_builtins *builts);
void	my_env(t_builtins *builts);
void	my_unset(t_builtins *builts, char *variable);
void	my_export(t_builtins *builts, char *arg);
void	print_export(t_builtins *builts);
int		if_equal_exist(char *str);
// parsing-------------------------------------------------------------
t_list    *ft_free_list(t_list *list);

#endif