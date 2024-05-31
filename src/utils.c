/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:53:10 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/31 19:53:23 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	argument_error(void)
{
	ft_putendl_fd(ARG_ERROR, 2);
	return (EXIT_FAILURE);
}

int	leave_program(char *path, char **commands)
{
	perror("pipex error");
	if (path)
		free(path);
	if (commands)
		free_commands(commands);
	exit(EXIT_FAILURE);
}

int	error_exit()
{
	perror("pipex error");
	exit(EXIT_FAILURE);
}

void	free_commands(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free(commands);
	return ;
}