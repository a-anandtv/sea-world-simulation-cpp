#include "sea .h"

/*
*
* Argument:
* Return:
* Description:
      Default constructor for location object
*
*/

location::location () {
  x = -1 ;
  y = -1 ;
}


/*
*
* Argument:integer row number, integer column number
* Return:
* Description:
      parameterized constructor for location object
*
*/

location::location (int i, int j) {
  x = i ;
  y = j ;
}


/*
*
* Argument: location element
* Return: bool
* Description:
      returns the == comparison between two Location elements
*
*/

bool location::operator== ( location r ) {

  return ( (x == r.getX ()) && (y == r.getY ()) ) ;
}


/*
*
* Argument: location element
* Return: bool
* Description:
      returns the == comparison between two Location pointer elements
*
*/

bool location::operator== ( location* r ) {

  return ( (x == r -> getX ()) && (y == r -> getY ()) ) ;
}


/*
*
* Argument:
* Return:
* Description:
      Default constructor for Sea object
*
*/

sea::sea () {
  bornOn = 0 ;
  loc.setX (-1) ;
  loc.setY (-1) ;
}


/*
*
* Argument: integer row number, integer column number, integer born on (iteration count)
* Return:
* Description:
      parameterized constructor for sea object
*
*/

sea::sea (int x, int y, int bno) {
  bornOn = bno ;
  loc.setX (x) ;
  loc.setY (y) ;
}


/*
*
* Argument:
* Return:
* Description:
      default constructor for water object
*
*/

water::water () {
}


/*
*
* Argument: coordinates for the position of the water along with parameters for water Sea class
* Return:
* Description:
       parameterized constructor for water object
*
*/

water::water (int x, int y, int bno) : sea( x, y, bno) {
}
