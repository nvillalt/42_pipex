/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:53:10 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/31 19:58:43 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define ARG_ERROR	"execute as './pipex <infile> <cmd1> <cmd2> <outfile>'"

// pipex.c
int		first_child(int *pip, char **argv, char **env);
int		second_child(int *pip, char **argv, char **env);

// get_path.c
int		exec_path(char *argv, char **envp);

// utils.c
int		argument_error();
int		leave_program(char *path, char **commands);
int		error_exit();
void	free_commands(char **commands);

#endif