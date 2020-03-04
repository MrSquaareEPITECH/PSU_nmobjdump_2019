/*
** EPITECH PROJECT, 2020
** nm
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

#include "32/nm_32.h"
#include "64/nm_64.h"
#include "common/def.h"
#include "common/file.h"

int buffer_errors(char *path, char *buffer)
{
    if (file_is_elf(buffer) == false) {
        fprintf(stderr, "nm: %s: file format not recognized\n", path);

        return (FAILURE);
    }

    if (file_get_arch(buffer) == ARCH_UNKNOWN) {
        fprintf(stderr, "nm: %s: file arch not recognized\n", path);

        return (FAILURE);
    }

    return (SUCCESS);
}

int buffer_load(char *path, char **buffer, unsigned long *size)
{
    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        fprintf(stderr, "nm: '%s': %s\n", path, strerror(errno));
        return (FAILURE);
    }

    struct stat stat;
    int fs = fstat(fd, &stat);

    if (fs == -1) {
        fprintf(stderr, "nm: '%s': %s\n", path, strerror(errno));
        return (FAILURE);
    }

    *buffer = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    *size = stat.st_size;

    if (buffer == MAP_FAILED) {
        fprintf(stderr, "nm: '%s': %s\n", path, strerror(errno));
        return (FAILURE);
    }

    close(fd);

    return (SUCCESS);
}

int main(int argc, char **argv)
{
    char *argv_default[] = {argv[0], "a.out"};
    int rcode = 0;

    if (argc < 2) {
        argc = 2;
        argv = argv_default;
    }

    for (int i = 1; i < argc; ++i) {
        char *buffer = NULL;
        unsigned long size = 0;

        if (buffer_load(argv[i], &buffer, &size)) {
            rcode = FAILURE;

            continue;
        }

        if (buffer_errors(argv[i], buffer)) {
            rcode = FAILURE;

            munmap(buffer, size);

            continue;
        }

        enum ARCH arch = file_get_arch(buffer);

        if (argc > 2) {
            if (i > 1) printf("\n");
            printf("%s:\n", argv[i]);
        }

        if (arch == ARCH_32)
            nm_32(argv[i], (Elf32_Ehdr *)(buffer));
        else if (arch == ARCH_64)
            nm_64(argv[i], (Elf64_Ehdr *)(buffer));

        munmap(buffer, size);
    }

    return rcode;
}