#include "get_next_line.h"

void	freestr(char **str)
{
	if (str || *str)
	{
		free(*str);
		*str = NULL;
	}
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	index;

	index = 0;
	while (index < len)
	{
		((unsigned char *)b)[index] = c;
		index++;
	}
	return (b);
}

char	*ft_calloc(size_t count, size_t size)
{
	void	*heap;
	size_t	total_size;

	total_size = count * size;
	heap = (char *)malloc(total_size);
	if (!heap)
		return (NULL);
	ft_memset(heap, 0, total_size);
	return (heap);
}

char	*get_good(char **str, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
	{
		*line = ft_substr(*str, 0, i + 1);
		temp = ft_strdup(&((*str)[i + 1]));
		freestr(str);
		*str = temp;
		return (*line);
	}
	else if ((*str)[i] == '\0' && i > 0)
	{
		*line = ft_strdup(*str);
		freestr(str);
		return (*line);
	}
	freestr(str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	int			reader;
	char		buffer[BUFFER_SIZE + 1];
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reader = 1;
	while (!(ft_strchr_gnl(str, '\n')) && reader > 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader < 0)
			return (NULL);
		if (!str)
			str = ft_calloc(1, 1);
		buffer[reader] = '\0';
		temp = ft_strjoin(str, buffer);
		freestr(&str);
		str = temp;
	}
	return (get_good(&str, &line));
}
