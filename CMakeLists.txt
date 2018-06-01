###############################################################################
#     Made by Daniel Aaron Salwerowicz 2018-03-12 egeikkjenorsk@gmail.com
###############################################################################
# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

###############################################################################
# Global name of the project
project(AnalProber)

###############################################################################
# Include required packages
find_package(Qt5Core REQUIRED)

###############################################################################
# Compile and build
option(BUILD_APPLICATION "Build demo application" TRUE)
if(BUILD_APPLICATION)

    #############################################################################
    # Source files and friends
    set( HDRS
        include/Battlefield.hpp
        include/GameManager.hpp
        include/SceneObject.hpp
        include/FpsCounter.hpp
        include/Projectile.hpp
        include/OBJLoader.hpp
        include/Spaceship.hpp
        include/Particle.hpp
        include/Camera.hpp
        include/Shader.hpp
        include/Skybox.hpp
        include/Enemy.hpp
        include/WahAh.hpp
        include/Input.hpp )

    set( SRCS
        src/Battlefield.cpp
        src/GameManager.cpp
        src/SceneObject.cpp
        src/Projectile.cpp
        src/OBJLoader.cpp
        src/Spaceship.cpp
        src/Particle.cpp
        src/Camera.cpp
        src/Shader.cpp
        src/Skybox.cpp
        src/Enemy.cpp
        src/WahAh.cpp

        app/main.cpp )

    set( TEXT
        textures/battlefield_specular_map.bmp
        textures/battlefield_colour_map.bmp
        textures/battlefield_height_map.bmp
        textures/battlefield_light_map.bmp
        textures/battlefield_normal_map.bmp
        textures/particle.bmp
        textures/space_bk.tga
        textures/space_dn.tga
        textures/space_ft.tga
        textures/space_lf.tga
        textures/space_rt.tga
        textures/space_up.tga
        textures/trident.tga )

    set( FAGS
        shaders/particle.frag
        shaders/height.frag
        shaders/object.frag
        shaders/skybox.frag
        shaders/phong.frag
        shaders/wahah.frag
        shaders/red.frag )

    set( VERS
        shaders/particle.vert
        shaders/height.vert
        shaders/object.vert
        shaders/skybox.vert
        shaders/phong.vert
        shaders/wahah.vert
        shaders/red.vert )

    add_executable(${PROJECT_NAME}
        ${HDRS}
        ${SRCS}
        ${TEXT}
        ${FAGS}
        ${VERS} )

    #############################################################################
    # Turn on C++17 features
    if(${CMAKE_VERSION} VERSION_LESS "3.8.0")

        message(STATUS
            "${PROJECT_NAME} requires compiling in mode supporting C++17 features.")

    else()

        target_compile_features(${PROJECT_NAME}
            PUBLIC $<$<CXX_COMPILER_ID:Clang>:cxx_std_17>
            PUBLIC $<$<CXX_COMPILER_ID:GNU>:cxx_std_17>
            )

    endif() # end ${CMAKE_VERSION} VERSION_LESS "3.8.0"

    #############################################################################
    # Compiler specific options
    if(CMAKE_BUILD_TYPE MATCHES DEBUG)
        target_compile_options(${PROJECT_NAME}
            PUBLIC $<$<CXX_COMPILER_ID:Clang>:
                -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-documentation -pedantic -Werror
                -Wno-missing-variable-declarations # Shit I cannot fix, other's code
                -Wno-zero-as-null-pointer-constant # Since some OpenGL methods insist on using NULL...
                -Wno-unused-member-function # SHUT UP CLANG I HAVEN'T IMPLEMENTED THE CODE YET, JUST LET ME DEBUG
                -Wno-exit-time-destructors # Shit I cannot fix, other's code
                -Wno-unused-private-field # SHUT UP CLANG I HAVEN'T IMPLEMENTED THE CODE YET, JUST LET ME DEBUG
                -Wno-global-constructors # Shit I cannot fix, other's code
                -Wno-missing-prototypes # Shit I cannot fix, other's code
                -Wno-sign-conversion # Since vertShaderError, fragShaderError, and program ShaderError fuck me up
                -Wno-unused-variable # SHUT UP CLANG I HAVEN'T IMPLEMENTED THE CODE YET, JUST LET ME DEBUG
                -Wno-old-style-cast # Shit I cannot fix, other's code
                -Wno-float-equal # Shit I cannot fix, other's code
                -Wno-padded # QtCreator stuff
            >
            PUBLIC $<$<CXX_COMPILER_ID:GNU>:
                -pedantic -Wall -Werror
            >
            )
    else()
        target_compile_options(${PROJECT_NAME}
            PUBLIC $<$<CXX_COMPILER_ID:Clang>:
                -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-documentation -pedantic -Werror
                -Wno-missing-variable-declarations # Shit I cannot fix, other's code
                -Wno-zero-as-null-pointer-constant # Since some OpenGL methods insist on using NULL...
                -Wno-exit-time-destructors # Shit I cannot fix, other's code
                -Wno-global-constructors # Shit I cannot fix, other's code
                -Wno-missing-prototypes # Shit I cannot fix, other's code
                -Wno-sign-conversion # Since vertShaderError, fragShaderError, and program ShaderError fuck me up
                -Wno-old-style-cast # Shit I cannot fix, other's code
                -Wno-float-equal # Shit I cannot fix, other's code
                -Wno-padded # QtCreator stuff
            >
            PUBLIC $<$<CXX_COMPILER_ID:GNU>:
                -pedantic -Wall -Werror
            >
            )
    endif()


    #############################################################################
    # Default from QtCreator
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)

    #############################################################################
    # Qt dependencies
    target_link_libraries(${PROJECT_NAME} Qt5::Core GLEW GL GLU glut SOIL)

endif() # end BUILD_APPLICATION
