project(gc_can_1)

# Targets  
add_executable(gc_can_1
    src/main_gc_can_1.cpp
)

# definitions     
if(CARLSIM_NO_CUDA)
    target_compile_definitions(gc_can_1 PUBLIC
        -D__NO_CUDA__ )
endif()

# Linking    
target_link_libraries(gc_can_1 PRIVATE
    carlsim
    carlsim-stopwatch
)
target_include_directories(gc_can_1 PRIVATE
    ../../tools/stopwatch
)
   
        
# Installation   
install(TARGETS gc_can_1
    EXPORT carlsim
    RUNTIME 
        DESTINATION $<$<CONFIG:Debug>:debug/>samples 
        COMPONENT gc_can_1
        )

#install(FILES run_gc_can_1 DESTINATION $<$<CONFIG:Debug>:debug/>samples)          