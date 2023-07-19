/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:58:54 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/19 19:56:21 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*ft_getenv(t_builtins *builts, char *path)
{
	int j = 0;

	while(builts->env[j])
	{
		if(!ft_strncmp(path, builts->env[j], ft_strlen(path)))
			return(ft_strchr(builts->env[j], '='));
		j++;	
	}
	return (NULL);
}

void	my_cd(t_builtins *builts, char *path)
{
	char *old_pwd;

	old_pwd = ft_getenv(builts, "PWD");
	if(!path)
		path = ft_getenv(builts,"HOME");
	if (chdir(path) == -1)
		perror("minishell");
	else
	{	
		my_export(builts, ft_strjoin("OLDPWD=", old_pwd));
		my_export(builts, ft_strjoin("PWD=", my_pwd(0)));
	}
}