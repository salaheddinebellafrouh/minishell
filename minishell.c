/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:08:26 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/08 16:32:15 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_c(int SIGC)
{
	if (SIGC == 2)
	{
		rl_on_new_line();
		// rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
		g_global = 1;
	}
}

void	run_execution(t_list *list, t_builtins *builts)
{
	int	_old;
	int	_new;

	g_global = 0;
	_old = dup(0);
	_new = dup(1);
	run_heredoc(list);
	ft_pipe(builts, list);
	dup2(_old, 0);
	dup2(_new, 1);
}

int	main(int ac, char **av, char **env)
{
	char		*read;
	t_list		*list;
	t_builtins	*builts;

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
			exit(g_global);
		if (read[0])
			add_history(read);
		list = ft_start(read, builts->env);
		if (list)
			run_execution(list, builts);
		ft_free_list(list);
		free(read);
	}
	return (0);
}
