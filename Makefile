##
## EPITECH PROJECT, 2019
## PSU_nmobjdump_2019
## File description:
## Makefile
##

NM_NAME				=		my_nm
OBJDUMP_NAME		=		my_objdump

NM_DIR				=		nm
OBJDUMP_DIR			=		objdump

RM					=		rm -rf

MAKEFLAGS			+=		--silent

all:				nm objdump

nm:
					cd $(NM_DIR) && $(MAKE) all
					mv $(NM_DIR)/$(NM_NAME) $(NM_NAME)

objdump:
					cd $(OBJDUMP_DIR) && $(MAKE) all
					mv $(OBJDUMP_DIR)/$(OBJDUMP_NAME) $(OBJDUMP_NAME)

clean:
					cd $(NM_DIR) && $(MAKE) clean
					cd $(OBJDUMP_DIR) && $(MAKE) clean

fclean:				clean
					cd $(NM_DIR) && $(MAKE) fclean
					$(RM) $(NM_NAME)
					cd $(OBJDUMP_DIR) && $(MAKE) fclean
					$(RM) $(OBJDUMP_NAME)

re:					fclean all

sweet:				all clean

debug:
					cd $(NM_DIR) && $(MAKE) debug
					cd $(OBJDUMP_DIR) && $(MAKE) debug

debug_re:
					cd $(NM_DIR) && $(MAKE) debug_re
					cd $(OBJDUMP_DIR) && $(MAKE) debug_re

debug_sweet:
					cd $(NM_DIR) && $(MAKE) debug_sweet
					cd $(OBJDUMP_DIR) && $(MAKE) debug_sweet

tests_run:
					cd $(NM_DIR) && $(MAKE) tests_run
					cd $(OBJDUMP_DIR) && $(MAKE) tests_run

tests_clean:		clean
					cd $(NM_DIR) && $(MAKE) tests_clean
					cd $(OBJDUMP_DIR) && $(MAKE) tests_clean

tests_fclean:		tests_clean
					cd $(NM_DIR) && $(MAKE) tests_fclean
					cd $(OBJDUMP_DIR) && $(MAKE) tests_fclean

tests_re:			tests_fclean tests_run

tests_sweet:		tests_run tests_clean

tests_sh:			re
					cd $(NM_DIR) && $(MAKE) tests_sh
					cd $(OBJDUMP_DIR) && $(MAKE) tests_sh

full:				all

full_clean:			clean tests_clean

full_fclean:		fclean tests_fclean

full_re:			full_fclean full

full_sweet:			full full_clean

.PHONY:				nm objdump all clean fclean re sweet								\
					debug debug_re debug_sweet											\
					tests_run tests_clean tests_fclean tests_re tests_sweet tests_sh	\
					full full_clean full_fclean full_re full_sweet						\
