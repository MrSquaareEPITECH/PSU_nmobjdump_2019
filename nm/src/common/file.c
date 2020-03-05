/*
** EPITECH PROJECT, 2020
** nm
** File description:
** file.c
*/

#include "file.h"

#include <elf.h>

bool file_is_elf(const char *buffer)
{
    const unsigned char ELF_MAGIC[] = {0x7f, 'E', 'L', 'F'};

    for (int i = 0; i < 4; ++i)
        if (buffer[i] != ELF_MAGIC[i])
            return (false);
    return (true);
}

arch_t file_get_arch(const char *buffer)
{
    char arch = buffer[EI_CLASS];

    if (arch == ELFCLASS32)
        return (ARCH_32);
    if (arch == ELFCLASS64)
        return (ARCH_64);
    return (ARCH_UNKNOWN);
}