/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:53:10 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/31 20:49:56 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	**get_environment(char **envp, char *argv)
{
	char	*path;
	char	**variables;
	int		i;

	i = 0;
	variables = NULL;
	if (envp == NULL || argv[0] == '/' || argv[0] == '.')
		return (NULL);
	while (envp[i])
	{
		path = envp[i];
		if (!ft_strncmp(path, "PATH", 4))
		{
			path = ft_strchr(path, '=');
			path++;
			variables = ft_split(path, ':');
			if (!variables)
				return (NULL);
			break ;
		}
		i++;
	}
	return (variables);
}

char	*join_path_env(char **variables, char **commands)
{
	char	*aux;
	char	*path;
	int		i;

	path = NULL;
	if (variables != NULL)
	{
		i = 0;
		while (variables[i])
		{
			aux = ft_strjoin(variables[i], "/");
			path = ft_strjoin(aux, commands[0]);
			free(aux);
			if (!access(path, X_OK))
			{
				free_commands(variables);
				return (path);
			}
			free(path);
			i++;
		}
	}
	else if (!variables)
		path = ft_strdup(commands[0]);
	return (path);
}

int	exec_path(char *argv, char **envp)
{
	int		err;
	char	*path;
	char	**variables;
	char	**commands;

	variables = NULL;
	if (envp != NULL)
		variables = get_environment(envp, argv);
	commands = ft_split(argv, ' ');
	path = join_path_env(variables, commands);
	if (!access(path, X_OK))
	{
		err = execve(path, commands, envp);
		if (err == -1)
			return (leave_program(path, commands));
	}
	else if (access(path, X_OK))
		perror("pipex error");
	free(path);
	free_commands(commands);
	return (EXIT_SUCCESS);
}
