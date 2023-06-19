/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:46:10 by sbellafr          #+#    #+#             */
/*   Updated: 2023/06/15 19:11:51 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start(char *read)
{
	printf("%s\n", read);
}
int	main(void)
{
	char	*read;

	while (1)
	{
		read = readline("minishell> ");
		if (!read)
			exit(0);
		ft_start(read);
		free(read);
	}
}
