project(gc_can)

# Targets  
add_executable(gc_can
    src/main_gc_can.cpp
)

# definitions     
if(CARLSIM_NO_CUDA)
    target_compile_definitions(gc_can PUBLIC
        -D__NO_CUDA__ )
endif()

# Linking    
target_link_libraries(gc_can PRIVATE
    carlsim
    carlsim-stopwatch
)
target_include_directories(gc_can PRIVATE
    ../../tools/stopwatch
)
   
        
# Installation   
install(TARGETS gc_can
    EXPORT carlsim
    RUNTIME 
        DESTINATION $<$<CONFIG:Debug>:debug/>samples 
        COMPONENT gc_can
        )

#install(FILES run_gc_can DESTINATION $<$<CONFIG:Debug>:debug/>samples)          