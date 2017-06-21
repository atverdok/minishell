/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 14:59:53 by atverdok          #+#    #+#             */
/*   Updated: 2017/06/21 14:59:59 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				add_to_history(char ***history_buf, char *buf, int *i)
{
	if ((*history_buf)[29] != NULL)
		ft_strdel(history_buf[29]);
	ft_memmove(((*history_buf) + 1), (*history_buf), (29 * sizeof(char *)));
	*history_buf[0] = buf;
	*i = -1;
	return (1);
}

void			init_tmp_buf(char **tmp_buf, char *buf, int key)
{
	if (*tmp_buf == NULL && key != 1)
	{
		*tmp_buf = ft_memalloc(sizeof(char) * (MAX_INPUT + 1));
		ft_memcpy(*tmp_buf, buf, MAX_INPUT);
	}
}

char			*history(char *buf, int key)
{
	static char	**history_buf = NULL;
	static char	*tmp_buf = NULL;
	int			len;
	static int	i = -1;

	len = len_arr_str(history_buf);
	init_tmp_buf(&tmp_buf, buf, key);
	if (history_buf == NULL)
		history_buf = (char **)ft_memalloc(sizeof(char *) * 30);
	if (key == 1 && ft_strlen(buf) && add_to_history(&history_buf, buf, &i))
		return (buf);
	if (key == KEY_UP && i < (len - 1) && i < 29)
		i++;
	else if (key == KEY_DOWN && i >= 0)
		i--;
	if (i >= 0 && history_buf[i])
		return (history_buf[i]);
	else
	{
		buf = tmp_buf;
		ft_strdel(&tmp_buf);
		tmp_buf = NULL;
		i = -1;
		return (buf);
	}
}
