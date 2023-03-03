/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lizhang <lizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 21:37:43 by lizhang       #+#    #+#                 */
/*   Updated: 2021/11/02 23:22:31 by lizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t	words;
	size_t	count;

	words = 1;
	count = 0;
	while (s[count])
	{
		if (s[count] != c && (!s[count + 1] || s[count + 1] == c))
			words++;
		count++;
	}
	return (words);
}

static size_t	ft_countchar(char const *s, char c, size_t start)
{
	size_t	wlen;

	wlen = 1;
	while (s[start] && s[start] != c)
	{
		start++;
		wlen++;
	}
	return (wlen);
}

static void	ft_cponeword(char *dst, char const *s, size_t start, size_t wlen)
{
	size_t	ccount;

	ccount = 0;
	while (ccount < wlen - 1)
	{
		dst[ccount] = s[start];
		start++;
		ccount++;
	}
}

static void	ft_cpwords(char const *s, char c, char **dst, size_t words)
{
	size_t	sccount;
	size_t	wcount;
	size_t	wlen;

	wcount = 0;
	sccount = 0;
	while (wcount < words - 1)
	{
		while (s[sccount] && s[sccount] == c)
			sccount++;
		wlen = ft_countchar(s, c, sccount);
		dst[wcount] = ft_calloc(wlen, sizeof(char));
		if (!dst[wcount])
		{
			while (wcount-- > 1)
			{
				free (dst[wcount]);
				dst[wcount] = NULL;
			}
			return ;
		}
		ft_cponeword(dst[wcount], s, sccount, wlen);
		sccount = sccount + wlen;
		wcount++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	words;

	if (!s || (s[0] == 0 && c == 0))
	{
		dst = malloc(sizeof(char *));
		if (!dst)
			return (NULL);
		dst[0] = NULL;
		return (dst);
	}
	words = ft_countwords(s, c);
	dst = malloc(sizeof(char *) * (words));
	if (!dst)
		return (NULL);
	ft_cpwords(s, c, dst, words);
	if (dst[0] == NULL)
	{
		free (dst);
		return (NULL);
	}
	dst[words - 1] = NULL;
	return (dst);
}
