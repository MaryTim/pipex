/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:17:23 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/02 11:28:44 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
    // envp[i] contains "PATH=/bin:/usr/bin:/some/other/dir"
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
    // skip the "PATH=" (5 characters) and split the directories by ':'
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
    // Construct the full path to the command
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	execute(char *argv, char **envp)
{
	char	**split;
	int 	i;
	char	*path;
	
	i = -1;
	split = ft_split(argv, ' ');
	path = find_path(split[0], envp);
	if (!path)	
	{
		while (split[++i])
			free(split[i]);
		free(split);
		error_handling("something is wrong with PATH");
	}
	if (execve(path, split, envp) == -1)
		error_handling("something is wrong with execve");
}