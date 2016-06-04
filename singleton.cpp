#ifndef __SINGLETON_H
#define __SINGLETON_H
#endif

class Singleton
{
public:
  static Singleton* getinstance();//必须为static,由类名调用.
private:
  Singleton(){}
  Singleton(Singleton&);
  Singleton& operator=(Singleton&);
};


Singleton.cpp
Singleton* getinstance()
{
  static Singleton *instance=0;//开始判断为0,instance有值之后,她是一只存在的,所以重新对她的声明当然没起效用(推断依据重复声明会报错,想不报错就忽略声明)
  if(instance==NULL) instance=new Singleton();
  return instance;
}
