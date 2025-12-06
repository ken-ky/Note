add_executable(Tutorial)

find_package(fmt REQUIRED)

target_link_libraries(Tutorial PUBLIC fmt::fmt)

target_sources(Tutorial
  PRIVATE
    Tutorial.cxx
)

target_link_libraries(Tutorial
  PRIVATE
    MathFunctions
)
