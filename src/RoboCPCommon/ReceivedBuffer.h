#pragma once
#include <queue>
#ifdef BOOST
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#else // BOOST
#include "qmutex.h"
#include "qsemaphore.h"
#include <memory>
#endif
template <class Type>
class ReceivedBuffer
{
private:
  std::queue<Type> queue;
  #ifdef BOOST
  boost::interprocess::interprocess_mutex* mtx; // Mutex for thread safety
#else // BOOST
QMutex* mtx;
#endif // BOOST
public:
#ifdef BOOST
  boost::interprocess::interprocess_semaphore* Vacant; // Count of vacant places
  boost::interprocess::interprocess_semaphore* Used; // Count of used places
   #else // BOOST
   QSemaphore* Vacant;
   QSemaphore* Used;
   #endif
  ReceivedBuffer(int size);

  ~ReceivedBuffer(void);

  void Enqueue(Type a); // Add to buffer

  Type Dequeue(); // Receive from buffer
};
