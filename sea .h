#ifndef __SEA__
#define __SEA__

/**
 * Class name	: Location
 *
 * Date		: 17/01/2019
 * Auther	: Akash Anand (51043)
 * Email	: athayyil@hs-mittweida.de
 *
 *
 * Description	:  Class implements a location class to hold the location of objects in the simulation (row number, column number)
 */

class location {
//attributes
private:
  int x ; // row number
  int y ; // column number

//function
public:
  location () ; //  default constructor
  location (int i, int j) ; //  parameterized constructor
  ~location () {} //  default destructor

  int getX () { return x ; }  //  getter function
  int getY () { return y ; }  //  getter function
  void setX (int i) { x = i ; } //  setter function for X
  void setY (int j) { y = j ; } //  setter function for Y

  bool operator== (location r) ;  //  overloaded operator
  bool operator== (location* r) ; //  overloaded operator
};


/**
 * Class name	: Sea
 *
 * Date		: 17/01/2019
 * Auther	: Akash Anand (51043)
 * Email	: athayyil@hs-mittweida.de
 *
 *
 * Description	:  Class implements a Sea class that acts as an abstract class for the simulation
                  All other classes inherit from this Sea class
 */

class sea {
//attributes
private:
  int bornOn ;  // holds the start cycle for the object (initialized with the iteration number at which this object is created; defaults to 0)

public:
  location loc ;  //  holds the current location for the object

//functions
public:
  sea () ;  //  default Sea constructor
  sea (int x, int y, int bno = 0) ;  //  parameterized constructor with initialization for Location
  ~sea () {}  // default destructor

  virtual bool isWater () { return false ; }  //  Abstract function to be overridden by derived classes. Returns true when overridden by water.
  virtual bool isRock () { return false ; }  //  Abstract function to be overridden by derived classes. Returns true when overridden by rock.
  virtual bool isFish () { return false ; } //  Abstract function to be overridden by derived classes. Returns true when overridden by fish.
  virtual bool isSalmon () { return false ; }  //  Abstract function to be overridden by derived classes. Returns true when overridden by salmon.
  virtual bool isShark () { return false ; }  //  Abstract function to be overridden by derived classes. Returns true when overridden by shark.
  virtual sea* getPointer () { return this ; }  //  Abstract function to be overridden by derived classes. Returns a pointer to this object.

  int getBirthCycle () { return bornOn ; }  //  getter function for bornOn
};


/**
 * Class name	: Water
 *
 * Date		: 17/01/2019
 * Auther	: Akash Anand (51043)
 * Email	: athayyil@hs-mittweida.de
 *
 *
 * Description	:  Class implements a Water class to simulate water in the simulation
 */

class water : public sea {
//functions
public:
  water () ;  //  default constructor
  water (int x, int y, int bno) ; //  parameterized constructor
  ~water () {}  //  default destructor

  bool isWater () { return true ; } //  overridden water identifier function
  sea* getPointer () { return this ; }  //  overridden getPointer function. Returns pointer to water object.
};


#endif
