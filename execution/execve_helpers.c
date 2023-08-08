/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:57:57 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/08 16:02:33 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	function_found(int *found, int *status)
{
	if (found[0] == 1)
	{
		if (WIFSIGNALED(status[0]))
			g_global = WTERMSIG(status[0]) + 128;
		else
			g_global = WEXITSTATUS(status[0]);
	}
}

void	function_not_found(int *found, char **args)
{
	if (!found[0])
	{
		print_error(args[0], "command not found");
		g_global = 127;
	}
}

char	*get_path(char **env)
{
	int	j;

	j = -1;
	while (env[++j])
	{
		if (!ft_strncmp(env[j], "PATH", 4))
			return (ft_strchr(env[j], '='));
	}
	return (NULL);
}

int	if_no_path(char *path, char **args)
{
	if (!path)
	{
		print_error(args[0], "No such file or directory");
		g_global = 127;
		return (1);
	}
	return (0);
}
