/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:52:48 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/08 16:00:55 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	check_permission(char *cmd)
{
	struct stat	file_state;

	lstat(cmd, &file_state);
	if (S_ISDIR(file_state.st_mode))
	{
		print_error(cmd, "is a directory");
		return (0);
	}
	else if (access(cmd, F_OK))
	{
		print_error(cmd, "No such file or directory");
		return (0);
	}
	return (1);
}

void	has_path(char **args, char **env)
{
	int	status;

	if (access(args[0], F_OK | X_OK) == 0)
	{
		if (fork() == 0)
			execve(args[0], args, env);
		else
			wait(&status);
		g_global = WEXITSTATUS(status);
	}
	else
	{
		print_error(args[0], "No such file or directory");
		g_global = 126;
	}
}

void	hasnt_path_loop(char **args, char **env, char **paths, int *found)
{
	int		i;
	char	*str;
	char	*tmp;
	int		status;

	i = -1;
	while (paths[++i])
	{
		str = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(str, args[0]);
		free(str);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			(*found) = 1;
			if (fork() == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				execve(tmp, args, env);
			}
			else
				wait(&status);
		}
		free(tmp);
	}
	function_found(found, &status);
}

void	ft_execve(char **args, char **env)
{
	char	*path;
	char	**paths;
	int		found;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (!check_permission(args[0]))
		{
			g_global = 126;
			return ;
		}
		has_path(args, env);
	}
	else
	{
		path = get_path(env);
		if (if_no_path(path, args) == 1)
			return ;
		paths = ft_split(path, ':');
		found = 0;
		hasnt_path_loop(args, env, paths, &found);
		function_not_found(&found, args);
		free_double_demen(paths);
	}
}

void	execute_externals(char **arg, char **env)
{
	ft_execve(arg, env);
}
