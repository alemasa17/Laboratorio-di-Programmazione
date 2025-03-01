//
// Created by Alessio Masala on 27/02/25.
//

#ifndef ELABORATO_ALESSIO_MASALA_OBSERVER_H
#define ELABORATO_ALESSIO_MASALA_OBSERVER_H


class Observer {
public:
    virtual void update() = 0;
    virtual void draw() = 0;
    ~Observer(){}
};


#endif //ELABORATO_ALESSIO_MASALA_OBSERVER_H
