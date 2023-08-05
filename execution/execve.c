/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:52:48 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/05 18:21:59 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_execve(char **args, char **env)
{
	char	*path;
	char	**paths;
	int		found;
	int		i;
	char	*str;
	char	*tmp;

	if (args[0][0] == '/')
	{
		if (access(args[0], F_OK | X_OK) == 0)
		{
			if (fork() == 0)
				execve(args[0], args, env);
			else
				wait(NULL);
		}
		else
			dprintf(2, "minishell: %s: No such file or directory\n", args[0]);
	}
	else
	{
		path = get_path(env);
		if (!path)
		{
			dprintf(2, "minishell: %s: No such file or directory\n", args[0]);
			return ;
		}
		paths = ft_split(path, ':');
		found = 0;
		i = -1;
		while (paths[++i])
		{
			str = ft_strjoin(paths[i], "/");
			tmp = ft_strjoin(str, args[0]);
			free(str);
			if (access(tmp, F_OK | X_OK) == 0)
			{
				found = 1;
				if (fork() == 0)
					execve(tmp, args, env);
				else
					wait(NULL);
			}
			free(tmp);
		}
		if (!found)
			dprintf(2, "minishell: %s: command not found\n", args[0]);
		free_double_demen(paths);
	}
}

void	execute_externals(char **arg, char **env)
{
	ft_execve(arg, env);
}
