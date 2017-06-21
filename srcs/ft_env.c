/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 10:53:52 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/26 12:49:39 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		handling_u(char **args, int *i, char **env)
{
	if (ft_strchr(args[*i + 1], '=') && args[*i + 2]
			&& ft_strncmp(args[*i + 2], "-", 1))
	{
		ft_print_error("ft_env: ", "unsetenv ", ERR_TMA);
		del_arr_str(env);
		return (1);
	}
	else
	{
		ft_unsetenv(args[*i + 1], env);
		(*i)++;
	}
	return (0);
}

int		handling_param(char **args, int *i, char ***env)
{
	while (args[*i] && args[*i][0] == '-')
	{
		if (!ft_strcmp(args[*i], "-i"))
		{
			del_arr_str(*env);
			*env = (char **)ft_memalloc(sizeof(char *) * (BUF_SIZE + 1));
		}
		else if (!ft_strcmp(args[*i], "-u")
				&& args[*i + 1]
				&& ft_strncmp(args[*i + 1], "-", 1))
		{
			if (handling_u(args, i, *env))
				return (1);
		}
		else
		{
			ft_print_error("ft_env: ", args[*i], ERR_ILLOP);
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int		handling_equal(char **args, int *i, char **env)
{
	char	*arg_ptr;

	arg_ptr = NULL;
	while (args[*i]
			&& ((args[*i][0] != '=' || !ft_strcmp(args[*i], "="))
				&& ((arg_ptr = ft_strrchr(args[*i], '=')) != NULL)))
	{
		*arg_ptr = '\0';
		arg_ptr++;
		if (ft_setenv(args[*i], arg_ptr, 1, env))
			return (1);
		(*i)++;
	}
	return (0);
}

int		ft_env(char **args, char **env)
{
	int		i;
	char	**env_cop;

	if (args[1] == NULL)
	{
		print_env(env);
		return (0);
	}
	i = 1;
	env_cop = copy_arr_str(env, BUF_ENV);
	if (handling_param(args, &i, &env_cop) || handling_equal(args, &i, env_cop))
	{
		del_arr_str(env_cop);
		return (0);
	}
	if (args[i] == NULL)
		print_env(env_cop);
	else
	{
		if ((**(args + i)) == '=')
			ft_memmove(*(args + i), (*(args + i) + 1), ft_strlen(*(args + i)));
		execute((args + i), env_cop);
	}
	del_arr_str(env_cop);
	return (0);
}
