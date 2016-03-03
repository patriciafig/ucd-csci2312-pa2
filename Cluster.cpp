//
//  Cluster.cpp
//  PA2
//
//  Created by Figueroa, Patricia on 2/16/16.

#include "Cluster.h"

#include <cassert>
#include <string>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;
namespace Clustering {

    LNode::LNode(const Point &new_Point, LNodePtr n) : point(new_Point), next(n) {
        point = new_Point;
        next = n;

    }
    //The Big Three

    //1.Copy Constructor
    Clustering::Cluster::Cluster() {
        __size = 0;
        __points = nullptr;
    }

    Cluster::Cluster(const Cluster &rhs) : Cluster() {
        for (int count = 0; count < rhs.getSize(); ++count) {
            add(rhs[count]);
        }
    }

    //2. Overloaded Assignment
    Cluster &Clustering::Cluster::operator=(const Cluster &rhs) {
        LNodePtr curr;

        if (this == &rhs)
            return *this;
        else {
            while (__points != nullptr) {
                curr = __points;
                __points = __points->next;
                delete curr;
                __size--;
            }

            for (int count = 0; count < rhs.__size; count++)
                add(rhs[count]);
        }

        return *this;
    }

    int Cluster::getSize() const {
        return __size;
    }
    //3. Destructor

    Cluster::~Cluster() {
        LNodePtr curr;
        while (__points != nullptr) {
            curr = __points;
            __points = curr->next;

            delete curr;
        }
    }

    // Functions

    void Clustering::Cluster::add(const Point &point) {
        if (__size == 0) {
            ++__size;
            __points = new LNode(point, nullptr);
        }
        else {
            if (contains(point))
                return; // if the point exists, then exit

            LNodePtr curr;
            LNodePtr prev;

            curr = __points;
            prev = nullptr;
            while (curr != nullptr) {
                if (point < curr->point) {
                    if (prev == nullptr) {
                        __points = new LNode(point, curr);

                        __size++;

                        return;  // Add complete, exit
                    }
                    else {
                        prev->next = new LNode(point, curr);

                        __size++;

                        return;  // complete, exit
                    }
                }

                prev = curr;
                curr = curr->next;

            }


            prev->next = new LNode(point, nullptr);

            __size++;
        }
    }

    const Point &Clustering::Cluster::remove(const Point &point) {

        LNodePtr prev = __points;
        LNodePtr curr = __points;

        if (__points == nullptr)
            return point;
        else if (__points->point == point) {
            curr = __points;
            __points = __points->next;
            delete curr;
            __size--;
        }
        else {
            curr = curr->next;
            while (curr != nullptr) {
                if (curr->point == point) {
                    prev->next = curr->next;
                    delete curr;
                    __size--;
                    break;
                }
                curr = curr->next;
                prev = prev->next;
            }
        }
        return point;
    }

    bool Clustering::Cluster::contains(const Point &point) {
        LNodePtr next = this->__points;

        while (next != nullptr) {
            if (next->point.getId() == point.getId())
                return true;
            else
                next = next->next;
        }

        return false;
    }

    const Point &Cluster::operator[](unsigned int index) const {
        assert (__size > 0);
        LNodePtr cursor = __points;

        for (int count = 0; count < index; count++) {
            cursor = cursor->next;
        }
        return cursor->point;
    }

    Cluster &Clustering::Cluster::operator+=(const Point &point) {
        add(point);

        return *this;
    }

    Cluster &Clustering::Cluster::operator-=(const Point &point) {
        remove(point);

        return *this;
    }

    // Members
    Cluster &Cluster::operator+=(const Cluster &rhs) {
        for (int i = 0; i < rhs.getSize(); ++i) {
            add(rhs[i]);
        }

        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &rhs) {
        for (int i = 0; i < rhs.getSize(); ++i) {
            remove(rhs[i]);
        }

        return *this;
    }

    // Private Members
    void Cluster::__del() {

    }

    void Cluster::__cpy(LNodePtr pts) {

    }

    bool Cluster::__in(const Point &p) const {
        return 0;
    }

    // friend comparison
    bool operator==(const Cluster &lhs, const Cluster &rhs) {
        if (lhs.getSize() != rhs.getSize())
            return false;

        for (int i = 0; i < lhs.getSize(); ++i) {
            if (lhs[i] != rhs[i])
                return false;
        }

        return true;
    }

    bool operator!=(const Cluster &lhs, const Cluster &rhs) {
        return !(lhs == rhs);
    }

    const Cluster operator+(const Cluster &lhs, const Point &rhs) {
        Cluster sum(lhs);
        sum += rhs;
        return sum;
    }

    const Cluster operator-(const Cluster &lhs, const Point &rhs) {
        Cluster sub(lhs);
        sub -= rhs;
        return sub;
    }

    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {
        Cluster sum(lhs);
        sum += rhs;
        return sum;
    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {
        Cluster sub(lhs);
        sub -= rhs;
        return sub;
    }


    // Operators Friends
    // Friends
    std::ostream &operator<<(std::ostream &os, const Cluster &cluster1) {
        os << std::setprecision(20);
        for (int count = 0; count < cluster1.getSize(); count++) {
            os << cluster1[count] << std::endl;

        }

        return os;
    }

    std::istream &operator>>(std::istream &input, Cluster &cluster1) {
        std::string line;
        std::getline(input, line);

        while (!input.eof()) {
            Point point(1);


            if (line.length() > 0) {
                std::stringstream ss(line);

                ss >> point;

                cluster1.add(point);
            }
        }

        return input;
    }


}