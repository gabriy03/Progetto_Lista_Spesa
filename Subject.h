//
// Created by gabriele on 09/01/26.
//

#ifndef PROGETTOLISTASPESA_SUBJECT_H
#define PROGETTOLISTASPESA_SUBJECT_H

#include "Observer.h"
class Subject {
public:
    virtual ~Subject() {}

    virtual void aggiungiObserver(Observer* o) = 0;
    virtual void rimuoviObserver(Observer* o) = 0;
    virtual void notify() = 0;
};

#endif //PROGETTOLISTASPESA_SUBJECT_H