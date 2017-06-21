/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_search_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 17:45:44 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/27 17:45:50 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			is_local_file_dir(char *arg, struct stat *stat_f)
{
	char *full_path;

	if (ft_strchr(arg, '/') == NULL)
		return (0);
	full_path = ft_strdup(arg);
	if (lstat(full_path, stat_f))
	{
		ft_strdel(&full_path);
		full_path = get_full_path_lokal(arg);
		if (!lstat(full_path, stat_f) && stat_f->st_dev)
		{
			ft_strdel(&full_path);
			return (1);
		}
	}
	else
	{
		ft_strdel(&full_path);
		return (1);
	}
	ft_strdel(&full_path);
	return (0);
}

static char	*get_path(char *path, char *arg)
{
	char *full_path;

	full_path = ft_strnew(ft_strlen(path) + ft_strlen(arg) + 1);
	full_path = ft_strcpy(full_path, path);
	full_path = ft_strcat(full_path, "/");
	full_path = ft_strcat(full_path, arg);
	return (full_path);
}

int			is_path_file(char *arg, struct stat *stat_f, char **env)
{
	char *env_path;
	char *path;
	char *full_path;

	if (env && (ft_getenv("PATH", env) != NULL))
	{
		env_path = ft_strdup(ft_getenv("PATH", env));
		path = ft_strtok_quote(env_path, ":");
		while (path != NULL)
		{
			full_path = get_path(path, arg);
			if (lstat(full_path, stat_f))
				path = ft_strtok_quote(NULL, ":");
			else
			{
				ft_strdel(&full_path);
				ft_strdel(&env_path);
				return (1);
			}
			ft_strdel(&full_path);
		}
		ft_strdel(&env_path);
	}
	return (0);
}

static int	print_error_file_or_directory(char *arg)
{
	if (ft_strchr(arg, '/'))
		ft_print_error("minishell: ", arg, ERR_NSFOD);
	else
		ft_print_error("minishell: ", arg, ERR_CNF);
	return (1);
}

int			is_file_or_directory(char *arg, char **env)
{
	struct stat stat_f;

	ft_bzero(&stat_f, sizeof(stat_f));
	if (!is_local_file_dir(arg, &stat_f))
		is_path_file(arg, &stat_f, env);
	if (stat_f.st_dev)
	{
		if (!(stat_f.st_mode & (1 << 2))
				&& ((stat_f.st_mode & S_IFMT) == S_IFDIR
					|| (stat_f.st_mode & S_IFMT) == S_IFLNK))
		{
			ft_print_error("minishell: ", arg, ERR_PD);
			return (1);
		}
		else if (((stat_f.st_mode & S_IFMT) == S_IFREG)
				&& (!(stat_f.st_mode & (1 << 0)
						|| !(stat_f.st_mode & (1 << 3)
							|| !(stat_f.st_mode & (1 << 6))))))
		{
			ft_print_error("minishell: ", arg, ERR_PD);
			return (1);
		}
		return (0);
	}
	return (print_error_file_or_directory(arg));
}
