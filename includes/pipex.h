/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:42:20 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/24 10:45:15 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/types.h>

# define READ 0
# define WRITE 1

# define ERR_FORK "Error: fork failed\n"
# define ERR_CMD "Error: command not found\n"
# define ERR_PIPE "Error: pipe cannot be opened\n"
# define ERR_EXEC "Error: fail to execute command\n"
# define ERR_INFILE "Error: infile cannot be opened\n"
# define ERR_OUTFILE "Error: outfile cannot be opened\n"
# define ERR_ARGS "Error: bad number of arguments or no environment\n"

/* Errors */

int		message(char *error);
void	file_error(char *msg);
void	message_error(char *error_msg, int exit_status);

/* Funtions utils */

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/* Child */

int		open_file(char	*path, int type);
char	*find_path(char	*cmd, char **envp);
void	exec_command(char *argv, char **envp);
void	exec_child(int *pipe_fd, char **argv, char **envp);
void	exec_parent(int *pipe_fd, char **argv, char **envp);

#endif