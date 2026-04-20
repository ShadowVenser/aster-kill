set(LIB_NAME easy_ecs)
set(ECS_LIB_NAME ${LIB_NAME} PARENT_SCOPE)
set(SOURCES World/World.cpp
        Filter/FilterBuilder.cpp
        Filter/OptimisedFilter.cpp
        Filter/SparseFilter.cpp
        Entity/EntityId.cpp
        Systems/SystemsManager.cpp
        World/World.cpp
)

add_library(${LIB_NAME}
    ${SOURCES})

target_compile_definitions(${LIB_NAME} PUBLIC -DDEBUG)

target_compile_options(${LIB_NAME} PUBLIC -Wall -Wextra -Wpedantic -Werror)
target_compile_options(${LIB_NAME} PUBLIC -g3 -O0)
add_compile_options(-fsanitize=address -g)
add_link_options(-fsanitize=address)

target_compile_features(${LIB_NAME} PRIVATE cxx_std_20)