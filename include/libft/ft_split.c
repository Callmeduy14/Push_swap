/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:49:28 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/08 20:20:00 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	count;
	int	word;

	count = 0;
	word = 0;
	while (*s)
	{
		if (*s != c && !word)
		{
			word = 1;
			count++;
		}
		if (*s == c)
			word = 0;
		s++;
	}
	return (count);
}

static char	*extract_word(const char **s, char c)
{
	const char	*start;
	size_t		len;
	char		*word;

	start = *s;
	while (**s && **s != c)
		(*s)++;
	len = *s - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, start, len);
	word[len] = '\0';
	return (word);
}

static void	cleanup(char **result, int count)
{
	while (count-- > 0)
		free(result[count]);
	free(result);
}

static int	fill_result(char **result, const char *s, char c, int word_count)
{
	int	i;

	i = 0;
	while (*s && i < word_count)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			result[i] = extract_word(&s, c);
			if (!result[i])
				return (0);
			i++;
		}
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = count_word(s, c);
	result = (char **)malloc((word_count + 1) * sizeof (char *));
	if (!result)
		return (NULL);
	ft_bzero(result, (word_count + 1) * sizeof(char *));
	if (!fill_result(result, s, c, word_count))
	{
		cleanup(result, word_count);
		return (NULL);
	}
	return (result);
}
