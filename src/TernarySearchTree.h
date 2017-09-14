/**
*  @file TernarySearchTree.h
*  @brief Modélise un arbre ternaire de recherche (Ternary Search Tree).
*
*  @author Damien Carnal, Matthieu Chatelan, Loan Lassalle
*  @date 27 December 2016
*  @version 1.0
*/

#pragma once

#include <algorithm>
#include <string>
#include <vector>

template<typename ValueType>
class TernarySearchTree {
public:
    /**
    * @fn TernarySearchTree()
    * @brief Constructeur d'un arbre ternaire de recherche.
    */
    TernarySearchTree() : root(nullptr) {}

    /**
    * @fn ~TernarySearchTree()
    * @brief Destructeur d'un arbre ternaire de recherche.
    */
    ~TernarySearchTree() {
        clear();
    }

    /**
    * @fn std::vector<std::string>& allKeys(std::vector<std::string>& keys) const
    * @brief Obtient toutes les clés de l'arbre ternaire de recherche.
    *
    * @param[in] keys      tableau de toutes les clés de l'arbre ternaire de
    *                      recherche.
    * @return tableau contenant toutes les clés de l'arbre ternaire de
    *         recherche.
    */
    std::vector<std::string> &allKeys(std::vector<std::string> &keys) const {
        collect(root, "", keys);
        return keys;
    }

    /**
    * @fn std::vector<std::string> allKeys() const
    * @brief Obtient toutes les clés de l'arbre ternaire de recherche.
    *
    * @return tableau contenant toutes les clés de l'arbre ternaire de
    *         recherche.
    */
    std::vector<std::string> allKeys() const {
        std::vector<std::string> key;
        return allKeys(key);
    }

    /**
    * @fn bool contains(const std::string& key) const
    * @brief Indique si la clé recherchée est contenue dans l'arbre ternaire
    *        de recherche.
    *
    * @param[in] key     clé à rechercher
    *
    * @return true si la clé est contenue dans l'arbre ternaire de recherche,
    *         false sinon
    */
    bool contains(const std::string &key) const {
        return get(key) != (ValueType) NULL;
    }

    /**
    * @fn void clear()
    * @brief Supprime le contenu de l'arbre ternaire de recherche.
    */
    void clear() {
        visitInOrder([](char c, ValueType &value) {
            value = (ValueType) NULL;
        });

        root = removeSubTree(root);
    }

    /**
    * @fn size_t countKeys() const
    * @brief Obtient le nombre de clés contenues dans l'arbre ternaire de
    *        recherche.
    *
    * @param[in] key     clé à rechercher
    *
    * @return nombre de clés contenues dans l'arbre ternaire de recherche.
    */
    size_t countKeys() const {
        return countKeys(root);
    }

    /**
    * @fn ValueType get(const std::string& key) const
    * @brief Obtient la valeur d'un clé de l'arbre ternaire de recherche.
    *
    * @param[in] key     clé de la valeur recherché
    *
    * @return valeur de la clé de l'arbre ternaire de recherche.
    */
    ValueType get(const std::string &key) const {
        if (key.empty())
            return (ValueType) NULL;

        Node *node = get(root, key, 0);
        if (!node)
            return (ValueType) NULL;

        return node->value;
    }

    /**
    * @fn size_t height() const
    * @brief Obtient la hauteur de l'arbre ternaire de recherche.
    *
    * @return hauteur de l'arbre ternaire de recherche.
    */
    size_t height() const {
        return height(root);
    }

    /**
    * @fn void put(const std::string& key, const ValueType& value)
    * @brief Ajoute une clé et une valeur à l'arbre ternaire de recherche.
    */
    void put(const std::string &key, const ValueType &value) {
        if (!key.empty())
            root = put(root, key, value, 0);
    }

    /**
    * @fn size_t remove(const std::string& key)
    * @brief Obtient la hauteur de l'arbre ternaire de recherche.
    *
    * @return hauteur de l'arbre ternaire de recherche.
    */
    size_t remove(const std::string &key) {
        if (key.empty())
            return 0;

        Node *node = get(root, key, 0);
        if (!node)
            return 0;

        node->value = (ValueType) NULL;
        root = removeSubTree(root);

        return 1;
    }

    /**
    * @fn template <typename Function>
    *     void visitInOrder(Function f)
    * @brief Permet de visiter l'arbre ternaire de recherche dans l'ordre
    *        symétrique.
    */
    template<typename Function>
    void visitInOrder(Function f) {
        visitInOrder(root, f);
    }

private:
    /**
  * @var   struct Node
    * @brief Noeux de l'arbre. Contient un caractères, une valeur et les liens
  *        vers les sous-arbres gauche, central et droit.
    */
    struct Node {
    public:
        char c;
        ValueType value;
        Node *left; // sous-arbre avec des clés plus petites
        Node *middle; // sous-arbre avec des clés égales
        Node *right; // sous-arbre avec des clés plus grandes
    };

