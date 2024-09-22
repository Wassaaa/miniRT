/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:18:16 by jtu               #+#    #+#             */
/*   Updated: 2024/08/28 20:25:47 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

bool	change_target(void)
{
	static const char	*tar_type_strings[] = {
	[PLANE] = "PLANE",
	[SPHERE] = "SPHERE",
	[CYLINDER] = "CYLINDER",
	[CONE] = "CONE",
	[LIGHT] = "LIGHT"
	};

	rtx()->ui[rtx()->target]->enabled = false;
	rtx()->target = (rtx()->target + 1) % SHAPE_NUM;
	while (!rtx()->ui[rtx()->target])
		rtx()->target = (rtx()->target + 1) % SHAPE_NUM;
	rtx()->ui[rtx()->target]->enabled = true;
	printf("\e[8;1HTARGET: [%s]\e[K\n", tar_type_strings[rtx()->target]);
	return (false);
}
