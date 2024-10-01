/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:56:03 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/09/24 14:25:30 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **argv, char **envp, int *fd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		error_handling("Can't open the file with provided fd");
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

int main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		error_handling("Please check the number of your arguments!");
	else
	{
		if (pipe(fd) == -1)
			error_handling("Something went wrong with file descriptor!");
		pid = fork();
		if (pid == -1)
			error_handling("Something went wrong with forking!");
		if (pid == 0)
		//child
		waitpid(pid, NULL, 0);
		// otherwise parent
	}
	return (0);
}