add_custom_target(build_all_tests echo "Built all tests!"
        DEPENDS
        lightcxx_testing
        lightcxx_testing_interceptors_libc
        process_safe_wrapper)

add_custom_target(check ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS build_all_tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_custom_target(check_xunit ${CMAKE_CTEST_COMMAND} --no-compress-output -T Test
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

function(add_lightcxx_test filename section name)
    # Parse expectations from test file comments.
    file(STRINGS ${filename} lines)
    set(EXIT "CODE = 0")
    set(STEPS "")
    set(INTERCEPTORS "")
    set(NO_COMPILE "")
    foreach (line ${lines})
        if (NOT (line MATCHES "^//[\ ]*([A-Z_]*):([A-Z_]*) (.*)$"))
            break()
        endif ()
        set(keyword ${CMAKE_MATCH_1})
        set(argument ${CMAKE_MATCH_2})
        if ("${keyword}" STREQUAL "EXPECT" AND (("${argument}" STREQUAL "NO_COMPILE") OR ("${argument}" STREQUAL "EXIT")))
            set(${argument} "${CMAKE_MATCH_3}")
        elseif ("${keyword}" STREQUAL "EXPECT" AND "${argument}" STREQUAL "STEPS")
            string(LENGTH "${CMAKE_MATCH_3}" STEPS_LEN)
            math(EXPR STEPS_LEN "${STEPS_LEN} - 2")
            string(SUBSTRING "${CMAKE_MATCH_3}" 1 ${STEPS_LEN} RAW_STEPS)
            foreach (step ${RAW_STEPS})
                string(APPEND STEPS "STEP: ${step}\n")
            endforeach ()
        elseif ("${keyword}" STREQUAL "REQUEST" AND "${argument}" STREQUAL "ARGUMENTS")
            string(LENGTH "${CMAKE_MATCH_3}" ARGUMENTS_LEN)
            math(EXPR ARGUMENTS_LEN "${ARGUMENTS_LEN} - 2")
            string(SUBSTRING "${CMAKE_MATCH_3}" 1 ${ARGUMENTS_LEN} ARGUMENTS)
        elseif ("${keyword}" STREQUAL "REQUEST" AND "${argument}" STREQUAL "SKIP")
            string(LENGTH "${CMAKE_MATCH_3}" REASON_LEN)
            math(EXPR REASON_LEN "${REASON_LEN} - 2")
            string(SUBSTRING "${CMAKE_MATCH_3}" 1 ${REASON_LEN} REASON)
            message(STATUS "Test [${section}]:${name} is skipped: ${REASON}")
            set(SKIP_TEST TRUE)
        elseif ("${keyword}" STREQUAL "REQUEST" AND "${argument}" STREQUAL "INTERCEPTORS")
            string(LENGTH "${CMAKE_MATCH_3}" INTERCEPTORS_LEN)
            math(EXPR INTERCEPTORS_LEN "${INTERCEPTORS_LEN} - 2")
            string(SUBSTRING "${CMAKE_MATCH_3}" 1 ${INTERCEPTORS_LEN} INTERCEPTORS)
        endif ()
    endforeach ()

    if (NOT (NO_COMPILE STREQUAL ""))
        if (NO_COMPILE MATCHES "^[0-9]+$")
            foreach (fail_index RANGE ${NO_COMPILE})
                set(test_name [${section}]:${name}:COMPILE_FAIL_${fail_index})
                set(test_exe_name test-${section}-${name}-${fail_index})
                add_library(${test_exe_name} OBJECT ${filename})
                target_link_libraries(${test_exe_name} PUBLIC lightcxx_testing)
                target_compile_definitions(${test_exe_name} PUBLIC NC_TEST_ID=${fail_index})
                set_target_properties(${test_exe_name} PROPERTIES
                        EXCLUDE_FROM_ALL TRUE
                        EXCLUDE_FROM_DEFAULT_BUILD TRUE)
                if (NOT SKIP_TEST)
                    add_test(NAME ${test_name}
                            COMMAND ${CMAKE_COMMAND}
                            --build .
                            --target ${test_exe_name}
                            --config $<CONFIGURATION>
                            WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
                    set_tests_properties(${test_name} PROPERTIES WILL_FAIL TRUE)
                endif ()
            endforeach ()
        else ()
            set(test_name [${section}]:${name}:COMPILE_FAIL)
            set(test_exe_name test-${section}-${name})
            add_library(${test_exe_name} OBJECT ${filename})
            target_link_libraries(${test_exe_name} PUBLIC lightcxx_testing)
            set_target_properties(${test_exe_name} PROPERTIES
                    EXCLUDE_FROM_ALL TRUE
                    EXCLUDE_FROM_DEFAULT_BUILD TRUE)
            if (NOT SKIP_TEST)
                add_test(NAME ${test_name}
                        COMMAND ${CMAKE_COMMAND}
                        --build .
                        --target ${test_exe_name}
                        --config $<CONFIGURATION>
                        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
                set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION "${NO_COMPILE}")
            endif ()
        endif ()
        return()
    endif ()

    set(test_name [${section}]:${name})
    set(test_exe_name test-${section}-${name})
    set(exclude_from_all "")
    if (SKIP_TEST)
        set(exclude_from_all EXCLUDE_FROM_ALL)
    endif ()
    add_executable(${test_exe_name} ${exclude_from_all} ${filename})
    target_link_libraries(${test_exe_name} PUBLIC lightcxx_testing)
    foreach (interceptor ${INTERCEPTORS})
        target_link_libraries(${test_exe_name} PUBLIC lightcxx_testing_interceptors_${interceptor})
    endforeach ()
    if (NOT SKIP_TEST)
        add_dependencies(build_all_tests ${test_exe_name})
        if (NOT (EXIT STREQUAL "CODE = 0") OR STEPS)
            add_test(NAME ${test_name} COMMAND process_safe_wrapper $<TARGET_FILE:${test_exe_name}> ${ARGUMENTS})
            set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION "^${STEPS}\n----\nPROCESS EXIT ${EXIT}")
        else ()
            add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${test_exe_name}> ${ARGUMENTS})
        endif ()
        set_tests_properties(${test_name} PROPERTIES FAIL_REGULAR_EXPRESSION "EXPECTATION FAILED")
    endif ()
endfunction()

function(scan_for_lightcxx_tests directory)
    file(GLOB_RECURSE test_files ${directory}/**/*.cpp)
    foreach (test_file ${test_files})
        if (test_file MATCHES "^.*/([a-z.]*)/([^/]*).cpp$")
            if (CMAKE_MATCH_2 STREQUAL "skipped")
                message(STATUS "Tests for section [${CMAKE_MATCH_1}] are not implemented")
            elseif (NOT (CMAKE_MATCH_2 STREQUAL "nothing_to_do"))
                add_lightcxx_test(${test_file} ${CMAKE_MATCH_1} ${CMAKE_MATCH_2})
            endif ()
        else ()
            message(WARNING "Test path not recognized: ${test_file}")
        endif ()
    endforeach ()
endfunction()

scan_for_lightcxx_tests(${CMAKE_CURRENT_SOURCE_DIR})
