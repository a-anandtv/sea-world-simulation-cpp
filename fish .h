#ifndef __FISH__
#define __FISH__

#include "sea .h"

/**
 * Class name	: Fish
 *
 * Date		: 17/01/2019
 * Auther	: Akash Anand (51043)
 * Email	: athayyil@hs-mittweida.de
 *
 *
 * Description	:  Class implements a Fish class that inherits from a Sea class
 */

class fish:public sea {
//attributes
private:
  int speed ; //  speed of the fish in number of cells covered in a single cycle
  int reproduceRate ; //  rate of reproduction for the fish

//functions
public:
  fish () ; //  default constructor
  fish (int s, int r, int x, int y, int bno) ; //  parameterized constructor
  ~fish () {} //  default destructor

  // location nextMove () ;  //  randomly chooses a direction and returns target location
  bool isFish () { return true ; }  //  overridden fish identifier function
  void setSpeed (int sp) { speed = sp ; } //  setter function for speed
  void setReproduceRate ( int r ) { reproduceRate = r ; } // setter function for reproduction rate
  int getSpeed () { return speed ; }  // getter function for speed
  int getReproduceRate () { return reproduceRate ; }  //  getter function for reproduceRate
};

#endif
