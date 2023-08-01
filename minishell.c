/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:08:26 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/01 18:50:54 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_c(int SIGC)
{
	if (SIGC == 2)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
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
			exit(0);
		if (read[0])
			add_history(read);
		list = ft_start(read, builts->env);
		if (list)
			ft_pipe(builts, list);
		ft_free_list(list);
		free(read);
		// system("leaks minishell | grep 'leaks for'");
	}
	return (0);
}
