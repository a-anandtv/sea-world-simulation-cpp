#include "salmon .h"

/*
*
* Argument:
* Return:
* Description:
      parameterized constructor for salmon object
*
*/

salmon::salmon (int s, int r, int x, int y, int bno) :  fish (s, r, x, y, bno) {

}


/*
*
* Argument:
* Return:
* Description:
      Reset location for salmon object
*
*/

void salmon::setLocation (int x, int y) {
  loc.setX (x) ;
  loc.setY (y) ;
}
