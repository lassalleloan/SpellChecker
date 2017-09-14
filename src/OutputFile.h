/**
*  @file OutputFile.h
*  @brief Modélise un flux vers un fichier.
*
*  @author Damien Carnal, Matthieu Chatelan, Loan Lassalle
*  @date 27 December 2016
*  @version 1.0
*/

#pragma once

#include <fstream>
#include <string>

class OutputFile {
public:
    /**
    * @fn OutputFile(const std::string& filename,
    *                std::ios_base::openmode mode = std::ios_base::out)
    * @brief Constructeur d'un flux vers un fichier avec un nom de fichier et
    *        un mode pour son ouverture.
    */
    OutputFile(const std::string &filename,
               std::ios_base::openmode mode = std::ios_base::out);

    /**
    * @fn ~OutputFile()
    * @brief Destructeur d'un flux qui ferme le fichier.
    */
    ~OutputFile();

    /**
    * @fn std::string getFilename() const
    * @brief Obtient le nom du fichier du flux.
    *
    * @return nom du fichier du flux.
    */
    std::string getFilename() const;

    /**
    * @fn void setFilename(const std::string& filename)
    * @brief Définis le nom du fichier.
    *
    * @param[in] filename   nom du fichier
    */
    void setFilename(const std::string &filename);

    /**
    * @fn std::ios_base::openmode getMode() const
    * @brief Obtient le mode d'ouverture du fichier.
    *
    * @return mode d'ouverture du fichier.
    */
    std::ios_base::openmode getMode() const;

    /**
    * @fn void setMode(std::ios_base::openmode mode)
    * @brief Définis le mode d'ouverture du fichier.
    *
    * @param[in] mode    mode d'ouverture du fichier
    */
    void setMode(std::ios_base::openmode mode);

    /**
    * @fn template <typename T>
    *     OutputFile& operator <<(const T& a)
    * @brief Insert la variable dans le flux.
    *
    * @param[in] a       variable à insérer dans le flux
    *
    * @return flux modifié.
    */
    template<typename T>
    OutputFile &operator<<(const T &a) {
        if (!output.is_open())
            output.open(filename, mode);

        output << a;
        return *this;
    }

    /**
    * @fn OutputFile& operator <<(std::ios_base::openmode mode)
    * @brief Définis le mode d'ouverture du fichier
    *
    * @param[in] mode    mode d'ouverture du fichier
    *
    * @return flux avec le nouveau mode d'ouverture.
    */
    OutputFile &operator<<(std::ios_base::openmode mode);

    /**
    * @fn OutputFile& operator <<(std::ostream& (*os) (std::ostream&))
    * @brief Insert la variable std::endl dans le flux.
    *
    * @param[in] os      std::endl
    *
    * @return flux modifié.
    */
    OutputFile &operator<<(std::ostream &(*os)(std::ostream &));

    /**
    * @fn void close()
    * @brief Ferme le flux.
    */
    void close();

private:
    /**
    * @var   std::string filename
    * @brief Nom du fichier.
    */
    std::string filename;

    /**
    * @var   std::ios_base::openmode mode
    * @brief Mod pour l'ouverture du fichier.
    */
    std::ios_base::openmode mode;

    /**
    * @var   std::ofstream output
    * @brief Flux représentant le fichier.
    */
    std::ofstream output;
};