/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:36:17 by lgosselk          #+#    #+#             */
/*   Updated: 2024/01/17 11:27:40 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	message(char *error)
{
	write(STDERR_FILENO, error, ft_strlen(error));
	return (1);
}

void	file_error(char *msg)
{
	perror(msg);
}

void	message_error(char *error_msg, int exit_status)
{
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	exit(exit_status);
}
