#ifndef __SALMON__
#define __SALMON__

#include "fish .h"

/**
 * Class name	: Salmon
 *
 * Date		: 17/01/2019
 * Auther	: Akash Anand (51043)
 * Email	: athayyil@hs-mittweida.de
 *
 *
 * Description	:  Class implements a Salmon class that inherits from a Fish class
 */


class salmon:public fish {
public:
  salmon () {} //  Default salmon constructor
  salmon (int s, int r, int x, int y, int bno) ; //  Salmon constructor to initialize attributes
  ~salmon () {}  //  Default salmon destructor

  bool isSalmon () { return true ; }  //  overridden salmon identifier function
  void setLocation (int x, int y) ; //  Reset location for salmon object
};

#endif
