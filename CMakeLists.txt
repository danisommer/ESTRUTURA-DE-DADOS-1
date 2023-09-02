cmake_minimum_required(VERSION 3.26)
project(ESTRUTURA_DADOS_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(ESTRUTURA_DADOS_1 main.cpp
        ListaSequencial.h
        ListaEncadeada.h
        ListaSequencial.cpp
        ListaEncadeada.cpp
        Dado.h)
