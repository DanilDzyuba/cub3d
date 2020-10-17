cmake_minimum_required(VERSION 3.16)
project(cub3d C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -framework OpenGl -framework AppKit")

link_directories(${CMAKE_SOURCE_DIR}/libft/
        ${CMAKE_SOURCE_DIR}/minilibx/)
add_executable(cub3d gnl/get_next_line.c main.c includes/cub3d.h includes/keys.h utils.c parser_utils.c raycaster.c sprites.c textures.c map.c drawing_utils.c parser.c)
target_link_libraries(cub3d ft mlx)