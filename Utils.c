#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*s2;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (s2 == NULL)
		return (NULL);
	while (len > i && (int)start < ft_strlen(s))
	{
		s2[i] = s[start + i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

char	*ft_strdup(const char *s1)
{
	unsigned int	i;
	char			*s2;

	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if(s1 && s2)
	{

	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*finalstr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	finalstr = malloc(((ft_strlen(s1)) + (ft_strlen(s2))) + 1);
	if (!finalstr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
		finalstr[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		finalstr[i] = s2[j];
		i++;
		j++;
	}
	finalstr[i] = '\0';
	return (finalstr);
}

static int	words_counter(const char *str, char c)
{
	int	counter;
	int	breaker;

	counter = 0;
	breaker = 0;
	while (*str)
	{
		if (*str != c && breaker == 0)
		{
			counter++;
			breaker = 1;
		}
		else if (*str == c)
		{
			breaker = 0;
		}
		str++;
	}
	return (counter);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	int		start;
	int		i;
	int		j;

	split = malloc((words_counter(s, c) + 1) * sizeof(char *));
	if (!split || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i > 0)
		{
			split[j] = ft_substr(s, start, i - start);
			j++;
		}
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	split[j] = 0;
	return (split);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			i++;
			return ((char *)&s[i]);
		}
		else
			i++;
	}
	if ((char)c == 0)
		return (((char *)&s[i]));
	return (NULL);
}

int	ft_isalnum_v2(char n)
{
	if ((n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'z') ||
		(n >= '0' && n <= '9') || (n == '_') || (n == '='))
		return (1);
	else
		return (0);
}
