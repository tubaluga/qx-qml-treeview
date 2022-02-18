function(use_files TARGET)
    string(TOUPPER ${TARGET} TARGET_NAME)

    if("${ARGV1}" STREQUAL "RECURSE")
        file(GLOB_RECURSE TARGET_FILES "${ARGV2}")
    else()
        file(GLOB TARGET_FILES "${ARGV1}")
    endif()

    add_custom_target("${PROJECT_NAME}-${TARGET}" SOURCES ${TARGET_FILES})

    set(${TARGET_NAME}_FILES ${TARGET_FILES} PARENT_SCOPE)
endfunction()
