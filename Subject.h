//
// Created by Alessio Masala on 27/02/25.
//

#ifndef ELABORATO_ALESSIO_MASALA_SUBJECT_H
#define ELABORATO_ALESSIO_MASALA_SUBJECT_H

#include "Observer.h"


class Subject {
public:
    virtual void addObserver(Observer* newObserver) = 0;
    virtual void removeObserver(Observer* deletedObserver) = 0;
    virtual void notify() = 0;
protected:
    virtual ~Subject(){}
};


#endif //ELABORATO_ALESSIO_MASALA_SUBJECT_H
