cmake_minimum_required (VERSION 3.8)

project ("vk-draft")

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

file(GLOB_RECURSE vk_draft_sources CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE vk_draft_headers CONFIGURE_DEPENDS "headers/*.hpp")

set (vk_draft_headers_dirs "")
foreach (_headerFile ${vk_draft_headers})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND vk_draft_headers_dirs ${_dir})
endforeach()
list (REMOVE_DUPLICATES vk_draft_headers_dirs)

add_executable (vk-draft
            ${vk_draft_sources}
        )
target_link_libraries(vk-draft ${CONAN_LIBS})
target_include_directories(vk-draft
        PRIVATE ${vk_draft_headers_dirs}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET vk-draft PROPERTY CXX_STANDARD 20)
endif()
