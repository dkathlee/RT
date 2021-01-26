NAME = RT

SRCDIR					= srcs/
INCDIR					= includes/
OBJDIR					= obj/
LIBSDIR					= libs/
VULKAN_INCLUDE_PATH 	= libs/vulkan/includes/
JSON_LIB_PATH			= libs/cJSON/

SHADER_COMPILER = libs/vulkan/glslangValidator
GLSLS = $(wildcard shaders/*.vert shaders/*.frag)
SPIRVS = $(addsuffix .spv,$(GLSLS))

SRCS =	app_core.c \
		input.c \
		lights_parser.c \
		main.c \
		objects_parser_2.c \
		objects_parser.c \
		rotation.c \
		scene_reader_json.c \
		shader_reader.c \
		textures.c \
		utils.c \
		vku_buffers.c \
		vku_commandbuffers.c \
		vku_descriptors.c \
		vku_drawframe.c \
		vku_framebuffer.c \
		vku_instance.c \
		vku_logical_device.c \
		vku_physical_device.c \
		vku_pipeline.c \
		vku_pipeline_states_creation.c \
		vku_render.c \
		vku_renderpass.c \
		vku_shadermodule.c \
		vku_swapchain.c \
		vku_window.c

OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

VULKANINC = -I $(VULKAN_INCLUDE_PATH)

JSONINC = -I $(JSON_LIB_PATH)
JSONLIB =  $(addprefix $(JSON_LIB_PATH), libjson.a)

SDL2LINK = -l SDL2
SDL2INC = -I $(addprefix $(LIBSDIR), SDL2/includes/)
SDL2LINK_win = -L $(addprefix $(LIBSDIR), SDL2/lib/) -l SDL2 -l SDL2_image

VECLIB =  $(addprefix $(LIBSDIR), vec_lib/lib/vec_lib.a)
VECINC =  $(addprefix $(LIBSDIR), vec_lib/includes)
VECLIBINC = -I $(VECINC)

FTLIB =  $(addprefix $(LIBSDIR), printf/libftprintf.a)
FTINCDIR =  $(addprefix $(LIBSDIR), printf/includes)
FTINC = -I $(FTINCDIR)

all: $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(FTINC) $(JSONINC) $(VECLIBINC) -I $(INCDIR) $(VULKANINC) $(SDL2INC) -o $@ -c $<

$(NAME): libs obj $(OBJS) shaders
	$(CC) $(OBJS) $(VECLIB) $(FTLIB) $(JSONLIB) -F libs/SDL2/lib -framework SDL2 -framework SDL2_image -L libs/vulkan/macOS/lib -l vulkan.1.2.148 -l vulkan.1 -l vulkan -lm -o $(NAME)
	install_name_tool -change @rpath/libvulkan.1.dylib libs/vulkan/macOS/lib/libvulkan.1.dylib $(NAME)
	install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image libs/SDL2/lib/SDL2_image.framework/Versions/A/SDL2_image $(NAME)
	install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 libs/SDL2/lib/SDL2.framework/Versions/A/SDL2 $(NAME)

clean:
	rm -rf $(OBJDIR)
	rm -f $(SPIRVS)

fclean: clean
	make -C libs/printf fclean
	make -C libs/cJSON fclean
	make -C libs/vec_lib fclean
	rm -rf $(NAME)
	rm -rf SDL2.dll
	rm -rf SDL2_image.dll
	rm -rf libjpeg-9.dll
	rm -rf libpng16-16.dll

re: fclean all

libs:
	@make -C libs/printf
	@make -C libs/vec_lib
	@make -C libs/cJSON

shaders: $(SPIRVS)

$(SPIRVS): %.spv: %
	$(SHADER_COMPILER) -V $< -o $@

.PHONY: clean fclean all re windows libs
