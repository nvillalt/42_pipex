/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:53:10 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/01 20:37:28 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	pip[2];
	int	status;
	int	i;

	i = 0;
	if (argc != 5)
		return (argument_error());
	if (pipe(pip) == -1)
		return (leave_program(NULL, NULL));
	first_child(pip, argv, env);
	close(pip[1]);
	second_child(pip, argv, env);
	close(pip[0]);
	while (i < 2)
	{
		wait(&status);
		i++;
	}
	return (EXIT_SUCCESS);
}
