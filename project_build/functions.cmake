function(glob_exec src_location extra_dirs extra_libs)
    message("Source folders to generate from: " ${src_location})
    foreach (srcfile ${src_location})
        get_filename_component(target ${srcfile} NAME_WE)
        message("Creating exec " ${target} " from:" ${srcfile} ${extra_libs})
        add_executable(${target} ${srcfile})
        if (target)
            target_include_directories(${target} PUBLIC
                    common
                    ${extra_dirs})
            target_link_libraries(${target} PRIVATE
                    glfw
                    ${GLFW_LIBRARIES}
                    ${OPENGL_LIBRARIES}
                    glad
                    stb_image
                    imgui
                    GLEW::glew_s
                    ${CMAKE_DL_LIBS}
                    ${extra_libs}
                    )
        endif (target)
    endforeach()
endfunction()

# Copyall: copy texture files and asset files to somewhere in the binary directory
# from_dir:
# to_dir: path in binary directory
function(COPYALL from_dir to_dir)
    file(MAKE_DIRECTORY ${to_dir})
    file(GLOB ASSETS ${from_dir}/*)
    foreach (file_path ${ASSETS})
        get_filename_component(file ${file_path} NAME)
        configure_file(${from_dir}/${file} ${to_dir}/${file} COPYONLY)
    endforeach ()
endfunction()


function(FIND_ALL_LIBRARIES
        from_dir
        save_lib
        include_libs
        include_dirs)
    file(GLOB MODULES ${from_dir}/*)
    #message("BFORE " ${save_lib})
    set(SAVE_LIB_NAME ${save_lib})
    set(save_lib "")
    message("Include dirs; " ${include_dirs})
    foreach (module ${MODULES})
        get_filename_component(target ${module} NAME)
        if (${target} MATCHES "^.*\\.h$" OR ${target} MATCHES "tests.cpp")
            message("Not building: " ${target})
            continue()
        endif()
        # printing one line for each module & its directory
#        message("" ${target} " built from directory " ${module})
        # auto loaded libraries all have prefix 'loaded_'
        add_library(loaded_${target} ${module}/module.cpp)
        target_include_directories(loaded_${target} PUBLIC
                common
                ${CMAKE_SOURCE_DIR}/modules/
                # common/??
                ${CMAKE_SOURCE_DIR}/
                ${include_dirs}
                )
        target_link_libraries(loaded_${target} PRIVATE
                glfw
                ${GLFW_LIBRARIES}
                ${OPENGL_LIBRARIES}
                glad
                ${include-libs}
                #            stb_image
                )
        # the setting aspect must not be the parsed variable....
        # set save_lib to set the variable, set ${save_lib} = ALL_MODULES to be the
        LIST(APPEND save_lib loaded_${target})
    endforeach ()

    set(${SAVE_LIB_NAME} ${save_lib} PARENT_SCOPE)
    message(${save_lib} " saved in " ${SAVE_LIB_NAME})
endfunction()