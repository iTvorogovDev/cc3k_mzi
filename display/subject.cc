#include <algorithm>
#include "subject.h"
#include <vector>

using namespace std;

Subject::Subject() {
  observers = vector<Observer*>();
}
Subject::~Subject() { 
  for(auto &o : observers){
    delete o;
  }
}

void Subject::attach(Observer *ob) { observers.emplace_back(ob); }

void Subject::detach(Observer *ob) {
  auto index = find(observers.begin(), observers.end(),ob);
  if (index != observers.end()) observers.erase(index);
}

void Subject::notifyObservers() {
  for (auto & ob : observers) ob->notify();
}
