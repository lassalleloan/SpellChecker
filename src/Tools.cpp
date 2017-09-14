/**
*  @file Tools.cpp
*  @brief Divers outils.
*
*  @author Damien Carnal, Matthieu Chatelan, Loan Lassalle
*  @date 27 December 2016
*  @version 1.0
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <unistd.h>

#include "Tools.h"

// Option pour indiquer un fichier dictionnaire source.
#define OPTION_D 'd'

// Option pour indiquer un fichier source à corriger.
#define OPTION_I 'i'

// Option pour indiquer un fichier de destination des corrections.
#define OPTION_O 'o'

// Options permises par l'exécution.
#define ALL_OPTIONS    "d:i:o:"

// Fichiers par défaut
#define DICTIONARY "resources/dictionary.txt"
#define INPUT      "resources/input_sh.txt"
#define OUTPUT     "output.txt"

std::vector<std::string> &parseCmdline(int argc, char *argv[],
                                       std::vector<std::string> &filenames) {
    if (filenames.size() != 3) {
        std::cerr << "Not enough space in the vector" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Le caractere '?' est retourne si une erreur est detectee.
    opterr = 0;

    int c;
    while ((c = getopt(argc, argv, ALL_OPTIONS)) != -1) {
        switch (c) {
            case OPTION_D:
                filenames[0] = optarg;
                break;

            case OPTION_I:
                filenames[1] = optarg;
                break;

            case OPTION_O:
                filenames[2] = optarg;
                break;

            case '?':
                showError();

            default:
                exit(EXIT_FAILURE);
        }
    }

    for (int index = optind; index < argc; index++)
        std::cerr << "Non-option argument " << argv[index] << "." << std::endl;

    if (optind == argc)
        return filenames;
    else
        exit(EXIT_FAILURE);
}

std::vector<std::string> parseCmdline(int argc, char *argv[]) {
    std::vector<std::string> filenames = {DICTIONARY, INPUT, OUTPUT};
    return parseCmdline(argc, argv, filenames);
}

void showError() {
    unsigned char option = optopt;

    if (option == OPTION_D || option == OPTION_I || option == OPTION_O)
        std::cerr << "Option '-" << option << "' requires an argument."
                  << std::endl;
    else if (isprint(option))
        std::cerr << "Unknown option '-" << option << "'." << std::endl;
    else
        std::cerr << "Unknown option character '-\\" << option << "'."
                  << std::endl;
}

std::vector<std::string> &split(const std::string &str, const std::string &delims,
                                std::vector<std::string> &tokens) {
    size_t begin = str.find_first_not_of(delims),
            end = 0;

    // Récupère les jetons de la chaîne de caractères
    while ((end = str.find_first_of(delims, begin)) != std::string::npos) {
        tokens.push_back(str.substr(begin, end - begin));
        begin = str.find_first_not_of(delims, end);
    }

    // Récupère le dernier jeton de la chaîne de caractères
    if (begin != std::string::npos)
        tokens.push_back(str.substr(begin));

    return tokens;
}

std::vector<std::string> split(const std::string &str, const std::string &delims) {
    std::vector<std::string> tokens;
    split(str, delims, tokens);

    return tokens;
}

std::string &strSanitize(std::string &str) {
    // Suppression des caractères non gérés
    str.erase(std::remove_if(str.begin(), str.end(), isNotAllowedChar),
              str.end());

    // Suppression des apostrophes au début de la chaîne de caractères
    if (*str.begin() == '\'')
        str.erase(str.begin());

    // Suppression des apostrophes à la fin de la chaîne de caractères
    if (*(str.end() - 1) == '\'')
        str.erase(str.end() - 1);

    return strTolower(str);
}

std::string &strTolower(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), tolower);
    return str;
}

bool isNotAllowedChar(unsigned char c) {
    return !(isalpha(c) || c == '\'' || c == ' ');
}

