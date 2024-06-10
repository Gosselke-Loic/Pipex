/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:26:23 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/24 10:54:49 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	exec_child_bonus(char *path, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		message_error(ERR_PIPE, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		message_error(ERR_FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		exec_command(path, envp);
	}
	else
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
	}
}

static int	get_next_line(char **line)
{
	int		i;
	char	c;
	int		byte;
	char	*buffer;

	i = 0;
	byte = 0;
	buffer = (char *) malloc(10000 * sizeof(char));
	if (buffer == NULL)
		return (-1);
	byte = read(STDIN_FILENO, &c, 1);
	while (byte && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		byte = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (byte);
}

static void	handle_here_doc(char *limiter)
{
	pid_t	pid1;
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		message_error(ERR_PIPE, EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == 0)
	{
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(pipe_fd[WRITE], line, ft_strlen(line));
		}
		free(line);
	}
	else
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
		wait(NULL);
	}
}

int	open_outfile(char	*path, int type)
{
	int	file;

	file = 0;
	if (type == 0)
		file = open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (type == 1)
		file = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file < 0)
	{
		perror("pipex");
		exit(127);
	}
	return (file);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		infile;
	int		outfile;

	if (argc < 5 || (argc < 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
		|| !envp[0])
		return (message(ERR_ARGS));
	i = 2;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		outfile = open_outfile(argv[argc - 1], 0);
		handle_here_doc(argv[2]);
	}
	else
	{
		infile = open_file(argv[1], 2);
		outfile = open_outfile(argv[argc - 1], 1);
		dup2(infile, STDIN_FILENO);
	}
	while (i < (argc - 2))
		exec_child_bonus(argv[i++], envp);
	dup2(outfile, STDOUT_FILENO);
	exec_command(argv[argc - 2], envp);
	exit(EXIT_SUCCESS);
}
