/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:53:10 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/03 15:47:09 by nvillalt         ###   ########.fr       */
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

int	error_exit(void)
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

void	exit_dup_error(int *pip, int fd)
{
	perror("pipex error");
	if (pip && pip[0] != -1)
		close(pip[0]);
	if (pip && pip[1] != -1)
		close(pip[1]);
	if (fd)
		close(fd);
	exit(EXIT_FAILURE);
}
