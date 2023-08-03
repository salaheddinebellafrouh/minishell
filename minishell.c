/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:08:26 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/03 16:24:37 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_heredoc(t_list *list)
{
	int fd[2];
	char *str;
	t_list *temp = list;
	Node *heredoc = list->hairdoc;
	while (temp)
	{
		while (heredoc)
		{
			pipe(fd);
			while (1)
			{
				str = readline(">");
				if (!str || !strcmp(str, heredoc->data))
				{
					if (str)
						free(str);
					else
						printf("\n");
					break;
				}
				write(fd[1], str, ft_strlen(str));
				write(fd[1], "\n", 1);
				free(str);
			}
			if (!heredoc->next)
			{
				dup2(fd[0], 0);
				close(fd[0]);
				close(fd[1]);
			}
			else
			{
				close(fd[0]);
				close(fd[1]);
			}
			heredoc = heredoc->next;
		}
		temp = temp->next;
	}
}

void signal_c(int SIGC)
{
	if (SIGC == 2)
	{
		rl_on_new_line();
		// rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

int main(int ac, char **av, char **env)
{
	char *read;
	t_list *list;
	t_builtins *builts;

	signal(SIGINT, signal_c);
	signal(SIGQUIT, SIG_IGN);
	(void)ac;
	(void)av;
	builts = malloc(sizeof(t_builtins));
	fill_env(env, builts);
	while (1)
	{
		read = readline("minishell> ");
		if (!read)
			exit(0);
		if (read[0])
			add_history(read);
		list = ft_start(read, builts->env);
		if (list)
		{
			int _old = dup(0);
			int _new = dup(1);
			run_heredoc(list);
			ft_pipe(builts, list);
			dup2(_old, 0);
			dup2(_new, 1);
		}
		ft_free_list(list);
		free(read);
		// system("leaks minishell | grep 'leaks for'");
	}
	return (0);
}
