/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:52:48 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/08 11:06:27 by nchaknan         ###   ########.fr       */
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

static int    check_permission(char *cmd)
{
    struct stat    file_state;

    lstat(cmd, &file_state);
    if (S_ISDIR(file_state.st_mode))
	{
        print_error(cmd, "is a directory");
		return(0);
	}
	else if(access(cmd,F_OK))
	{
		print_error(cmd,"No such file or directory");
		return(0);
	}
    return (1);
}

void	has_path(char **args, char **env)
{
	if (access(args[0], F_OK | X_OK) == 0)
	{
		if (fork() == 0)
			execve(args[0], args, env);
		else
			wait(NULL);
	}
	else
		print_error(args[0], "No such file or directory");
}

void	hasnt_path_loop(char **args, char **env, char **paths, int *found)
{
	int		i;
	char	*str;
	char	*tmp;

	i = -1;
	while (paths[++i])
	{
		str = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(str, args[0]);
		free(str);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			found[0] = 1;
			int pid=fork();
			if (pid == 0)
				execve(tmp, args, env);
			else
				wait(NULL);
		}
		free(tmp);
	}
}

void	ft_execve(char **args, char **env)
{
	char	*path;
	char	**paths;
	int		found;

	if (args[0][0] == '/')
	{
		if(!check_permission(args[0]))
			return ;
		has_path(args, env);
	}
	else
	{
		path = get_path(env);
		if (!path)
		{
			print_error(args[0], "No such file or directory");
			return ;
		}
		paths = ft_split(path, ':');
		found = 0;
		hasnt_path_loop(args, env, paths, &found);
		if (!found)
			print_error(args[0], "command not found");
		free_double_demen(paths);
	}
}

void	execute_externals(char **arg, char **env)
{
	ft_execve(arg, env);
}
