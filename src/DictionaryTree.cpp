/**
*  @file DictionaryTree.cpp
*  @brief Mod�lise un dictionnaire avec un arbre ternaire de recherche.
*
*  @author Damien Carnal, Matthieu Chatelan, Loan Lassalle
*  @date 27 December 2016
*  @version 1.0
*/

#include <fstream>

#include "DictionaryTree.h"
#include "Tools.h"

DictionaryTree::DictionaryTree(const std::string &filename) : IDictionary(filename) {
    std::string line;
    std::ifstream stream(filename);

    // Cr�ation du dictionnaire.
    while (std::getline(stream, line))
        add(strSanitize(line));

    stream.close();
}

DictionaryTree::~DictionaryTree() {
    clear();
}

void DictionaryTree::add(const std::string &word) {
    size_t value = 0;
    tree.put(word, ++value);
}

void DictionaryTree::clear() {
    tree.clear();
}

bool DictionaryTree::empty() const {
    return tree.countKeys() == 0;
}

size_t DictionaryTree::remove(const std::string &word) {
    return tree.remove(word);
}

bool DictionaryTree::contains(const std::string &str) {
    if (str.length() && tree.contains(str))
        return true;

    return false;
}

size_t DictionaryTree::size() const {
    return tree.countKeys();
}

