cmake_minimum_required(VERSION 3.26)
project(ESTRUTURA_DE_DADOS)

set(CMAKE_CXX_STANDARD 17)

add_executable(ESTRUTURA_DE_DADOS main.cpp
        ListaSequencial.cpp
        ListaEncadeada.cpp
        Principal.h
        Principal.cpp
        Lista.h
        Lista.hpp)
