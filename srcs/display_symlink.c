/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_symlink.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knaumov <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 13:14:06 by knaumov           #+#    #+#             */
/*   Updated: 2018/10/08 15:38:16 by knaumov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node				*find_symlink(t_node *path, t_node *symlink_list)
{
	char *str;
	char *real_name;

	str = getting_full_symlink(path->name, path->name);
	real_name = ft_strjoin(path->name, str);
	if (ft_strcmp(str, " ") != 0)
		free(str);
	symlink_list = node_add(symlink_list, real_name, path->buf);
	free(real_name);
	return (symlink_list);
}

void				display_symlink(t_node *path, t_flags *flags)
{
	t_node			*symlink_list;
	t_node			**beginlist;
	t_node			*begining;

	beginlist = &symlink_list;
	symlink_list = NULL;
	begining = path;
	flags->entity_fill = 1;
	while (path)
	{
		if (lstat(path->name, &path->buf) != -1)
			if ((path->buf.st_mode & S_IFLNK) == S_IFLNK && flags->flag_l == 1)
				symlink_list = find_symlink(path, symlink_list);
		path = path->next;
	}
	ft_list_clean(&path);
	path = begining;
	display_entity(path, symlink_list, flags);
	ft_list_clean(beginlist);
}
