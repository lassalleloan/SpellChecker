/**
*  @file Spellchecker.h
*  @brief Modélise un correcteur orthographique.
*
*  @author Damien Carnal, Matthieu Chatelan, Loan Lassalle
*  @date 27 December 2016
*  @version 1.0
*/

#pragma once

#define OUTPUT "output.txt"
#define DELIMITERS " -"

#include <algorithm>
#include <fstream>
#include <string>

#include "IDictionary.h"
#include "OutputFile.h"
#include "Tools.h"

class Spellchecker {
public:
    /**
    * @fn Spellchecker(IDictionary& dictionary,
    *                  const std::string& filenameOutput = OUTPUT)
    * @brief Constructeur d'un correcteur orthographique avec le dictionnaire
    *        à utiliser et le nom du fichier de la sortie orthographique.
    *
    * @param[in] dictionary      dictionnaire à utiliser
    * @param[in] filenameOutput  nom du fichier de sortie
    */
    Spellchecker(IDictionary &dictionary,
                 const std::string &filenameOutput = OUTPUT)
            : dictionary(&dictionary), output(filenameOutput) {}

    /**
    * @fn IDictionary getDictionary() const
    * @brief Obtient le dictionnaire utilisé.
    *
    * @return dictionnaire utilisé.
    */
    IDictionary *getDictionary() const {
        return dictionary;
    }

    /**
    * @fn void setDictionary(IDictionary& dictionary)
    * @brief Définis le dictionnaire utilisé.
    */
    void setDictionary(IDictionary &dictionary) {
        this->dictionary = &dictionary;
    }

    /**
    * @fn void checkString(const std::string& mistakeType, std::string& word)
    * @brief Ecris dans le fichier de sortie le type de l'erreur et
    *        l'orthographe correct du mot si seulement le mot n'est pas
    *        présent dans le dictionnaire.
    *
    * @param[in] mistakeType      type d'erreur orthographique
    * @param[in] word             mot à vérifier l'orthographe
    */
    void checkString(const std::string &mistakeType, std::string &word) {
        if (dictionary->contains(word))
            output << mistakeType << ":" << word << std::endl;
    }

    /**
    * @fn void extraLetter(const std::string& word)
    * @brief Ecris dans le fichier de sortie les orthographes corrects
    *        possibles du mot en supprimant chacune des lettre du mot.
    *
    * @param[in] word    mot à vérifier l'orthographe
    */
    void extraLetter(const std::string &word) {
        if (word.empty())
            return;

        const std::string MISTAKE_TYPE = "1";
        const size_t LENGTH = word.length();

        for (size_t i = 0; i < LENGTH; ++i) {
            std::string subWord = word.substr(0, i) + word.substr(i + 1, LENGTH - i - 1);

            // Vérification de l'orthographe
            checkString(MISTAKE_TYPE, subWord);
        }
    }

    /**
    * @fn void missingLetter(const std::string& word)
    * @brief Ecris dans le fichier de sortie les orthographes corrects
    *        possibles du mot en ajoutant une lettre de l'alphabet à n'importe
    *        quelle position dans le mot.
    *
    * @param[in] word    mot à vérifier l'orthographe
    */
    void missingLetter(std::string &word) {
        if (word.empty())
            return;

        const std::string MISTAKE_TYPE = "2";

        for (std::string::iterator it = word.begin(); it != word.end() + 1; ++it) {
            it = word.insert(it, 'a');
            replaceByAlphabet(MISTAKE_TYPE, word, it);
            it = word.erase(it);
        }
    }

    /**
    * @fn void typingError(const std::string& word)
    * @brief Ecris dans le fichier de sortie les orthographes corrects
    *        possibles du mot en remplaçant une lettre du mot par une lettre
    *        de l'alphabet.
    *
    * @param[in] word    mot à vérifier l'orthographe
    */
    void typingError(std::string &word) {
        if (word.empty())
            return;

        const std::string MISTAKE_TYPE = "3";

        // Position du caractère qui suit le dernier caractère
        const std::string::iterator END = word.end();

        for (std::string::iterator it = word.begin(); it != END; ++it) {
            replaceByAlphabet(MISTAKE_TYPE, word, it);
        }
    }

