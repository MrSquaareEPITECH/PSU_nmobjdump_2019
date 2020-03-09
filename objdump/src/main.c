/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** main.c
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "32/objdump_32.h"
#include "64/objdump_64.h"
#include "common/def.h"
#include "common/file.h"

static int stat_load(const char *path, unsigned long *size, int fd)
{
    struct stat stat;

    if (fstat(fd, &stat) == -1) {
        fprintf(stderr, "objdump: '%s': %s\n", path, strerror(errno));
        return (FAILURE);
    }
    if (S_ISDIR(stat.st_mode)) {
        fprintf(stderr, "objdump: Warning: '%s' is a directory\n", path);
        return (FAILURE);
    }
    if (!S_ISREG(stat.st_mode)) {
        fprintf(
            stderr, "objdump: Warning: '%s' is not an ordinary file\n", path);
        return (FAILURE);
    }
    *size = stat.st_size;
    return (SUCCESS);
}

static int buffer_load(const char *path, char **buffer, unsigned long *size)
{
    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        fprintf(stderr, "objdump: '%s': No such file\n", path);
        return (FAILURE);
    }
    if (stat_load(path, size, fd))
        return (FAILURE);
    *buffer = mmap(NULL, *size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buffer == MAP_FAILED) {
        fprintf(stderr, "objdump: '%s': %s\n", path, strerror(errno));
        return (FAILURE);
    }
    close(fd);
    return (SUCCESS);
}

static int buffer_errors(const char *path, const char *buffer)
{
    if (file_is_elf(buffer) == false) {
        fprintf(stderr, "objdump: %s: file format not recognized\n", path);
        return (FAILURE);
    }
    if (file_get_arch(buffer) == ARCH_UNKNOWN) {
        fprintf(stderr, "objdump: %s: file arch not recognized\n", path);
        return (FAILURE);
    }
    return (SUCCESS);
}

static int run(const char *path)
{
    char *buffer = NULL;
    unsigned long size = 0;

    if (buffer_load(path, &buffer, &size))
        return (FAILURE);
    if (buffer_errors(path, buffer))
        return (FAILURE);

    arch_t arch = file_get_arch(buffer);
    int rcode = 0;

    if (arch == ARCH_32)
        rcode = objdump_32(path, (Elf32_Ehdr *)buffer);
    else if (arch == ARCH_64)
        rcode = objdump_64(path, (Elf64_Ehdr *)buffer);
    munmap(buffer, size);
    return (rcode);
}

int main(int argc, char **argv)
{
    char *argv_default[] = {argv[0], "a.out"};

    if (argc < 2) {
        argc = 2;
        argv = argv_default;
    }

    int rcode = 0;

    for (int i = 1; i < argc; ++i)
        if (run(argv[i]))
            rcode = FAILURE;

    return (rcode);
}