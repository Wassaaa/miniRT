/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:40:48 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 13:40:49 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char *set)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_strchr(set, s[i]))
			i++;
		if (s[i])
			word++;
		while (s[i] && !ft_strchr(set, s[i]))
			i++;
	}
	return (word);
}

static void	free_ptr(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
}

static char	**split(char const *s, char *set, char **ptr)
{
	int	i;
	int	j;

	j = 0;
	while (*s)
	{
		while (*s && ft_strchr(set, *s))
			s++;
		if (*s)
		{
			i = 0;
			while (*(s + i) && !ft_strchr(set, *(s + i)))
				i++;
			ptr[j] = malloc(sizeof(char) * (i + 1));
			if (!ptr[j])
			{
				free_ptr(ptr, j);
				return (NULL);
			}
			ft_strlcpy(ptr[j++], s, i + 1);
			s += i;
		}
	}
	ptr[j] = 0;
	return (ptr);
}

/**
 * Allocates (with malloc(3)) and returns an array
 * of strings obtained by splitting ’s’ using the
 * character ’c’ as a delimiter. The array must end
 * with a NULL pointer.
 * @param s - The string to be split.
 * @param set - The delimiter character set.
 */
char	**ft_split_new(char const *s, char *set)
{
	char	**ptr;

	ptr = malloc(sizeof(char *) * (count_words(s, set) + 1));
	if (!ptr)
		return (NULL);
	ptr = split(s, set, ptr);
	return (ptr);
}
