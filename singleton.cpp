#ifndef __SINGLETON_H
#define __SINGLETON_H
#include<iostream>//NULL in this head

class Singleton
{
public:
  static Singleton* getinstance();
private:
  Singleton(){}
  Singleton(Singleton&);
  Singleton& operator=(Singleton&);
};

#endif
