cmake_minimum_required(VERSION 3.25)
project(hashmap)

#enable_language(CXX ASM_NASM)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-D _DEBUG -ggdb3 -O0 -msse4.2 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wnon-virtual-dtor -Wopenmp -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -fPIE -fsanitize=address,undefined,leak")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-D NDEBUG -ggdb3 -O3 -msse4.2 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wnon-virtual-dtor -Wopenmp -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -fPIE")
#set(CMAKE_ASM_NASM_FLAGS_RELWITHDEBINFO "-g -Fdwarf")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    hashtest
    src/benchmark.cpp
    src/hashmap.cpp
    src/main.cpp
    src/dictloader.cpp
    src/stats.cpp
#    src/strcmp_aligned32_noinline.nasm
)

include_directories(${PROJECT_SOURCE_DIR}/include)
