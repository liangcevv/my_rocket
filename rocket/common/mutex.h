#ifndef ROCKET_COMMON_MUTEX_H
#define ROCKET_COMMON_NUTEX_H

#include <string>
#include <memory>
#include <stdio.h>
#include <queue>
#include <pthread.h>

namespace rocket{

template<class T>
class ScopMutext
{
    public:
      ScopMutext(T& muext ) : m_muext(muext){
        m_muext.lock();
        m_is_lock = true;
      }

      ~ScopMutext(){
        m_muext.unlock();
        m_is_lock = false;
      }

      void lock(){
        if(!m_is_lock){
            m_muext.lock();
        }
      }

      void unlock(){
          if(m_is_lock){
            m_muext.unlock();
        }
      }

    private:
      T& m_muext;

      bool m_is_lock{false};

};

class Mutex
{
    public:
      Mutex(){
        pthread_mutex_init(&m_mutex, NULL);
      }
      
      ~Mutex(){
        pthread_mutex_destroy(&m_mutex);
      }

      void lock(){
        pthread_mutex_lock(&m_mutex);
      }

      void unlock(){
          pthread_mutex_unlock(&m_mutex);
      }


    private:
     pthread_mutex_t m_mutex;

};


}

#endif