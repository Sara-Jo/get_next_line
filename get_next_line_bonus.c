/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:24:49 by sjo               #+#    #+#             */
/*   Updated: 2022/01/03 14:33:05 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_save(char *save)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    // line 길이 구하기
    while (save[i] && save[i] != '\n')
        i++;
    if (!save[i])
    {
        free(save);
        return (NULL);
    }
    // (save 길이 - line 길이 + 1) 만큼 메모리 할당
    tmp = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
    if (!tmp)
        return (NULL);
    i++;
    j = 0;
    // save 에서 line 이후의 문자열 담기
    while (save[i])
        tmp[j++] = save[i++];
    tmp[j] = '\0';
    free(save);
    return (tmp);
}

char *ft_get_line(char *save)
{
    int i;
    char *tmp;

    i = 0;
    if (!save[i])
        return (NULL);
    // 개행문자 전까지의 길이 구하기
    while (save[i] && save[i] != '\n')
        i++;
    // (길이 + 2) 만큼 메모리 할당
    tmp = (char *)malloc(sizeof(char) * (i + 2));
    if (!tmp)
        return (NULL);
    i = 0;
    // 개행문자 전까지의 문자열 담기
    while (save[i] && save[i] != '\n')
    {
        tmp[i] = save[i];
        i++;
    }
    if (save[i] == '\n')
	{
		tmp[i] = save[i];
		i++;
	}
    tmp[i] = '\0';
    return (tmp);
}

char *ft_read(int fd, char *save)
{
    char *buff;
    ssize_t return_bytes;

    // 읽어들인 문자열을 담을 buff 메모리 할당
    buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buff)
        return (NULL);
    return_bytes = 1;
    
    // 개행문자를 만나거나 파일의 맨 끝에 도착할때까지 반복
    while (!ft_strchr(save, '\n') && return_bytes != 0)
    {
        // BUFFER_SIZE 만큼 읽어서 buff 에 저장
        return_bytes = read(fd, buff, BUFFER_SIZE);
        // 읽어들이는 중에 에러가 발생하면 buff를 free하고 종료
        if (return_bytes == -1)
        {
            free(buff);
            return (NULL);
        }
        // buff 의 맨끝에 널문자 넣기
        buff[return_bytes] = '\0';
        // save 뒤에 buff 붙이기
        save = ft_strjoin(save, buff);
    }
    free(buff);
    return (save);
}

char *get_next_line(int fd)
{
    static char *save[257];
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
        return (0);
    // 개행문자를 만나거나 파일의 맨 끝에 도착할때까지 읽어들여서 save 에 저장
    save[fd] = ft_read(fd, save[fd]);
    if (!save[fd])
        return (NULL);
    // 개행문자 전까지의 문자열을 line 에 저장
    line = ft_get_line(save[fd]);
    // save 에 line 이후의 문자열만 남기기
    save[fd] = ft_save(save[fd]);
    return (line);
}