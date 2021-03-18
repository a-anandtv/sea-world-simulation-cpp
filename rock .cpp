#include "rock .h"

/*
*
* Argument:
* Return:
* Description:
      default constructor for rock object
*
*/

rock::rock () {
}


/*
*
* Argument: coordinates for the position of the rock along with parameters for base Sea class
* Return:
* Description:
       parameterized constructor for rock object
*
*/

rock::rock (int x, int y, int bno) : sea( x, y, bno) {
}
