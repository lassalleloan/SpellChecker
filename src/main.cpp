/* 
 * Laboratoire : n° 6
 * 
 * File:         main.cpp
 * Authors:      Damien Carnal, Matthieu Chatelan, Loan Lassalle
 * Description:  Produit deux fichiers texte contenant la correction des mots
 *               mal orthographiés dans le texte fourni.
 *               Affiche le temps de création et de correction pour les deux
 *               types de dictionnaire.
 *
 * Created on 22. decembre 2016
 */

#include <chrono>
#include <iostream>

#include "DictionarySet.h"
#include "DictionaryTree.h"
#include "Spellchecker.h"

#define TIME_UNIT " ms"
#define OUTPUT_SET "output_dictionarySet.txt"
#define OUTPUT_TREE "output_dictionaryTree.txt"

using namespace std;

int main(int argc, char *argv[]) {
    // Récupération des arguments de la ligne de commande
    vector<string> filenames(parseCmdline(argc, argv));

    // Spellchecker avec un DictionarySet

    // Création du DictionarySet
    auto t1_1 = chrono::high_resolution_clock::now();
    DictionarySet dictionarySet(filenames[0]);
    auto t2_1 = chrono::high_resolution_clock::now();

    Spellchecker spellcheckerSet(dictionarySet);

    // Correction du texte avec le DictionarySet
    auto t3_1 = chrono::high_resolution_clock::now();
    spellcheckerSet.checkFile(filenames[1], OUTPUT_SET);
    auto t4_1 = chrono::high_resolution_clock::now();

    // Affichage des temps pour le DictionarySet
    auto creationTime_1 = chrono::duration_cast<chrono::milliseconds>(t2_1 - t1_1).count();
    auto checkTime_1 = chrono::duration_cast<chrono::milliseconds>(t4_1 - t3_1).count();
    cout << "DictionarySet" << endl
         << "Creation of dictionary : " << creationTime_1 << TIME_UNIT << endl
         << "Spelling correction    : " << checkTime_1 << TIME_UNIT << endl
         << endl;

    // Spellchecker avec un DictionaryTree

    // Création du DictionaryTree
    auto t1_2 = chrono::high_resolution_clock::now();
    DictionaryTree dictionaryTree(filenames[0]);
    auto t2_2 = chrono::high_resolution_clock::now();

    Spellchecker spellcheckerTree(dictionaryTree);

    // Correction du texte avec le DictionaryTree
    auto t3_2 = chrono::high_resolution_clock::now();
    spellcheckerTree.checkFile(filenames[1], OUTPUT_TREE);
    auto t4_2 = chrono::high_resolution_clock::now();

    // Affichage des temps pour le DictionaryTree
    auto creationTime_2 = chrono::duration_cast<chrono::milliseconds>(t2_2 - t1_2).count();
    auto checkTime_2 = chrono::duration_cast<chrono::milliseconds>(t4_2 - t3_2).count();
    cout << "DictionaryTree" << endl
         << "Creation of dictionary : " << creationTime_2 << TIME_UNIT << endl
         << "Spelling correction    : " << checkTime_2 << TIME_UNIT;

    return EXIT_SUCCESS;
}

