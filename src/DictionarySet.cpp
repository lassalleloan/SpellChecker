/**
*  @file DictionarySet.cpp
*  @brief Modélise un dictionnaire avec une table de hachage.
*
*  @author Damien Carnal, Matthieu Chatelan, Loan Lassalle
*  @date 27 December 2016
*  @version 1.0
*/

#include <fstream>

#include "DictionarySet.h"
#include "Tools.h"

DictionarySet::DictionarySet(const std::string &filename) : IDictionary(filename) {
    std::string line;
    std::ifstream stream(filename);

    // Création du dictionnaire.
    while (std::getline(stream, line))
        add(strSanitize(line));

    stream.close();
}

DictionarySet::~DictionarySet() {
    clear();
}

void DictionarySet::add(const std::string &word) {
    set.insert(word);
}

void DictionarySet::clear() {
    set.clear();
}

bool DictionarySet::empty() const {
    return set.empty();
}

size_t DictionarySet::remove(const std::string &word) {
    return set.erase(word);
}

bool DictionarySet::contains(const std::string &str) {
    if (str.length() && set.find(str) != set.end())
        return true;

    return false;
}

size_t DictionarySet::size() const {
    return set.size();
}

