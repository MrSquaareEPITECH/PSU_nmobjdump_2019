/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** objdump_32.h
*/

#ifndef OBJDUMP_OBJDUMP_32_H
#define OBJDUMP_OBJDUMP_32_H

#include <elf.h>

int objdump_32(const char *path, const Elf32_Ehdr *elf_hdr);

#endif // OBJDUMP_OBJDUMP_32_H
