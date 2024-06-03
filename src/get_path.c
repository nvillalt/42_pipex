/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:53:10 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/01 20:30:34 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	*find_env_path(char **env)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			str = ft_strtrim(env[i], "PATH=");
		i++;
	}
	if (str == NULL)
		leave_program(NULL, NULL);
	return (str);
}

static char	**get_path(char **env)
{
	char	**path;
	char	*aux;
	char	*oneline;
	int		i;

	if (!env)
		return (NULL);
	i = -1;
	oneline = find_env_path(env);
	path = ft_split(oneline, ':');
	if (!path)
		return (NULL);
	while (path[++i])
	{
		aux = ft_strjoin(path[i], "/");
		if (!aux)
		{
			leave_program(oneline, path);
			return (NULL);
		}
		free(path[i]);
		path[i] = aux;
	}
	free(oneline);
	return (path);
}

char	*get_final(char **dup, char *cmd)
{
	char	**cmds;
	char	*route;
	int		i;

	i = 0;
	cmds = ft_split(cmd, ' ');
	while (dup[i])
	{
		route = ft_strjoin(dup[i], cmds[0]);
		if (!access(route, X_OK))
			return (route);
		else
			free(route);
		i++;
	}
	free_commands(cmds);
	return (NULL);
}

char	*dup_path(char *cmd, char **env)
{
	char	**dup;
	char	*final;

	dup = NULL;
	final = NULL;
	if (env && *cmd)
	{
		dup = get_path(env);
		final = get_final(dup, cmd);
		if (!final)
			leave_program(NULL, dup);
	}
	if (dup)
		free_commands(dup);
	return (final);
}

void	exec_path(char *s, char **env)
{
	char	*path;
	char	**cmds;

	if (!*s)
	{
		ft_putendl_fd(ERROR, 2);
		exit(EXIT_FAILURE);
	}
	if (!access(s, X_OK))
		path = s;
	else if (access(s, X_OK))
		path = dup_path(s, env);
	cmds = ft_split(s, ' ');
	if (!cmds)
		leave_program(path, cmds);
	if (execve(path, cmds, env) == -1)
	{
		perror("pipex error");
		free(path);
		free_commands(cmds);
		exit(EXIT_FAILURE);
	}
}