    /**
    * @var   Node* root
    * @brief Racine de l'arbre.
    */
    Node *root;

    /**
    * @fn void collect(Node* node, std::string prefix,
    *                  std::vector<std::string>& keys) const
    * @brief Rempli le tableau de toutes clés contenues dans l'arbre ternaire
    *        de recherche.
    */
    void collect(Node *node, std::string prefix,
                 std::vector<std::string> &keys) const {
        if (!node)
            return;

        if (node->left)
            collect(node->left, prefix, keys);
        if (node->middle)
            collect(node->middle, prefix + std::string(1, node->c), keys);
        if (node->right)
            collect(node->right, prefix, keys);

        if (node->value && !prefix.empty())
            keys.push_back(prefix + std::string(1, node->c));
    }

    /**
    * @fn size_t countKeys(Node* node) const
    * @brief Obtient le nombre de clés contenues dans l'arbre ternaire de
    *        recherche.
    *
    * @param[in] node    noeud de l'arbre ternaire de recherche
    *
    * @return nombre de clés contenues dans l'arbre ternaire de recherche.
    */
    size_t countKeys(Node *node) const {
        size_t counter = 0;

        if (!node)
            return counter;
        else if (node->value)
            counter = 1;

        return counter + countKeys(node->left) + countKeys(node->middle)
               + countKeys(node->right);
    }

    /**
    * @fn Node* get(Node* node, const std::string& key, size_t charIndex) const
    * @brief Obtient le noeud recherché de l'arbre ternaire de recherche.
    *
    * @param[in] node          noeud de l'arbre ternaire de recherche
    * @param[in] key           clé du noeud recherché
    * @param[in] charIndex     index de la partie de la clé
    *
    * @return noeud recherché de l'arbre ternaire de recherche.
    */
    Node *get(Node *node, const std::string &key, size_t charIndex) const {
        if (!node)
            return nullptr;

        char c = key.at(charIndex);

        if (c < node->c)
            return get(node->left, key, charIndex);
        else if (c > node->c)
            return get(node->right, key, charIndex);
        else if (charIndex < key.length() - 1)
            return get(node->middle, key, charIndex + 1);
        else
            return node;
    }

    /**
    * @fn size_t height((Node* node) const
    * @brief Obtient la hauteur de l'arbre ternaire de recherche.
    *
    * @param[in] node          noeud de l'arbre ternaire de recherche
    *
    * @return hauteur de l'arbre ternaire de recherche.
    */
    size_t height(Node *node) const {
        if (!node)
            return 0;

        return std::max({height(node->left), height(node->middle),
                         height(node->right)}) + 1;
    }

    /**
    * @fn Node* put(Node* node, const std::string& key, const ValueType& value,
    *               size_t charIndex)
    * @brief Ajoute une clé et une valeur à l'arbre ternaire de recherche.
    *
    * @param[in] node          noeud de l'arbre ternaire de recherche
    * @param[in] key           clé du noeud recherché
    * @param[in] charIndex     index de la partie de la clé
    *
    * @return noeud ajouté de l'arbre ternaire de recherche.
    */
    Node *put(Node *node, const std::string &key, const ValueType &value,
              size_t charIndex) {
        char c = key.at(charIndex);

        if (!node) {
            node = new Node();
            node->c = c;
        }

        if (c < node->c)
            node->left = put(node->left, key, value, charIndex);
        else if (c > node->c)
            node->right = put(node->right, key, value, charIndex);
        else if (charIndex < key.length() - 1)
            node->middle = put(node->middle, key, value, charIndex + 1);
        else
            node->value = value;

        return node;
    }

    /**
    * @fn Node* removeSubTree(Node* node)
    * @brief Supprime un noeud à l'arbre ternaire de recherche.
    *
    * @param[in] node    noeud de l'arbre ternaire de recherche
    *
    * @return noeud supprimé de l'arbre ternaire de recherche.
    */
    Node *removeSubTree(Node *node) {
        if (!node)
            return nullptr;

        if (node->left)
            node->left = removeSubTree(node->left);
        if (node->middle)
            node->middle = removeSubTree(node->middle);
        if (node->right)
            node->right = removeSubTree(node->right);

        if (node->left || node->middle || node->right || node->value)
            return node;
        else
            return nullptr;
    }

    /**
    * @fn template <typename Function>
    *     void visitInOrder(Node* node, Function f)
    * @brief Permet de visiter l'arbre ternaire de recherche dans l'ordre
    *        symétrique.
    *
    * @param[in] node    noeud de l'arbre ternaire de recherche
    */
    template<typename Function>
    void visitInOrder(Node *node, Function f) {
        if (!node)
            return;

        f(node->c, node->value);

        if (node->left)
            visitInOrder(node->left, f);
        if (node->middle)
            visitInOrder(node->middle, f);
        if (node->right)
            visitInOrder(node->right, f);
    }
};