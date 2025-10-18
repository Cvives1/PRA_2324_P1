#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
        Node<T>* first;
        int n;

    public:
        // Constructor
        ListLinked() : first(nullptr), n(0) {}

        // Destructor
        ~ListLinked() {
            while (first != nullptr) {
                Node<T>* aux = first->next;
                delete first;
                first = aux;
            }
        }

        // Sobrecarga del operador []
        T operator[](int pos) {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición inválida!");
            }
            Node<T>* current = first;
            for (int i = 0; i < pos; i++) {
                current = current->next;
            }
            return current->data;
        }

        // Devuelve el tamaño de la lista
        int size() const override {
            return n;
        }

        // Indica si la lista está vacía
        bool empty() const override {
            return n == 0;
        }

        // Inserta un elemento en una posición
        void insert(int pos, T e) override {
            if (pos < 0 || pos > n) {
                throw std::out_of_range("Posición inválida!");
            }
            if (pos == 0) {
                first = new Node<T>(e, first);
            } else {
                Node<T>* prev = first;
                for (int i = 0; i < pos - 1; i++) {
                    prev = prev->next;
                }
                prev->next = new Node<T>(e, prev->next);
            }
            n++;
        }

        // Obtiene el elemento en una posición
        T get(int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición inválida!");
            }
            Node<T>* current = first;
            for (int i = 0; i < pos; i++) {
                current = current->next;
            }
            return current->data;
        }

        // Elimina un elemento en una posición
        T remove(int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición inválida!");
            }
            Node<T>* toDelete;
            T data;
            if (pos == 0) {
                toDelete = first;
                data = toDelete->data;
                first = first->next;
            } else {
                Node<T>* prev = first;
                for (int i = 0; i < pos - 1; i++) {
                    prev = prev->next;
                }
                toDelete = prev->next;
                data = toDelete->data;
                prev->next = toDelete->next;
            }
            delete toDelete;
            n--;
            return data;
        }

        // Busca un elemento
        int search(T e) override {
            Node<T>* current = first;
            int index = 0;
            while (current != nullptr) {
                if (current->data == e) return index;
                current = current->next;
                index++;
            }
            return -1;
        }

        // Operador << (impresión)
        friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
            out << "List => [";
            if (!list.empty()) {
                out << "\n";
                Node<T>* current = list.first;
                while (current != nullptr) {
                    out << "  " << current->data << "\n";
                    current = current->next;
                }
            }
            out << "]";
            return out;
        }
};

#endif // LISTLINKED_H

