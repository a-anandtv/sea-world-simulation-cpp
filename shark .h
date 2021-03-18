#ifndef __SHARK__
#define __SHARK__

#include "fish .h"

/**
 * Class name	: Shark
 *
 * Date		: 17/01/2019
 * Auther	: Akash Anand (51043)
 * Email	: athayyil@hs-mittweida.de
 *
 *
 * Description	:  Class implements a Shark class that inherits from a Fish class
                  **  Only additional attribute available is the no of salmon eaten attribute
 */

class shark:public fish {
//attributes
private:
  int nSalmonEaten ;

//functions
public:
  shark () ;  //  Default Shark constructor
  shark (int s, int r, int x, int y, int bno) ; //  Shark constructor to initialize attributes
  ~shark () { } //  Default Shark destructor

  bool isShark () { return true ; } //  overridden shark identifier function
  void setLocation (int x, int y) ; //  Reset location attributs for the Shark object
  void incSalmonEaten () { ++nSalmonEaten ; } //  Increments nSalmonEaten attribute
};

#endif
