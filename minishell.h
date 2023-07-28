/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:46:32 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/28 22:01:23 by sbellafr         ###   ########.fr       */
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
#define INFILE 17
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
    int  in_type;
    int pipe;
    int has_pipe;
} t_list;


typedef struct s_builtins
{
    char **env;
    int     env_len;
    char **args_arr;
    int arg_len;
    int pipe_nbr;
} t_builtins;


// libft ------------------------------------------------------
char	*ft_substr(char const *s, unsigned int start, int len);
int		ft_strlen(const char *str);
int		ft_atoi(char *str);
char	*ft_strdup(const char *s1);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_isalnum(int c);
int	    ft_isalnum_v2(char n);
// built in ---------------------------------------------------
void	execute_built_ins(t_builtins *builts, t_list *list);
void	my_cd(t_builtins *builts, char *path);
char    *my_pwd(int print);
void	my_exit(char *exit_arg);
void	my_echo(t_builtins *builts);
void	fill_env(char **environ, t_builtins *builts);
void	my_env(t_builtins *builts);
void	my_unset(t_builtins *builts, char *variable);
void	my_export(t_builtins *builts, char *arg);
void	print_export(t_builtins *builts);
int		if_equal_exist(char *str);
void	free_double_demen(char **split);
void	fill_args_arr(t_builtins *builts, t_list *list);
// execeve ----------------------------------------------------
int     ft_execve(char **args, char **env);
void	execute_externals(char **arg, char **env);
int ft_pipe(t_builtins *builts, t_list *list);
// parsing-------------------------------------------------------------
t_list	*ft_free_list(t_list *list);
char	*ft_strcpy_before(char *dst, char *src);
char	*ft_strcpy_after(char *dst, char *src);
t_list	*ft_expand(t_list *list, char **env);
int	    ft_isdigit(int c);
t_list	*ft_remove_quotes(t_list *list);
void	add_to_list(struct Node **head, char *data, int type);
void	add_elements(struct Node **head, char *data);
int	    ft_symbols(char c);
int	    string_list(char *read, int i, struct Node **head);
t_list	*init_list(void);
t_list	*copy_list(Node *source);
void	print_copy(t_list *list);
Node	*syntax_error(Node *head);
int		ft_syntax_quotes(Node *head);
t_list	*ft_start(char *read, char **env);

typedef struct s_vars
{
    int		i;
	int		j;
	int		k;
	int		s;
	int		d;
	int		l;
	int		kk;
	char	*id;
}   t_vars;

#endif  