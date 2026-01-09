//
// Created by gabriele on 09/01/26.
//

#ifndef PROGETTOLISTASPESA_OBSERVER_H
#define PROGETTOLISTASPESA_OBSERVER_H

class Observer {
public:
    virtual ~Observer() {}

    virtual void update() = 0;
};

#endif //PROGETTOLISTASPESA_OBSERVER_H