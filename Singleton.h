/////////////////////////////////////////////////////////////////////////////
//
// Singleton - modèle Singleton applicable à n'importe quelle classe.
//
/////////////////////////////////////////////////////////////////////////////

#pragma once 

//#include <afx.h>
#include"ConcertoDlg.h"

class CConcertoDlg;

template <typename T>
class Singleton
{
protected:
  // Constructeur/destructeur
  Singleton () { }
  ~Singleton () { }

public:
  // Interface publique
  static T *getInstance (CConcertoDlg *pObject)
  {
    if (NULL == _singleton)
      {
        _singleton = new T(pObject);
      }
    else
      {
      }

    return (static_cast<T*> (_singleton));
  }

  static void kill ()
  {
    if (NULL != _singleton)
      {
        delete _singleton;
        _singleton = NULL;
      }
  }

private:
  // Unique instance
  static T *_singleton;
};

template <typename T>
T *Singleton<T>::_singleton = NULL;