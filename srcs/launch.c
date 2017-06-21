/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 18:58:30 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/26 18:58:36 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		search_local_dir(char **args, char **env)
{
	char *full_path;
	char buff[MAXPATHLEN];

	if (!ft_strncmp(args[0], "/.", 2))
	{
		if (getcwd(buff, MAXPATHLEN) == NULL)
			return (0);
		else
		{
			full_path = ft_strnew(ft_strlen(buff)
								+ ft_strlen((args[0] + 2)) + 1);
			full_path = ft_strncpy(full_path, buff, ft_strlen(buff));
			full_path = ft_strcat(full_path, (args[0] + 2));
		}
	}
	else
		full_path = ft_strdup(args[0]);
	(void)execve(full_path, args, env);
	ft_strdel(&full_path);
	return (-1);
}

int		search_exec(char **args, char **env)
{
	char *env_path;
	char *path;
	char *full_path;

	if (search_local_dir(args, env) == -1)
	{
		env_path = ft_getenv("PATH", env);
		path = ft_strtok_quote(env_path, ":");
		while (path != NULL)
		{
			full_path = ft_strnew(ft_strlen(path) + ft_strlen(args[0]) + 1);
			ft_strcpy(full_path, path);
			ft_strcat(full_path, "/");
			ft_strcat(full_path, args[0]);
			if (execve(full_path, args, env) == -1)
			{
				ft_strdel(&full_path);
				path = ft_strtok_quote(NULL, ":");
			}
		}
	}
	return (-1);
}

void	make_wake(int pid, int *status)
{
	while (1)
	{
		(void)waitpid(pid, status, WUNTRACED);
		if (!WIFEXITED(*status) && !WIFSIGNALED(*status))
			continue ;
		else
			break ;
	}
}

int		launch(char **args, char **env)
{
	pid_t	pid;
	int		status;
	char	**copy_args;

	copy_args = copy_arr_str(args, (size_t)len_arr_str(args));
	pid = fork();
	if (pid == 0)
	{
		if (search_exec(copy_args, env) == -1)
			ft_print_error("minishell: ", *copy_args, ERR_PD);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		ft_print_error("minishell: ", "Error forking", ERR_ERROR);
	else
		make_wake(pid, &status);
	del_arr_str(copy_args);
	return (1);
}

int		ft_strequ_case_insen(char const *s1, char const *s2)
{
	if (s1 && s2)
	{
		while (ft_tolower(*s1) == ft_tolower(*s2))
		{
			if (*s1 == '\0' && *s2 == '\0')
				return (1);
			s1++;
			s2++;
		}
	}
	return (0);
}
