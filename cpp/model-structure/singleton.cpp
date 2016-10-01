#include "singleton.h"

Singleton* getInstance(){
  static Singleton* instance=0;
  if(instance==NULL) instance=new Singleton();
  return instance;
}
