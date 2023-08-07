/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:46:32 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/07 22:00:31 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

typedef struct t_node
{
	char			*data;
	int				type;
	int				token;
	struct t_node	*next;
	struct t_node	*prev;
}				t_node;

# define REDIRECTION_SYMBOL 5
# define OUTFILE 15
# define APPEND 16
# define INFILE 17
# define HAIRDOC 18

/**********************/
# define DQUOTES 19
# define SQUOTES 20
# define NQUOTES 21

typedef struct t_list {
	t_node			*arg;
	struct t_list	*next;
	struct t_list	*prev;
	t_node			*redirect;
	t_node			*infiles;
	t_node			*outfiles;
	t_node			*hairdoc;
	int				in_type;
	int				pipe;
	int				has_pipe;
}t_list;

typedef struct s_builtins
{
	char	**env;
	int		env_len;
	char	**args_arr;
	int		arg_len;
	int		pipe_nbr;
	int		exp_var_place;
	int		uns_var_place;
	int		exit_status;
}t_builtins;
typedef struct s_vars
{
	int		i;
	int		j;
	int		k;
	int		s;
	int		d;
	int		l;
	int		count;
	int		kk;
	char	*id;
	char	*string;
	char	*returned;
}t_vars;

typedef struct s_headvar
{
	int		i;
	int		start;
	int		s;
	int		d;
	char	*cp;

}t_headvar;

int	g_global;
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
int		ft_isalnum_v2(char n);
// execution ---------------------------------------------------
void	ft_execution(t_builtins *builts);
void	my_cd(t_builtins *builts, char *path);
char	*my_pwd(int print);
void	my_exit(char *exit_arg);
void	my_echo(t_builtins *builts);
void	fill_env(char **environ, t_builtins *builts);
void	my_env(t_builtins *builts);
void	my_unset(t_builtins *builts, char *variable);
void	my_unset_v2(t_builtins *builts);
void	my_export(t_builtins *builts, char *arg);
void	my_export_v2(t_builtins *builts);
void	print_export(t_builtins *builts);
int		if_equal_exist(char *str);
int		check_arg(char *arg);
int		check_command(char *arg, char *str1);
void	free_double_demen(char **split);
void	fill_args_arr(t_builtins *builts, t_list *list);
void	ft_redirection(t_list *list);
int		ft_pipe(t_builtins *builts, t_list *list);
void	ft_execve(char **args, char **env);
void	execute_externals(char **arg, char **env);
int		ft_pipe(t_builtins *builts, t_list *list);
// parsing-------------------------------------------------------------
void	ft_free_list(t_list *list);
char	*ft_strcpy_before(char *dst, char *src);
char	*ft_strcpy_after(char *dst, char *src);
t_list	*ft_expand(t_list *list, char **env);
int		ft_isdigit(int c);
t_list	*ft_remove_quotes(t_list *list);
void	add_to_list(struct t_node **head, char *data, int type);
void	add_elements(struct t_node **head, char *data);
int		ft_symbols(char c);
int		string_list(char *read, int i, struct t_node **head);
t_list	*init_list(void);
t_list	*copy_list(t_node *source);
t_node	*syntax_error(t_node *head);
int		ft_syntax_quotes(t_node *head);
t_list	*ft_start(char *read, char **env);
t_node	*quotes_management(char *read, t_node *head);
void	free_infiles_t_nodes(t_list *list);
void	free_redirect_t_nodes(t_list *list);
void	free_arg_t_nodes(t_list *list);
void	free_t_list(t_list *list);
void	free_t_node(t_node *t_node);
t_list	*ft_remove_quotes(t_list *list);
void	init_vars(t_vars *vars);
int		calloc_after(char *string);
int		calloc_before(char *string);
char	*expnd_data(char *data, char **before, char **after);
int		ft_count_string(char *data, char **before, char **after);
void	ft_count_dollar(char *data, char **before, char **after, t_vars *d);
int		count_dollar(char *data);
char	*get_id2(char *data);
void	digit_dollar(t_vars *vars, char *data, char *string);
char	*before_after(char **before, char **after, t_vars *vars, char *string);
void	free_t_nodes_prev(t_node *newt_node, t_node *temp);
void	free_t_nodes_next(t_node *newt_node, t_node *temp);
void	free_newt_node(t_node *newt_node);
char	*ft_itoa(int n);
void	init_headvar(t_headvar *var);
int		syntaxq_return(t_node *head, t_node *temp);
void	init_var(t_headvar *var);
void	ft_putstr_fd(char *s, int fd);
int 	ft_strcmp(char *s1, char *s2);
void	*ft_calloc(unsigned long count, unsigned long size);
typedef struct s_subt_nodes
{
	t_list	*tmp_list;
	t_node	*arg;
	t_node	*redirect;
	t_node	*infiles;
	t_node	*outfiles;
	t_node	*hairdoc;
}t_subt_nodes;

#endif  