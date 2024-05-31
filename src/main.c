/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:53:10 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/31 20:43:53 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
	Esta función controla el número de argumentos que tendremos en el programa e
	inicializa la pipe. En caso de error, sale del programa. Asimismo, crea las dos
	funciones para los dos hijos del proceso padre.
	Se necesitan dos hijos para que el proceso padre pueda esperar a los dos, si se 
	hiciera con un padre y un hijo, el padre se saldría nada más terminar sus cosas, 
	dejando a los hijos colgados.
*/

int	main(int argc, char **argv, char **env)
{
	int	pip[2]; // fd[0] es el read end de la pipe y fd[1] es el write end de la pipe - 0 on success, -1 on error

	if (argc != 5)
		return (argument_error());
	if (pipe(pip) == -1)
		return (leave_program(NULL, NULL));
	first_child(pip, argv, env);
	second_child(pip, argv, env);
	return (EXIT_SUCCESS);
}