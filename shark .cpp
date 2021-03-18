#include "shark .h"

/*
*
* Argument:
* Return:
* Description:
      constructor for Shark object
*
*/

shark::shark () {
}


/*
*
* Argument: coordinates for the position of the shark along with parameters for base Fish class
* Return:
* Description:
       Default constructor for Shark object
*
*/

shark::shark (int s, int r, int x, int y, int bno) : fish(s, r, x, y, bno) {
  nSalmonEaten = 0 ;
}



/*
*
* Argument:
* Return:
* Description:
      Reset location for Shark object
*
*/

void shark::setLocation (int x, int y) {
  loc.setX (x) ;
  loc.setY (y) ;
}
