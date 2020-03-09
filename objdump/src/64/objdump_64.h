/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** objdump_64.h
*/

#ifndef OBJDUMP_OBJDUMP_64_H
#define OBJDUMP_OBJDUMP_64_H

#include <elf.h>

int objdump_64(const char *path, const Elf64_Ehdr *elf_hdr);

#endif // OBJDUMP_OBJDUMP_64_H
