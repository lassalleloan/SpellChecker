/**
*  @file DictionaryTree.h
*  @brief Mod�lise un dictionnaire avec un arbre ternaire de recherche.
*
*  @author Damien Carnal, Matthieu Chatelan, Loan Lassalle
*  @date 27 December 2016
*  @version 1.0
*/

#pragma once

#include <string>

#include "IDictionary.h"
#include "TernarySearchTree.h"

class DictionaryTree : public IDictionary {
public:
    /**
    * @fn DictionaryTree(const std::string& filename)
    * @brief Constructeur d'un dictionnaire avec le nom d'un fichier �
    *        importer.
    *
    * @param[in] filename      nom d'un fichier � importer
    */
    DictionaryTree(const std::string &filename);

    /**
    * @fn ~DictionaryTree()
    * @brief Destructeur d'un dictionnaire, suppression du contenu du
    *        dictionnaire.
    */
    ~DictionaryTree();

    /**
    * @fn void add(const std::string& word)
    * @brief Ajoute un mot au dictionnaire, si il n'y est pas pr�sent.
    *
    * @param[in] word      mot � ajouter au dictionnaire
    */
    void add(const std::string &word);

    /**
    * @fn void clear()
    * @brief Supprime le contenu du dictionnaire.
    */
    void clear();

    /**
    * @fn bool empty() const
    * @brief Indique si le dictionnaire est vide.
    *
    * @return true si le dictionnaire est vide, false sinon.
    */
    bool empty() const;

    /**
    * @fn size_t remove(const std::string& word)
    * @brief Supprime le mot du dictionnaire.
    *
    * @param[in] word      mot � supprimer au dictionnaire
    *
    * @return nombre de mots du dictionnaire supprim�s.
    */
    size_t remove(const std::string &word);

    /**
    * @fn bool contains(const std::string& word)
    * @brief Indique si le mot recherch� est contenu dans le dictionnaire.
    *
    * @param[in] word     mot � rechercher
    *
    * @return true si le mot est contenu dans le dictionnaire, false sinon
    */
    bool contains(const std::string &word);

    /**
    * @fn size_t size() const
    * @brief Obtient le nombre de mots contenus dans dictionnaire.
    *
    * @return nombre de mots contenus dans le dictionnaire.
    */
    size_t size() const;

private:
    /**
    * @var   TernarySearchTree tree
    * @brief Arbre ternaire de recherche pour stocker les mots du dictionnaire.
    */
    TernarySearchTree<size_t> tree;
};

