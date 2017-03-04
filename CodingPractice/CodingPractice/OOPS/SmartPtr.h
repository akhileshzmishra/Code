#include <iostream>
// Templated smart pointer .. Njoy
using namespace std;

class Ref {
	int count;
public:
	Ref() {
		count = 0;
	}
	void inc() {
		count++ ;
	}

	void deref() {
		count--;
	}

	int getRef() {
		return count;
	}
};

template < typename T>
class container : public Ref{
	T* mRaw;
public:
	container():
	mRaw(0)
	{
	}

	container(T tmp) {
		mRaw = new T(tmp);
		inc();
	}
    
	container(const container& tmp) {
		*mRaw = *tmp.mRaw;
		inc();
		
	}
	
	
	~container()  {
		delete mRaw;
	}
	T* returnPtr() {
		return mRaw;
	}
	T& returnRef() {
		return *mRaw;
	}
};

template < class T>
class SmartPtr {
	container<T>* m_p;
public:
	SmartPtr():
	m_p(0)
	{
	}
	SmartPtr(T* p):
	m_p(*p)
	{
	}
	SmartPtr(const SmartPtr<T>& other):
	m_p(other.m_p)
	{
		if(m_p)
		{
			m_p->inc();
		}
	}
	
	SmartPtr<T>& operator = (const SmartPtr<T>& other)
	{
		if(m_p)
		{
			m_p->deref();
		}
		m_p = other.m_p;
		if(m_p)
		{
			m_p->inc();
		}
	}
	
	T* operator ->()
	{
		return m_p->returnPtr();
	}
	T& operator *()
	{
		return m_p->returnRef();
	}
};
