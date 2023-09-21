

function(add_exe name)
    add_executable(${name} src/${name}.cpp)
    target_link_libraries(${name}
        cy
    )
endfunction()

add_exe(fs_example)
add_exe(memory_example)
add_exe(proc_example)
add_exe(shell_example)
add_exe(network_example)
