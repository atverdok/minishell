/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 17:41:28 by atverdok          #+#    #+#             */
/*   Updated: 2017/05/27 17:41:35 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_arr_str(char **env, size_t size)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	while (env[i] != NULL)
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	return (tmp);
}

void	del_arr_str(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int		len_arr_str(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i] != NULL)
		i++;
	return (i);
}

void	*ft_realoc(void *ptr, size_t size)
{
	char *new;

	if (!size)
		ft_memdel(&ptr);
	if (ptr)
	{
		new = ft_memalloc(sizeof(char) * size);
		ft_memcpy(new, ptr, size);
		ft_memdel(&ptr);
		return (new);
	}
	return (ptr);
}

int		hangling_dquote(int *f_q_dq, int c)
{
	if (c == '"' && !IS_QUOTE(*f_q_dq))
	{
		*f_q_dq = (*f_q_dq ^ (1 << 2));
		*f_q_dq = (*f_q_dq ^ (1 << 0));
		return (1);
	}
	else if (c == '\'' && !IS_DQUOTE(*f_q_dq))
	{
		*f_q_dq = (*f_q_dq ^ (1 << 1));
		*f_q_dq = (*f_q_dq ^ (1 << 0));
		return (1);
	}
	return (0);
}
