/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:37:29 by aboumall          #+#    #+#             */
/*   Updated: 2025/01/15 13:15:57 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	is_in_set(char c_s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (c_s1 == set[i++])
			return (1);
	return (0);
}

static size_t	trimed_len(char const *s1, char const *set, size_t *start,
		size_t *end)
{
	*start = 0;
	*end = ft_strlen(s1) - 1;
	while (s1[*start] && is_in_set(s1[*start], set))
		*start += 1;
	if (s1[*start] == '\0')
		return (0);
	while (is_in_set(s1[*end], set))
		*end -= 1;
	if (*start == *end)
		return (1);
	return (*end - *start);
}

static char	*strcpy_trim(char *dst, char const *s1, size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while (s1[start] && start <= end)
	{
		dst[i] = s1[start];
		start++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	size;
	size_t	start;
	size_t	end;

	size = trimed_len(s1, set, &start, &end) + 1;
	if (size == 1)
		return (ft_strdup("\0"));
	if (start == end)
		size = 1;
	trim = (char *)malloc((size + 1) * sizeof(char));
	if (!trim)
		return (NULL);
	trim = strcpy_trim(trim, s1, start, end);
	return (trim);
}
