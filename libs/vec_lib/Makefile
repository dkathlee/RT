NAME = lib/vec_lib.a

SRCDIR = srcs/
INCDIR = includes/
OBJDIR = obj/
LIBDIR = lib/

SRCS =	vec3_add.c \
		vec3_cross.c \
		vec3_mod.c \
		vec3_mul.c \
		vec3_mul_n.c \
		vec3_scalar.c \
		vec3_sub.c \
		vec4_add.c \
		vec4_cross.c \
		vec4_mod.c \
		vec4_mul.c \
		vec4_mul_n.c \
		vec4_scalar.c \
		vec4_sub.c

OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

CC = gcc -g -Wall -Wextra -Werror

all: $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) -I $(INCDIR) $(CFLAGS) -o $@ -c $<

$(NAME): obj $(OBJS)
	mkdir -p $(LIBDIR)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re:	fclean all
