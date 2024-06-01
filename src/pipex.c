/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:53:10 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/01 20:38:18 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	first_child(int *pip, char **argv, char **env)
{
	int		fdin;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (error_exit());
	if (!pid)
	{
		fdin = open(argv[1], O_RDONLY);
		if (fdin == -1)
			return (error_exit());
		close(pip[0]);
		dup2(fdin, STDIN_FILENO);
		dup2(pip[1], STDOUT_FILENO);
		close(fdin);
		close(pip[1]);
		exec_path(argv[2], env);
		perror("exec_path");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	second_child(int *pip, char **argv, char **env)
{
	int		fdout;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (error_exit());
	if (!pid)
	{
		fdout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (fdout == -1)
			return (error_exit());
		dup2(fdout, STDOUT_FILENO);
		dup2(pip[0], STDIN_FILENO);
		close(fdout);
		close(pip[0]);
		exec_path(argv[3], env);
		perror("exec_path");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
