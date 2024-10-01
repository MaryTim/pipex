/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:39:10 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/09/24 13:54:03 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_argc(int argc)
{
	if (argc < 5)
		error_handling("Please check the number of your arguments!");
}

int	check_here_doc(char **argv, int (*p)[2])
{
	int	tmp_fd;

	tmp_fd = open(argv[1], O_RDWR);
	if (tmp_fd < 0)
		error_handling("Wrong file descriptor!");
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		// if (fd_tmp >= 0)
		// 	pip_read_here_d(argv[2], fd_tmp, (*p)[1]);
		// return (1);
	}
	else
	{
		//if (tmp_fd >= 0)
			(*p)[0] = tmp_fd;
		return (0);
	}
}