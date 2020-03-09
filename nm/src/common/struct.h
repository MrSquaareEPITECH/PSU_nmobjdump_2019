/*
** EPITECH PROJECT, 2020
** nm
** File description:
** struct.h
*/

#ifndef NM_STRUCT_H
#define NM_STRUCT_H

#define SYM_TYPE_UNKNOWN ('?')
#define SYM_TYPE_WEAK ('W')
#define SYM_TYPE_WEAK_OBJECT ('V')

typedef struct symbol_sec_name_type_s {
    char type;
    char *name;
} symbol_sec_name_type_t;

typedef struct symbol_sec_flags_type_s {
    char type;
    unsigned long flags;
} symbol_sec_mask_type_t;

typedef struct symbol_shndx_type_s {
    char type;
    unsigned short shndx;
} symbol_shndx_type_t;

extern const symbol_shndx_type_t SYM_SHNDX_TYPES[];
extern const symbol_sec_name_type_t SYM_SEC_NAME_TYPES[];
extern const symbol_sec_mask_type_t SYM_SEC_FLAGS_TYPES[];

#endif // NM_STRUCT_H
