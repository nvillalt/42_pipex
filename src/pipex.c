/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:53:10 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/01 20:11:57 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*

	On the success of a fork() system call:

    - The Process ID (PID) of the child process is returned to the parent process.
   -  0 is returned to the child process. // Because it refers to the Parent Process -> 0

	Child Process: A child process is created by a parent process 
	in an operating system using a fork() system call. 
	A child process may also be known as subprocess or a subtask.

    - A child process is created as a copy of its parent process.
    - The child process inherits most of its attributes.
    - If a child process has no parent process, then the child process is created directly by the kernel.
    - If a child process exits or is interrupted, then a SIGCHLD signal is sent to the parent process 
	to inform about the termination or exit of the child process.

*/

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
		close(pip[1]);
		dup2(fdout, STDOUT_FILENO);
		dup2(pip[0], STDIN_FILENO);
		close(fdout);
		close(pip[0]);
		exec_path(argv[3], env);
	}
	return (EXIT_SUCCESS);
}