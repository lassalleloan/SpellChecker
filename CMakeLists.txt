cmake_minimum_required(VERSION 3.8)
project(SpellChecker)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp src/AVLTree.h src/BinarySearchTree.h src/DictionarySet.cpp
        src/DictionarySet.h src/DictionaryTree.cpp src/DictionaryTree.h src/IDictionary.h
        src/OutputFile.cpp src/OutputFile.h src/Spellchecker.h src/TernarySearchTree.h
        src/Tools.cpp src/Tools.h)
add_executable(SpellChecker ${SOURCE_FILES})