/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:58:54 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/26 15:58:53 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_builtins *builts, char *path)
{
	int	j;

	j = 0;
	while (builts->env[j])
	{
		if (!ft_strncmp(path, builts->env[j], ft_strlen(path)))
			return (ft_strchr(builts->env[j], '='));
		j++;
	}
	return (NULL);
}

void	my_cd(t_builtins *builts, char *path)
{
	char *old_pwd;
	char *old;
	char *new;

	old_pwd = ft_getenv(builts, "PWD");
	if (!path)
		path = ft_getenv(builts, "HOME");
	if (chdir(path) == -1)
		perror("minishell");
	else
	{
		old = ft_strjoin("OLDPWD=", old_pwd);
		new = ft_strjoin("PWD=", my_pwd(0));
		my_export(builts, old);
		my_export(builts, new);
		free(old);
		free(new);
	}
}