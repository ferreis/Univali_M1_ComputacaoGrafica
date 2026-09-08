cmake_minimum_required(VERSION 3.20)

project(ComputacaoGrafica LANGUAGES CXX)

add_executable(ComputacaoGrafica
    ComputacaoGrafica/ComputacaoGrafica.cpp
)

target_compile_features(ComputacaoGrafica PRIVATE cxx_std_17)

# Mantem o executavel no mesmo local em geradores single-config e multi-config.
set_target_properties(ComputacaoGrafica PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

foreach(CONFIG Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER "${CONFIG}" CONFIG_UPPER)
    set_target_properties(ComputacaoGrafica PROPERTIES
        "RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER}" "${CMAKE_BINARY_DIR}/bin"
    )
endforeach()

if(WIN32)
    set(FREEGLUT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ComputacaoGrafica/freeglut")

    target_include_directories(ComputacaoGrafica PRIVATE
        "${FREEGLUT_ROOT}/include"
    )

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(FREEGLUT_LIB "${FREEGLUT_ROOT}/lib/x64/freeglut.lib")
        set(FREEGLUT_DLL "${FREEGLUT_ROOT}/bin/x64/freeglut.dll")
    else()
        set(FREEGLUT_LIB "${FREEGLUT_ROOT}/lib/freeglut.lib")
        set(FREEGLUT_DLL "${FREEGLUT_ROOT}/bin/freeglut.dll")
    endif()

    target_link_libraries(ComputacaoGrafica PRIVATE
        opengl32
        "${FREEGLUT_LIB}"
    )

    add_custom_command(TARGET ComputacaoGrafica POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${FREEGLUT_DLL}"
            "$<TARGET_FILE_DIR:ComputacaoGrafica>/freeglut.dll"
        COMMENT "Copiando freeglut.dll para a pasta do executavel"
    )
else()
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)

    target_link_libraries(ComputacaoGrafica PRIVATE
        OpenGL::GL
        GLUT::GLUT
    )
endif()
