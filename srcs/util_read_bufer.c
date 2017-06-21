/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_read_bufer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:04:36 by atverdok          #+#    #+#             */
/*   Updated: 2017/06/21 15:04:38 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			delite_char(char **buf, int *pos, size_t *len)
{
	ft_memmove((*buf + ((size_t)*pos - 1)), ((*buf + (size_t)*pos)),
			ft_strlen((*buf + (size_t)*pos)));
	(*len)--;
	(*pos)--;
	(*buf)[*len] = '\0';
	ft_putchar('\b');
	ft_putstr("\e[s");
	ft_putstr("\e[0K");
	ft_putstr((*buf + *pos));
	ft_putstr("\e[u");
}

void			insert_char(char **buf, int *pos, int c)
{
	ft_memmove((*buf + ((size_t)*pos + 1)), ((*buf + (size_t)*pos)),
			ft_strlen((*buf + (size_t)*pos)));
	(*buf)[*pos] = (char)c;
	ft_putstr("\e[s");
	ft_putstr((*buf + *pos));
	ft_putstr("\e[u");
	ft_putstr("\e[1C");
	(*pos)++;
}

int				add_to_buff(char **buf, int *pos, int c)
{
	size_t len;

	len = ft_strlen(*buf);
	if (c == '\n')
		return (1);
	else if ((size_t)*pos < len && c != 0x0000007f
			&& len < MAX_INPUT)
		insert_char(buf, pos, c);
	else if (c == 0x0000007f && *pos)
		delite_char(buf, pos, &len);
	else if ((size_t)*pos == len && c != 0x0000007f && len < MAX_INPUT)
	{
		(*buf)[*pos] = (char)c;
		(*pos)++;
		ft_putchar((char)c);
	}
	return (0);
}
