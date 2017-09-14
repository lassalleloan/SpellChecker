/**
*  @file Tools.h
*  @brief Divers outils.
*
*  @author Damien Carnal, Matthieu Chatelan, Loan Lassalle
*  @date 27 December 2016
*  @version 1.0
*/

#pragma once

#include <string>
#include <vector>

/**
* @fn std::vector<std::string>& parseCmdline(int argc, char* argv[],
*                                            std::vector<std::string>& filenames)
*
* @brief Recupère et traite les arguments des options transmises lors de
*		   l'exécution.
*    
* @param[in] argc		nombre d'arguments contenu dans argv
* @param[in] argv		tableau contenant des arguments
* @param[in] tokens  tableau contenant les noms des fichiers
*
* @return tableau contenant les noms des fichiers.
*/
std::vector<std::string> &parseCmdline(int argc, char *argv[],
                                       std::vector<std::string> &filenames);

/**
* @fn std::vector<std::string> parseCmdline(int argc, char* argv[])
*
* @brief Recupère et traite les arguments des options transmises lors de
*		   l'exécution.
*    
* @param[in] argc		nombre d'arguments contenu dans argv
* @param[in] argv		tableau contenant des arguments
*
* @return tableau contenant les noms des fichiers.
*/
std::vector<std::string> parseCmdline(int argc, char *argv[]);

/**
* @fn void showError()
*
* @brief Affiche différents messages d'erreur en fonction d'un caractère
*		   constant représentant l'option (optopt).
*/
void showError();

/**
* @fn std::vector<std::string> split(const std::string& str,
*                                    const std::string& delims,
*                                    std::vector<std::string>& tokens)
* @brief Sépare en jetons la chaîne de caractères en fonction des délimiteurs.
*
* @param[in] str      chaîne de caractères à séparer
* @param[in] delims   chaîne de caractères des délimmiteurs
* @param[in] tokens   tableau contenant les jetons
*
* @return tableau de jetons de la chaîne de caractères.
*/
std::vector<std::string> &split(const std::string &str, const std::string &delims,
                                std::vector<std::string> &tokens);

/**
* std::vector<std::string> split(const std::string& str,
                                 const std::string& delims)
* @brief Sépare en jetons la chaîne de caractères en fonction des délimiteurs.
*
* @param[in] str     chaîne de caractères à séparer
* @param[in] delims  chaîne de caractères des délimmiteurs
*
* @return tableau de jetons de la chaîne de caractères.
*/
std::vector<std::string> split(const std::string &str, const std::string &delims);

/**
* @fn std::string& strSanitize(std::string& str)
* @brief Nettoie la chaîne de caractères.
*
* @param[in] str    chaîne de caractères à nettoyer
*
* @return chaîne de caractères nettoyée.
*/
std::string &strSanitize(std::string &str);

/**
* @fn std::string& strTolower(std::string& str)
* @brief Transforme la chaîne de caractères en minuscule.
*
* @param[in] str    chaîne de caractères à mettre en minuscule
*
* @return chaîne de caractères en minuscule.
*/
std::string &strTolower(std::string &str);

/**
* @fn bool isNotAllowedChar(unsigned char c)
* @brief Indique si un caractère est autorisé.
*
* @param[in] c    caractère à tester
*
* @return true si le caractère n'est pas autorisé, false sinon.
*/
bool isNotAllowedChar(unsigned char c);
