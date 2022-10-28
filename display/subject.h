#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "observer.h"
#include <vector>

using namespace std;

class Subject {
vector<Observer *> observers;
public:
Subject();
void attach(Observer *ob);
void detach(Observer *ob);
void notifyObservers();
virtual ~Subject()=0;
};
#endif
