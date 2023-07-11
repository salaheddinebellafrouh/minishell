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
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
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
