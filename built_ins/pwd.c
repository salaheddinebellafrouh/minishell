/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:08 by nchaknan          #+#    #+#             */
/*   Updated: 2023/07/31 14:46:17 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_pwd(int print)
{
	char	*str;
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	if (print)
		printf("%s\n", cwd);
	str = cwd;
	return (str);
}
