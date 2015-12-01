#include "ReceivedBuffer.h"

template <class Type>
ReceivedBuffer<Type>::ReceivedBuffer(int size)
{
#ifdef BOOST
	Vacant = new boost::interprocess::interprocess_semaphore (size);
	Used = new boost::interprocess::interprocess_semaphore (0);
	mtx = new boost::interprocess::interprocess_mutex;
	#else
	Vacant=new QSemaphore(size);
	Used=new QSemaphore();
	mtx=new QMutex();
	#endif;
}

template <class Type>
ReceivedBuffer<Type>::~ReceivedBuffer(void)
{
	delete Vacant;
	delete Used;
	delete mtx;
}

template <class Type>
void ReceivedBuffer<Type>::Enqueue (Type a)
{
#ifdef BOOST
  Vacant->wait();
  mtx->lock();
    queue.push (a);
  mtx->unlock();
  Used->post();
  #else
  Vacant->acquire();
  mtx->lock();
  queue.push(a);
  mtx->unlock();
  Used->release();
  #endif
}

template <class Type>
Type ReceivedBuffer<Type>::Dequeue ()
{
#ifdef BOOST
  Used->wait();
  mtx->lock();
    Type value = queue.front();
    queue.pop ();
  mtx->unlock();
  Vacant->post();
#else
Used->acquire();
mtx->lock();
    Type value = queue.front();
    queue.pop ();
  mtx->unlock();
Vacant->release();
#endif
  return value;
}

class KinectData;
class NanoReceived;
class ArduCopterReceived;
class CameraReceived;
class Command;
class Send;

template class ReceivedBuffer<int>;
#ifdef BOOST
template class ReceivedBuffer< boost::shared_ptr<KinectData> >;
template class ReceivedBuffer< boost::shared_ptr<NanoReceived> >;
template class ReceivedBuffer< boost::shared_ptr<ArduCopterReceived> >;
template class ReceivedBuffer< boost::shared_ptr<CameraReceived> >;
template class ReceivedBuffer< boost::shared_ptr<Command> >;
template class ReceivedBuffer< boost::shared_ptr<Send> >;
#else
template class ReceivedBuffer<  std::shared_ptr<KinectData> >;
template class ReceivedBuffer< std::shared_ptr<NanoReceived> >;
template class ReceivedBuffer< std::shared_ptr<ArduCopterReceived> >;
template class ReceivedBuffer< std::shared_ptr<CameraReceived> >;
template class ReceivedBuffer< std::shared_ptr<Command> >;
template class ReceivedBuffer< std::shared_ptr<Send> >;
#endif
