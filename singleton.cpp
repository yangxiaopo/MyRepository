#ifndef __SINGLETON_H
#define __SINGLETON_H
#endif

class Singleton
{
public:
  static Singleton* getinstance();//����Ϊstatic,����������.
private:
  Singleton(){}
  Singleton(Singleton&);
  Singleton& operator=(Singleton&);
};


Singleton.cpp
Singleton* getinstance()
{
  static Singleton *instance=0;//��ʼ�ж�Ϊ0,instance��ֵ֮��,����һֻ���ڵ�,�������¶�����������Ȼû��Ч��(�ƶ������ظ������ᱨ��,�벻����ͺ�������)
  if(instance==NULL) instance=new Singleton();
  return instance;
}
