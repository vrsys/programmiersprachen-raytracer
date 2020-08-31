
file(GLOB FRAMEWORK_SOURCE *.cpp)
file(GLOB FRAMEWORK_INLINE *.inl)
file(GLOB FRAMEWORK_HEADER *.hpp)

source_group("Inline Files" FILES ${FRAMEWORK_INLINE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

#set_source_files_properties(window.cpp glew.c PROPERTIES COMPILE_FLAGS -P)


add_library(${FRAMEWORK_NAME} STATIC glew.c
  ${FRAMEWORK_SOURCE}
  ${FRAMEWORK_INLINE}
  ${FRAMEWORK_HEADER} "shape.cpp" "sphere.cpp" "box.cpp" "light.cpp" "material.cpp" "camera.cpp")
target_link_libraries(${FRAMEWORK_NAME}
  ${OPENGL_LIBRARIES}
  ${GLFW_LIBRARIES}
  )
