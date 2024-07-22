/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonte-e <smonte-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:23:57 by smonte-e          #+#    #+#             */
/*   Updated: 2023/11/14 15:59:11 by smonte-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int		input_file;

	input_file = open(argv[1], O_RDONLY);
	if (input_file == -1)
	{
		perror(argv[1]);
		return ;
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(input_file, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int		output_file;

	output_file = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	if (output_file == -1)
	{
		perror(argv[4]);
		exit(127);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(output_file, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pid1 = fork();
		if (pid1 == -1)
			exit(EXIT_FAILURE);
		if (pid1 == 0)
		{
			child_process(argv, envp, fd);
			waitpid(pid1, NULL, 0);
		}
		parent_process(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("Bad Arguments.\n", 2);
		ft_putstr_fd("Try: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