    /**
    * @fn void letterSwap(const std::string& word)
    * @brief Ecris dans le fichier de sortie les orthographes corrects
    *        possibles du mot en échangeant deux à deux les lettres du mot.
    *
    * @param[in] word    mot à vérifier l'orthographe
    */
    void letterSwap(std::string &word) {
        if (word.empty())
            return;

        const std::string MISTAKE_TYPE = "4";

        // Position du dernier caractère à échanger
        const std::string::iterator END = word.end() - 1;

        for (std::string::iterator it = word.begin(); it != END; ++it) {
            std::swap(*it, *(it + 1));

            // Vérification de l'orthographe
            checkString(MISTAKE_TYPE, word);

            std::swap(*it, *(it + 1));
        }
    }

    /**
    * @fn void checkFile(IDictionary* dictionary,
    *                    const std::string& filenameCheck,
    *                    const std::string& filenameOutput)
    * @brief Ecris dans le fichier de sortie toutes les erreurs et corrections
    *        orthographiques d'un texte en fonction du dictionnaire de
    *        référence.
    *
    * @param[in] dictionary       dictionnaire utilisé
    * @param[in] filenameCheck    nom du fichier vérifié
    * @param[in] filenameOutput   nom du fichier de sortie
    */
    void checkFile(IDictionary *dictionary,
                   const std::string &filenameCheck,
                   const std::string &filenameOutput) {
        if (filenameCheck.empty())
            return;

        // Changement du fichier de sortie
        output.setFilename(filenameOutput);
        output << "File checked : " << filenameCheck << std::endl
               << std::ios_base::app;

        std::ifstream stream(filenameCheck);
        std::string line;

        // Chargement de chaque ligne du fichier
        while (std::getline(stream, line)) {
            // Pour chaque mot de la ligne
            for (std::string &word : split(line, DELIMITERS)) {
                // Nettoyage du mot
                strSanitize(word);

                // Vérification de l'orthographe du mot en référence au
                // dictionnaire
                if (!(word.empty() || dictionary->contains(word))) {
                    // Chaîne de caractères mal orthographié
                    output << "*" << word << std::endl;

                    // Suppression d'une lettre du mot
                    extraLetter(word);

                    // Ajout d'une lettre au mot
                    missingLetter(word);

                    // Modification d'une lettre du mot
                    typingError(word);

                    // Echange deux à deux les lettres du mot
                    letterSwap(word);
                }
            }
        }

        stream.close();
        output.close();
    }

    /**
    * @fn void checkFile(const std::string& filenameCheck,
    *                    const std::string& filenameOutput = OUTPUT)
    * @brief Ecris dans le fichier de sortie toutes les erreurs et corrections
    *        orthographiques d'un texte en fonction du dictionnaire de
    *        référence.
    *
    * @param[in] filenameCheck    nom du fichier vérifié
    * @param[in] filenameOutput   nom du fichier de sortie
    */
    void checkFile(const std::string &filenameCheck,
                   const std::string &filenameOutput = OUTPUT) {
        checkFile(dictionary, filenameCheck, filenameOutput);
    }

private:
    /**
    * @fn void replaceByAlphabet(const std::string& mistakeType,
    *                            std::string& word,
    *                            const std::string::iterator& it)
    * @brief Ecris dans le fichier de sortie toutes les erreurs et corrections
    *        orthographiques d'un texte.
    *
    * @param[in] mistakeType   type d'erreur orthographique
    * @param[in] word          mot à vérifier l'orthographe
    * @param[in] it            pointeur sur un caractère du mot
    */
    void replaceByAlphabet(const std::string &mistakeType, std::string &word,
                           const std::string::iterator &it) {
        const char OLD_CHAR = *it;

        for (char c = 'a'; c <= 'z'; ++c) {
            *it = c;

            // Vérification de l'orthographe
            checkString(mistakeType, word);
        }

        *it = OLD_CHAR;
    }

    /**
    * @var   IDictionary* dictionary
    * @brief dictionnaire utilisé comme référence.
    */
    IDictionary *dictionary;

    /**
    * @var   OutputFile output
    * @brief Fichier de sortie des corrections orthographiques.
    */
    OutputFile output;
};

