/*
** EPITECH PROJECT, 2020
** nm
** File description:
** file.h
*/

#ifndef NM_FILE_H
#define NM_FILE_H

#include <stdbool.h>

enum ARCH { ARCH_UNKNOWN, ARCH_32, ARCH_64 };

bool file_is_elf(const char *buffer);
enum ARCH file_get_arch(const char *buffer);

#endif  // NM_FILE_H
