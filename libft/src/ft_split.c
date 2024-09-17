/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:44:57 by luibarbo          #+#    #+#             */
/*   Updated: 2024/06/06 16:20:13 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	*ft_strndup(char *s, size_t n)
{
	char	*s2;
	size_t	i;

	s2 = (char *)malloc(sizeof(char) * n + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	**free_tab(char **tab, int k)
{
	while (k >= 0)
		free (tab[k--]);
	free (tab);
	return (NULL);
}

static char	**split(char const *s, char c, char **tab, size_t words)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (k < words)
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
			tab[k] = ft_strndup((char *)s + j, i - j);
		if (tab[k] == NULL)
			return (free_tab(tab, k));
		k++;
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		words;

	words = ft_count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	tab = split(s, c, tab, words);
	return (tab);
}
