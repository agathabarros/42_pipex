/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agathabarros <agathabarros@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:20:13 by agathabarro       #+#    #+#             */
/*   Updated: 2023/08/16 19:16:10 by agathabarro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Print error message and exit
 * @param msg The error message
*/
void	error(void)
{
	perror("Error\n");
	exit(EXIT_FAILURE);
}

/**
 * @brief Print error message and exit
 * @param header The header of the error message
*/
void	if_error(char *header, char *msg)
{
	ft_putstr_fd(header, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free (str);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**path_envp;
	char	*path_cmd;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5)==0)
		i++;
	path_envp = ft_split(envp[i] + 5, ':');
	i = -1;
	while (path_envp[++i])
	{
		part_path = ft_strjoin(path_envp[i], "/");
		path_cmd = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path_cmd, F_OK) == 0)
			return (path_cmd);
		free(path_cmd);
	}
	i = -1;
	while (path_cmd[++i])
		free(path_cmd);
	if_error(cmd, "command not found");
	return (NULL);
}


void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_split(argv, ' '); 
	path = get_path(cmd[0], envp);
	if (!path)
	{
		while (cmd [i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		exit(1);
	}
	if (execve(path, cmd, envp) == -1)
		error();
}
