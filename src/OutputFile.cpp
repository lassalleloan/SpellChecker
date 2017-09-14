/**
*  @file OutputFile.cpp
*  @brief Modélise un flux vers un fichier.
*
*  @author Damien Carnal, Matthieu Chatelan, Loan Lassalle
*  @date 27 December 2016
*  @version 1.0
*/

#include "OutputFile.h"

OutputFile::OutputFile(const std::string &filename, std::ios_base::openmode mode)
        : filename(filename), mode(mode) {}

OutputFile::~OutputFile() {
    close();
}

std::string OutputFile::getFilename() const {
    return filename;
}

void OutputFile::setFilename(const std::string &filename) {
    close();
    setMode(std::ios_base::out);
    this->filename = filename;
}

std::ios_base::openmode OutputFile::getMode() const {
    return mode;
}

void OutputFile::setMode(std::ios_base::openmode mode) {
    this->mode = mode;
}

OutputFile &OutputFile::operator<<(std::ios_base::openmode mode) {
    setMode(mode);
    return *this;
}

OutputFile &OutputFile::operator<<(std::ostream &(*os)(std::ostream &)) {
    output << os;
    return *this;
}

void OutputFile::close() {
    if (output.is_open())
        output.close();
}

