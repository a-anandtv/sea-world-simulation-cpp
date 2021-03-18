#ifndef __ROCK__
#define __ROCK__

#include "sea .h"


/**
 * Class name	: Rock
 *
 * Date		: 17/01/2019
 * Auther	: Akash Anand (51043)
 * Email	: athayyil@hs-mittweida.de
 *
 *
 * Description	:  Class implements a rock class to simulate a rock in the simulation
 */

class rock : public sea {
//functions
public:
  rock () ; //  default constructor
  rock (int x, int y, int bno) ;  //  parameterized constructor
  ~rock () {} //  default destructor

  bool isRock () { return true ; }  //  overridden rock identifier function
};

#endif
