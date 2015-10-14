#pragma once
#include <queue>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

template <class Type>
class ReceivedBuffer
{
private:
  std::queue<Type> queue;
  boost::interprocess::interprocess_mutex* mtx; // Mutex for thread safety

public:
  boost::interprocess::interprocess_semaphore* Vacant; // Count of vacant places
  boost::interprocess::interprocess_semaphore* Used; // Count of used places
   
  ReceivedBuffer(int size);

  ~ReceivedBuffer(void);

  void Enqueue(Type a); // Add to buffer

  Type Dequeue(); // Receive from buffer
};
