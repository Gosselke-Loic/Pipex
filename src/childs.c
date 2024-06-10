/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:38:07 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/17 10:45:25 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_file(char	*path, int type)
{
	int	file;

	file = 0;
	if (type == 0)
		file = open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (type == 1)
		file = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (type == 2)
		file = open(path, O_RDONLY);
	if (file < 0)
		file_error("pipex");
	return (file);
}

char	*find_path(char	*cmd, char **envp)
{
	int		i;
	char	*path;
	char	*temp;
	char	**paths;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

void	exec_command(char *argv, char **envp)
{
	int		i;
	char	**cmds;
	char	*command;

	cmds = ft_split(argv, ' ');
	command = find_path(cmds[0], envp);
	if (command == NULL)
	{
		i = -1;
		while (cmds[++i])
			free(cmds[i]);
		free(cmds);
		message_error(ERR_CMD, 127);
	}
	if (execve(command, cmds, envp) == -1)
		message_error(ERR_EXEC, 127);
}

void	exec_parent(int *pipe_fd, char **argv, char **envp)
{
	int	outfile;

	outfile = open_file(argv[4], 1);
	if (outfile < 0)
		message_error(ERR_OUTFILE, EXIT_FAILURE);
	dup2(pipe_fd[READ], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipe_fd[WRITE]);
	exec_command(argv[3], envp);
	close(outfile);
}

void	exec_child(int *pipe_fd, char **argv, char **envp)
{
	int		infile;

	infile = open_file(argv[1], 2);
	if (infile < 0)
		message_error(ERR_INFILE, EXIT_FAILURE);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(pipe_fd[READ]);
	exec_command(argv[2], envp);
	close(infile);
}
