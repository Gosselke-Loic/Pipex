/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:42:08 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/24 10:46:36 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	exec_pipex(char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		message_error(ERR_PIPE, EXIT_FAILURE);
	pid1 = fork();
	if (pid1 < 0)
		message_error(ERR_FORK, EXIT_FAILURE);
	if (pid1 == 0)
		exec_child(pipe_fd, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		message_error(ERR_FORK, EXIT_FAILURE);
	if (pid2 == 0)
		exec_parent(pipe_fd, argv, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status, WUNTRACED);
	waitpid(pid2, &status, WUNTRACED);
	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	int	status;

	if (argc != 5 || !envp[0])
		message_error(ERR_ARGS, EXIT_FAILURE);
	status = exec_pipex(argv, envp);
	return (status);
}
