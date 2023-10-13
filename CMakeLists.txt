cmake_minimum_required(VERSION 3.26)
project(ESTRUTURA_DE_DADOS)

set(CMAKE_CXX_STANDARD 17)

add_executable(ESTRUTURA_DE_DADOS main.cpp
        ListaEncadeada.cpp
        ListaSequencial.cpp
        Principal.cpp)
