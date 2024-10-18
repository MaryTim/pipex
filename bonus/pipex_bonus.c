/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:40:31 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/07 16:29:33 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error_handling("some issues with file opening");
	return (file);
}

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error_handling("some issues with pipe");
	pid = fork();
	if (pid == -1)
		error_handling("some issues with forking");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	here_doc(char *limiter, int argc)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	if (argc < 6)
		error_handling("Please check your arguments!");
	if (pipe(fd) == -1)
		error_handling("something is wrong with the pipe (heredoc)");
	pid = fork();
	if (pid == 0) // Child process
	{
		close(fd[0]);  // Close the read end of the pipe
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (!line)
				error_handling("Error reading input");
			// If the line matches the limiter, exit
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			// Write the line to the pipe (to be used by the next process)
			write(fd[1], line, ft_strlen(line));
			free(line);  // Free the line after it's written to the pipe
		}
	}
	else // Parent process
	{
		close(fd[1]);  // Close the write end of the pipe
		dup2(fd[0], STDIN_FILENO);  // Redirect pipe read end to stdin
		wait(NULL);  // Wait for the child process to finish
	}
}

