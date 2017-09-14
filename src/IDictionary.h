/**
*  @file IDictionary.h
*  @brief Modélise un dictionnaire.
*
*  @author Damien Carnal, Matthieu Chatelan, Loan Lassalle
*  @date 27 December 2016
*  @version 1.0
*/

#pragma once

#include <string>

class IDictionary {
public:
    /**
    * @fn IDictionary(const std::string& filename)
    * @brief Constructeur d'un dictionnaire avec le nom d'un fichier à
    *        importer.
    *
    * @param[in] filename      nom d'un fichier à importer
    */
    IDictionary(const std::string &filename) : filename(filename) {}

    /**
    * @fn std::string getFilename() const
    * @brief Obtient le nom du fichier du dictionnaire.
    *
    * @return nom du fichier du dictionnaire.
    */
    virtual std::string getFilename() const {
        return filename;
    }

    /**
    * @fn void add(const std::string& word) = 0
    * @brief Ajoute un mot au dictionnaire, si il n'y est pas présent.
    *
    * @param[in] word      mot à ajouter au dictionnaire
    */
    virtual void add(const std::string &word) = 0;

    /**
    * @fn void clear() = 0
    * @brief Supprime le contenu du dictionnaire.
    */
    virtual void clear() = 0;

    /**
    * @fn bool empty() const = 0
    * @brief Indique si le dictionnaire est vide.
    *
    * @return true si le dictionnaire est vide, false sinon.
    */
    virtual bool empty() const = 0;

    /**
    * @fn size_t remove(const std::string& word) = 0
    * @brief Supprime le mot du dictionnaire.
    *
    * @param[in] word      mot à supprimer au dictionnaire
    *
    * @return nombre de mots du dictionnaire supprimés.
    */
    virtual size_t remove(const std::string &word) = 0;

    /**
    * @fn bool contains(const std::string& word) = 0
    * @brief Indique si le mot recherché est contenu dans le dictionnaire.
    *
    * @param[in] word     mot à rechercher
    *
    * @return true si le mot est contenu dans le dictionnaire, false sinon
    */
    virtual bool contains(const std::string &word) = 0;

    /**
    * @fn size_t size() const = 0
    * @brief Obtient le nombre de mots contenus dans dictionnaire.
    *
    * @return nombre de mots contenus dans le dictionnaire.
    */
    virtual size_t size() const = 0;

private:
    /**
    * @var   std::string filename
    * @brief Nom du fichier du dictionnaire à utiliser.
    */
    std::string filename;
};

