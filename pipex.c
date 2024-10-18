/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:56:03 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/07 16:25:35 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **argv, char **envp, int *fd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		error_handling("Can't open the file with provided fd in child");
	//dup2(fd[1], STDOUT_FILENO);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_handling("dup2 failed for STDOUT in child process");
	//dup2(filein, STDIN_FILENO);
	if (dup2(filein, STDIN_FILENO) == -1)
		error_handling("dup2 failed for STDIN in child process");
	close(fd[0]);
	execute(argv[2], envp);
}

void	parent(char **argv, char **envp, int *fd)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error_handling("Can't open the file with provided fd in parent");
	dup2(fd[0], STDIN_FILENO);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_handling("dup2 failed for STDIN in parent process");
	dup2(fileout, STDOUT_FILENO);
	if (dup2(fileout, STDOUT_FILENO) == -1)
		error_handling("dup2 failed for STDOUT in parent process");
	close(fd[1]);
	execute(argv[3], envp);
}

// int main(int argc, char **argv, char **envp)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	if (argc != 5)
// 		error_handling("Please check the number of your arguments!");
// 	else
// 	{
// 		if (pipe(fd) == -1)
// 			error_handling("Something went wrong with file descriptor!");
// 		pid = fork();
// 		if (pid == -1)
// 			error_handling("Something went wrong with forking!");
// 		if (pid == 0)
// 			child(argv, envp, fd);
// 		waitpid(pid, NULL, 0);
// 		parent(argv, envp, fd);
// 	}
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open_file(argv[argc - 1], 0);
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			fileout = open_file(argv[argc - 1], 1);
			filein = open_file(argv[1], 2);
			dup2(filein, STDIN_FILENO);
		}
		while (i < argc - 2)
			child_process(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp);
	}
	error_handling("Please check your arguments!");
}