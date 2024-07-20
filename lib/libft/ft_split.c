/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:42:12 by jtu               #+#    #+#             */
/*   Updated: 2024/01/25 18:40:08 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			word++;
		while (s[i] && s[i] != c)
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

static char	**split(char const *s, char c, char **ptr)
{
	int	i;
	int	j;

	j = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			i = 0;
			while (*(s + i) && *(s + i) != c)
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
 * @param c - The delimiter character.
 */
char	**ft_split(char const *s, char c)
{
	char	**ptr;

	ptr = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!ptr)
		return (NULL);
	ptr = split(s, c, ptr);
	return (ptr);
}
