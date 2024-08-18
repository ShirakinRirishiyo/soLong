/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:27:15 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/06/19 11:35:56 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Función auxiliar para encontrar el primer salto de línea en una cadena
char *ft_strchr_gnl(const char *s, int c) {
    while (*s) {
        if (*s == (char)c) {
            return (char *)s;
        }
        s++;
    }
    return NULL;
}

// Función auxiliar para concatenar dos cadenas
char *strjoin_and_free(char *s1, const char *s2) {
    char *result;
    size_t len1, len2;

    if (!s1) {
        s1 = malloc(1);
        if (!s1)
            return NULL;
        *s1 = '\0';
    }
    len1 = strlen(s1);
    len2 = strlen(s2);
    result = malloc(len1 + len2 + 1);
    if (!result)
        return NULL;
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    free(s1);
    return result;
}

// Función auxiliar para duplicar una cadena
char *ft_strdup_gnl(const char *s) {
    size_t len = ft_strlen(s);
    char *dup = malloc(len + 1);
    if (!dup)
        return NULL;
   ft_memcpy(dup, s, len + 1);
    return dup;
}

// Función auxiliar para copiar una cadena
void ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize) {
    size_t i;

    if (dstsize == 0)
        return;
    i = 0;
    while (src[i] && i < dstsize - 1) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

// Procesa la línea de la cadena del buffer
char *process_line(const char *buffer, int length) {
    char *line;

    line = malloc(length + 1);
    if (!line)
        return NULL;
    ft_strlcpy_gnl(line, buffer, length + 1);
    return line;
}

// Lee del archivo y añade el contenido al resultado
ssize_t read_and_append(int fd, char **result, char *buffer) {
    ssize_t bytes_read;

    bytes_read = 1;
    while (bytes_read > 0 && !ft_strchr_gnl(*result, '\n')) {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
            return -1;
        buffer[bytes_read] = '\0';
        *result = strjoin_and_free(*result, buffer);
    }
    return bytes_read;
}

// Procesa y actualiza el resultado
char *process_and_update(char **result, ssize_t line_length) {
    char *line;
    char *remaining;

    line = process_line(*result, line_length);
    if (!line)
        return (free(*result), NULL);
    remaining = ft_strdup_gnl(*result + line_length);
    free(*result);
    *result = remaining;
    return line;
}

// Obtiene la siguiente línea del archivo
char *get_next_line(int fd) {
    static char *result;
    char *line;
    char *buffer;
    ssize_t read_result;

    if (BUFFER_SIZE <= 0 || fd < 0)
        return NULL;
    if (!result)
        result = ft_strdup_gnl("");
    buffer = (char *)malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return NULL;
    read_result = read_and_append(fd, &result, buffer);
    free(buffer);
    if (read_result < 0 || !*result) {
        free(result);
        result = NULL;
        return NULL;
    }
    if (!ft_strchr_gnl(result, '\n')) {
        line = ft_strdup_gnl(result);
        free(result);
        result = NULL;
        return line;
    }
    read_result = ft_strchr_gnl(result, '\n') - result + 1;
    line = process_and_update(&result, read_result);
    return line;
}
