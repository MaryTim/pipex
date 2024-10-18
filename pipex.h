/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:55:51 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/07 16:26:55 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# include "libftPrintfGnl/libft.h"
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# define PIPEX_H

void	error_handling(char *str);
void	execute(char *argv, char **envp);
void	here_doc(char *limiter, int argc);
void	child_process(char *argv, char **envp);
int		open_file(char *argv, int i);

#endif
