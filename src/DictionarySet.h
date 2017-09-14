/**
*  @file DictionarySet.h
*  @brief Modélise un dictionnaire avec une table de hachage.
*
*  @author Damien Carnal, Matthieu Chatelan, Loan Lassalle
*  @date 27 December 2016
*  @version 1.0
*/

#pragma once

#include <string>
#include <unordered_set>

#include "IDictionary.h"

class DictionarySet : public IDictionary {
public:
    /**
    * @fn DictionarySet(const std::string& filename)
    * @brief Constructeur d'un dictionnaire avec le nom d'un fichier à
    *        importer.
    *
    * @param[in] filename      nom d'un fichier à importer
    */
    DictionarySet(const std::string &filename);

    /**
    * @fn ~DictionarySet()
    * @brief Destructeur d'un dictionnaire, suppression du contenu du
    *        dictionnaire.
    */
    ~DictionarySet();

    /**
    * @fn void add(const std::string& word)
    * @brief Ajoute un mot au dictionnaire, si il n'y est pas présent.
    *
    * @param[in] word      mot à ajouter au dictionnaire
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
    * @param[in] word      mot à supprimer au dictionnaire
    *
    * @return nombre de mots du dictionnaire supprimés.
    */
    size_t remove(const std::string &word);

    /**
    * @fn bool contains(const std::string& word)
    * @brief Indique si le mot recherché est contenu dans le dictionnaire.
    *
    * @param[in] word     mot à rechercher
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
    * @var   std::unordered_set<std::string> set
    * @brief Table de hachage pour stocker les mots du dictionnaire.
    */
    std::unordered_set<std::string> set;
};

