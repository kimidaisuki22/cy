

function(add_exe name)
    add_executable(example_${name} src/example_${name}.cpp)
    target_link_libraries(example_${name}
        cy
    )
endfunction()

add_exe(fs)
add_exe(memory)
add_exe(proc)
add_exe(shell)
add_exe(network)
add_exe(text_time)
add_exe(fs_collect)
add_exe(regex_extract)

add_exe(mmap)
