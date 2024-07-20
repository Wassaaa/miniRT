/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:43:44 by jtu               #+#    #+#             */
/*   Updated: 2024/04/05 09:13:10 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocates (with malloc(3)) and returns a copy of
 * ’s1’ with the characters specified in ’set’ removed
 * from the beginning and the end of the string.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_trim;
	int		start;
	int		end;
	int		len;
	int		i;

	len = ft_strlen(s1);
	start = 0;
	end = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end < len - start && ft_strchr(set, s1[len - end - 1]))
		end++;
	s1_trim = malloc((len - start - end + 1) * sizeof(char));
	if (!s1_trim)
		return (NULL);
	i = 0;
	while (i < len - start - end)
	{
		s1_trim[i] = s1[i + start];
		i++;
	}
	s1_trim[i] = '\0';
	return (s1_trim);
}
