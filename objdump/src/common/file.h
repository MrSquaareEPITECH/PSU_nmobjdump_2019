/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** file.h
*/

#ifndef OBJDUMP_FILE_H
#define OBJDUMP_FILE_H

#include <stdbool.h>

typedef enum ARCH arch_t;

enum ARCH { ARCH_UNKNOWN, ARCH_32, ARCH_64 };

bool file_is_elf(const char *buffer);
arch_t file_get_arch(const char *buffer);

#endif  // OBJDUMP_FILE_H
