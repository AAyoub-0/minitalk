/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:15:13 by aboumall          #+#    #+#             */
/*   Updated: 2025/01/15 13:15:57 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static size_t	str_size(char const *s, char c)
{
	size_t	i;
	char	*pstr;

	pstr = (char *)s;
	i = 0;
	c = (unsigned char)c;
	while ((unsigned char)pstr[i] != c && pstr[i])
		i++;
	return (i);
}

static size_t	count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	sep;

	i = 0;
	count = 0;
	sep = 0;
	if (s[0] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		if (s[i] == c)
			sep++;
		i++;
	}
	if (count == 0 && s[i] == '\0' && sep != i)
		count = 1;
	return (count);
}

static size_t	get_word_index(char const *s, char c, size_t i)
{
	size_t	j;
	size_t	count;

	j = 0;
	count = 0;
	while (s[j])
	{
		while (s[j] != c && s[j])
		{
			if (s[j + 1] == c || s[j + 1] == '\0')
				count++;
			j++;
		}
		if (count == i)
		{
			while (j > 0 && s[j - 1] != c)
				j--;
			return (j);
		}
		j++;
	}
	return (0);
}

static void	free_array(char **strs, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	word_count;
	char	**strs;

	i = 0;
	word_count = count_word(s, c);
	strs = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (i < word_count)
	{
		strs[i] = (char *)malloc(str_size(s + get_word_index(s, c, i + 1), c)
				+ 1);
		if (!strs[i])
		{
			free_array(strs, i);
			return (NULL);
		}
		ft_strlcpy(strs[i], s + get_word_index(s, c, i + 1), str_size(s
				+ get_word_index(s, c, i + 1), c) + 1);
		i++;
	}
	strs[word_count] = NULL;
	return (strs);
}
