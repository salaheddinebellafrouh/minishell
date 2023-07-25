/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:52:48 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/25 17:16:57 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*get_path(char **env)
{
	int j;

	j = -1;
	while (env[++j])
	{
		if(!ft_strncmp(env[j], "PATH", 4))
			return (ft_strchr(env[j], '='));
	}
	return (NULL);
}

int	ft_execve(char **args, char **env)
{
	int		i = -1;
	char	*str;
	char	*tmp;
	char	*path;
	char	**paths;
	int		found;

	found =  0;
	path = get_path(env);
	if (!path)
	{
		printf("minishell: %s: No such file or directory\n", args[0]);
		return (0);
	}
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		str = ft_strjoin(paths[i], "/");
		tmp = ft_strdup(str);
		free(str);
		str = ft_strjoin(tmp, args[0]);
		free(tmp);
		if (access(str, X_OK) == 0)
        {
			found  = 1;
			if (fork() == 0)
            	execve(str, args, env);
			else
				wait (NULL);
			free(str);	
		    break;
        }
		free(str);
	}
	if (!found)
		printf("minishell: %s: command not found\n", args[0]);
    free_double_demen(paths);
	return (1);
}

void	execute_externals(char **arg, char **env)
{
	// pid_t pid = fork();

    // if (pid < 0) {
    //     perror("fork");
    //     exit(EXIT_FAILURE);
    // }
	// else if (pid == 0)
	// {
		ft_execve(arg, env);
    // }
	// else
	// {
    //     int status;
    //     waitpid(pid, &status, 0);
    // }
}