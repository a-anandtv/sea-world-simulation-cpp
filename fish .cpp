#include "fish .h"

/*
*
* Argument:
* Return:
* Description:
      Default constructor for fish object
*
*/

fish::fish () {
  speed = 1 ;
  reproduceRate = 2 ;
}


/*
*
* Argument:
* Return:
* Description:
      parameterized constructor for fish object
*
*/

fish::fish (int s, int r, int x, int y, int bno) : sea (x, y, bno) {
  speed = s ;
  reproduceRate = r ;
}
