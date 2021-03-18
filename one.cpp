/**
 * Sheet 4 : Sea simulation
 *
 * Date		: 17/01/2019
 * Auther	: Akash Anand (51043)
 * Email	: athayyil@hs-mittweida.de
 *
 *  Current architecture :
      Class Simulation - "Encapsulates all other classes and runs the simulation"

      Class Sea - "Abstract class from which all other classes are derived"
          * Class Water - "Derived from Sea"
                          "Class holds default cells in sea"
          * Class Rock -  "Derived from Sea"
                          "Class for rocks  in sea"
          * Class Fish -  "Derived from Sea"
                          "Abstract class from which all other fishes are derived"
                          "Holds attributes common to fishes but not water or rocks"
                * Class Salmon -  "Derived from Fish"
                                  "Holds attributes for Salmons"
                * Class Sharks -  "Derived from Fish"
                                  "Holds attributes for Sharks"
 *
 *
 * Points to note :
      * Simulation runs for cycles rather than seconds.
      * Reproduction stops if no water cells are available in sea.

 * Existing bugs :
      * Simulation pushes a fish in the direction of execution causing it to be moved again in the same cycle (*scenerio not handled*)
      * Simulation assumes that only two fishes can fall on a cell at once causing them to reproduce (*scenerio not handled*)
            - However, more than one fish can randomly move into a single cell (*scenerio not handled*)
      * Simulation does not handle cases where a fish could be surrounded by rocks when the simulation is initialized (*scenerio not handled*)
      * Simulation fails for certain generated scenarios where a fish tries to move but reaches out of bounds
            - Issue is found to be in *moveTo* and *getPossibleMoves* functions

 * Future improvements :
      * A better execution of movements (probably using an additional <execution stack>)
      * A design update where in fishes can decide moves and being aware of its surroundings
 *
 */

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>
#include "sea .h"
#include "fish .h"
#include "salmon .h"
#include "shark .h"
#include "rock .h"



/**
 * Class name	: Simulation
 *
 * Date		: 17/01/2019
 * Auther	: Akash Anand (51043)
 * Email	: athayyil@hs-mittweida.de
 *
 *
 * Description	:  Class implements a simulation class to handle the simulation
 */

class simulation {
//attributes
private:
  //  initialized simulation attributes
  int nRows ; //  number of rows in simulation field
  int nCollumns ; //  number of columns in simulation field
  int nCycles ; //  cycles/time the simulation has to run for
  float fSharksPercentage ; //  percentage of initial cells for sharks
  float fSalmonPercentage ; //  percentage of initial cells for salmons
  float fRocksPercentage ;  //  percentage of initial cells for rocks
  int nMaxSharkAge ; //  maximum age for sharks
  int nMaxSalmonAge ; //  maximum age for salmons
  int nMaxRockAge ; //  maximum age for rocks
  int nFish2Rock ;  //  number of fishes to die before a rock is formed
  int nMaxSharkSpeed ;  //  speed for sharks
  int nMaxSalmonSpeed ; //  speed for salmons
  int nSalmonRRate ;  //  reproduction rate for salmons
  int nSharksRRate ;  //  reproduction rate for sharks

  //  calculated attributes
  int nSalmons ;  //  number of salmons
  int nSharks ; //  number of sharks
  int nRocks ;  //  number of rocks
  int nSalmonsBorn ;  //  number of salmons born
  int nSharksBorn ; //  number of sharks born
  int nRocksCreated ; //  number of rocks created
  int nSalmonsDead ;  //  number of salmons that died during the simulation
  int nSharksDead ; //  number of sharks that died during the simulation
  int nRocksRemoved ; //  number of rock that were removed from the simulation due to crossing its max age
  int nSalmonsEaten ; //  number of salmons eaten by sharks
  int nCurrentCycle ; //  the current iteration (used to set born on iteration for fishes. helps calculate age)

public:
  //  simulation environment and other objects
  std::vector< std::vector< std::vector<sea *> > > _sea_ ;  //  a 3 dimensional platform for the simulation to run on.
                                                  //  3rd dimension enables cases where more than 1 fish falls on a single cell (2 salmons or 2 sharks)
  std::vector< std::vector<sea *> > _sea_row_ ; //  the row vector that can be used to initialize the 3d space
  std::vector<sea *> _sea_cell_ ; //  a single cell representing a single cell on the 3d space

  std::vector<rock *> v_rocks ; //  rocks vector to store all rock object
  std::vector<water *> v_water ;  //  water vector to store all water objects
  std::vector<salmon *> v_salmons ;  //  salmons vector to store all salmon objects
  std::vector<shark *> v_sharks ;  //  sharks vector to store all shark objects

//functions
public:
  simulation () ; //  default simulation constructor
  simulation (int m, int n, int c) ; //  parameterized constructor that sets dimensions for the simulation environment and number of cycles
  ~simulation () {} //  default simulation destructor

  int getNRows () { return nRows ; }  //  getter function for nRows
  int getNCollumns () { return nCollumns ; }  // getter function for nCollumns
  int getNCycles () { return nCycles ; }  //  getter function for nCycles
  float getSharksPercentage () { return fSharksPercentage ; } //  getter function for fSharksPercentage
  float getSalmonPercentage () { return fSalmonPercentage ; } //  getter function for fSalmonPercentage
  float getRocksPercentage () { return fRocksPercentage ; } //  getter function for fRocksPercentage

  void setNRows (int n) { nRows = n ; } //  setter function for nRows
  void setNCollumns (int n) { nCollumns = n ; } //  setter function for nCollumns
  void setCycles (int n) { nCycles = n ; }  //  setter function for nCycles
  void setFSharks (float f) { fSharksPercentage = f ; } //  setter function for fSharksPercentage
  void setFSalmons (float f) { fSalmonPercentage = f ; }  //  setter function for fSalmonPercentage
  void setFRocks (float f) { fRocksPercentage = f ; } //  setter function for fRocksPercentage
  void setNMaxSharkAge (int n) { nMaxSharkAge = n ; } //  setter function for nMaxSharkAge
  void setNMaxSalmonAge (int n) { nMaxSalmonAge = n ; } //  setter functin for nMaxSalmonAge
  void setNMaxRockAge (int n) { nMaxRockAge = n ; } //  setter function for nMaxRockAge
  void setNFish2Rock (int n) { nFish2Rock = n ; }  //  setter function for nFish2Rock
  void setNMaxSharkSpeed (int n) { nMaxSharkSpeed = n ; }  //  setter function for nMaxSharkSpeed
  void setNMaxSalmonSpeed (int n) { nMaxSalmonSpeed = n ; } //  setter function for nMaxSalmonSpeed
  void setNSalmonRRate (int n) { nSalmonRRate = n ; }  //  setter function for nSalmonRRate
  void setNSharksRRate (int n) { nSharksRRate = n ; } //  setter function for nSharksRRate

  int generate () ;  //  generates the simulation field (the sea of nRows X nCollumns cells)
  int initialize () ;  //  initializes the sea with required number of sharks, salmon and rocks
  int simulate () ; //  starts and simulates the set environment for the set number of cycles
  int getPossibleMoves (int i, int j) ; //  checks for possible moves the fish can take from its current position i, j
  void moveTo (int i, int j, location dest) ; //  moves fish from i,j to dest location
  void reproduce (location at) ;  //  reproduce for fish at locatio 'at'
  void dieToAge () ;  //  kills off fishes and rocks based on the set max age parameters
  // void calculateAttributes () ; //  calculates values for the calculated attributes

  std::string getStatus () ; //  returns string with current status of the simulations environment
  std::string toString () ;  //  returns the results for a completed simulation * To be run after simulate()

};

std::string int2str ( int n ) ; //  function converts an integer value to a string
std::string num2char ( int n ) ;  //  function returns the string equivalent to the passed digit
unsigned int intFloor (float f) ; //  returns the integer floor value to passed floating point number






//-------------------------------------------------------------------------------
//*
//*
//*
//*
//  __MAIN__
int main () {

  simulation* sim1 = new simulation (5, 5, 2) ;

  std::cout << "\nGenerating simulation... " ;

  sim1 -> generate () ;

  std::cout << "\nSimulation generated! " << std::endl ;

  // std::cout << "------------------" << std::endl ;
  // std::cout << "Current status : " << std::endl ;
  // std::cout << "------------------" << std::endl ;
  //
  // std::cout << sim1 -> getStatus () ;


  sim1 -> setFSalmons (0.3) ; //  set salmon percenetage
  sim1 -> setFSharks (0.09) ;  //  set sharks percentage
  sim1 -> setFRocks (0.05) ; //  set rocks percentage

  sim1 -> setNMaxSalmonSpeed (1) ;
  sim1 -> setNMaxSharkSpeed (1) ;


  std::cout << "\nInitializing simulation... " ;

  sim1 -> initialize () ;

  std::cout << "\nSimulation initialized! " << std::endl  ;

  // std::cout << "------------------" << std::endl ;
  // std::cout << "Current status : " << std::endl ;
  // std::cout << "------------------" << std::endl ;
  //
  // std::cout << sim1 -> getStatus () ;

  std::cout << "\nSimulation running for " << sim1 -> getNCycles () << " iterations..." << std::endl  ;

  sim1 -> simulate () ;

  // std::cout << "------------------" << std::endl ;
  // std::cout << "Current status : " << std::endl ;
  // std::cout << "------------------" << std::endl ;
  //
  // std::cout << sim1 -> getStatus () ;

  std::cout << "------------------" << std::endl ;
  std::cout << "Final status : " << std::endl ;
  std::cout << "------------------" << std::endl ;

  std::cout << sim1 -> toString () ;

}

//*
//*
//*
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------



/*
*
* Argument:
* Return:
* Description:
      Default constructor for simulation object
*
*/

simulation::simulation () {

  nRows = 10 ;
  nCollumns = 10 ;
  nCycles = 100 ;
  fSharksPercentage = 0.05 ;
  fSalmonPercentage = 0.1 ;
  fRocksPercentage = 0.07 ;
  nMaxSharkAge = 30 ;
  nMaxSalmonAge = 20 ;
  nMaxRockAge = 200 ;
  nFish2Rock = 500 ;
  nMaxSharkSpeed = 1 ;
  nMaxSalmonSpeed = 1 ;
  nSalmonRRate = 8 ;
  nSharksRRate = 3 ;
  //  calculated attributes
  nSalmons = 0 ;
  nSharks = 0 ;
  nRocks = 0 ;
  nSalmonsBorn = 0 ;
  nSharksBorn = 0 ;
  nRocksCreated = 0 ;
  nSalmonsDead = 0 ;
  nSharksDead = 0 ;
  nRocksRemoved = 0 ;
  nSalmonsEaten = 0 ;
  nCurrentCycle = 0 ;
}


/*
*
* Argument: integer, integer, integer
* Return:
* Description:
      parameterized constructor for simulation object
*
*/

simulation::simulation (int m, int n, int c) {

  nRows = m ;
  nCollumns = n ;
  nCycles = c ;
  fSharksPercentage = 0.05 ;
  fSalmonPercentage = 0.1 ;
  fRocksPercentage = 0.07 ;
  nMaxSharkAge = 30 ;
  nMaxSalmonAge = 20 ;
  nMaxRockAge = 200 ;
  nFish2Rock = 500 ;
  nMaxSharkSpeed = 1 ;
  nMaxSalmonSpeed = 1 ;
  nSalmonRRate = 8 ;
  nSharksRRate = 3 ;
  //  calculated attributes
  nSalmons = 0 ;
  nSharks = 0 ;
  nRocks = 0 ;
  nSalmonsBorn = 0 ;
  nSharksBorn = 0 ;
  nRocksCreated = 0 ;
  nSalmonsDead = 0 ;
  nSharksDead = 0 ;
  nRocksRemoved = 0 ;
  nSalmonsEaten = 0 ;
  nCurrentCycle = 0 ;
}


/*
*
* Argument:
* Return:
* Description:
      generates the simulation field (the sea of nRows X nCollumns cells)
*
*/

int simulation::generate () {

  for (int i = 0; i < nRows; ++i) {
    for (int j = 0; j < nCollumns; ++j) {
      v_water.push_back (new water (i,j,0)) ; //  creates new water object at location i,j with BornOn attribute 0
      _sea_cell_.push_back(v_water.back() -> getPointer ()) ;
      _sea_row_.push_back (_sea_cell_) ;
      _sea_cell_.clear () ;
    }
    _sea_.push_back(_sea_row_) ;
    _sea_row_.clear();
  }

  return 1 ;
}


/*
*
* Argument:
* Return:
* Description:
      initializes the sea with required number of sharks, salmon and rocks
*
*/

int simulation::initialize () {

  int x, y, pos ;

  for (int i = 1; i <= intFloor ( float (nRows) * float (nCollumns) * fRocksPercentage) ; ++i) {

    srand (time (0)) ;
    pos = rand() % v_water.size () ;

    x = v_water[pos] -> loc.getX () ;
    y = v_water[pos] -> loc.getY () ;

    // std::cout << "Loop " << i << ": Random pos : " << pos << std::endl;
    v_rocks.push_back (new rock ( x, y, 0)) ;
    v_water.erase (v_water.begin () + pos) ;
    _sea_ [x][y].front () = v_rocks.back () -> getPointer () ;

    ++nRocks ;
  }

  for (int i = 1; i <= intFloor ( float (nRows) * float (nCollumns) * fSalmonPercentage) ; ++i) {

    srand (time (0)) ;
    pos = rand() % v_water.size () ;

    x = v_water[pos] -> loc.getX () ;
    y = v_water[pos] -> loc.getY () ;

    // std::cout << "Loop " << i << ": Random pos : " << pos << std::endl;
    v_salmons.push_back (new salmon ( nMaxSalmonSpeed, nSalmonRRate, x, y, 0)) ;
    v_water.erase (v_water.begin () + pos) ;
    _sea_ [x][y].front() = v_salmons.back () -> getPointer () ;

    ++nSalmons ;
  }

  for (int i = 1; i <= intFloor ( float (nRows) * float (nCollumns) * fSharksPercentage) ; ++i) {

    srand (time (0)) ;
    pos = rand() % v_water.size () ;

    x = v_water[pos] -> loc.getX () ;
    y = v_water[pos] -> loc.getY () ;

    // std::cout << "Loop " << i << ": Random pos : " << pos << std::endl;
    v_sharks.push_back (new shark ( nMaxSharkSpeed, nSharksRRate, x, y, 0)) ;
    v_water.erase (v_water.begin () + pos) ;
    _sea_ [x][y].front() = v_sharks.back () -> getPointer () ;

    ++nSharks ;
  }

  return 1 ;
}


/*
*
* Argument:
* Return:
* Description:
      starts and simulates the set environment for the set number of cycles
*
*/

int simulation::simulate () {

  location l ;
  int ch ;

  for (int p = 0; p < nCycles; ++p) {

    nCurrentCycle = p + 1 ;

    // std::cout << "I:" << nCurrentCycle << std::endl ;

    for (int i = 0; i < nRows; ++i) {
      for (int j = 0; j < nCollumns; ++j) {

        // std::cout << _sea_ [i][j].front () -> isFish () ;

        if ( _sea_ [i][j].front () -> isFish () ) {

          int speed ;
          if ( _sea_ [i][j].front () -> isSalmon () )
            speed = nMaxSalmonSpeed ;
          else if ( _sea_ [i][j].front () -> isShark () )
            speed = nMaxSharkSpeed ;

          for (int s = 0; s < speed; ++s) {

            int ch = getPossibleMoves (i, j) ;

            // std::cout << "Possible moves:" ;
            // for ( int t = 0; t < v.size (); ++t )
            //   std::cout << v[t] << "," ;

            // std::cout << "here" << std ::endl ;

            if ( ch >= 0 ) {

              if ( ch == 0 ) {
                l.setX ( i - 1 ) ;
                l.setY ( j ) ;
              }
              else if ( ch == 1 ) {
                l.setX ( i ) ;
                l.setY ( j + 1 ) ;
              }
              else if ( ch == 2 ) {
                l.setX ( i + 1 ) ;
                l.setY ( j ) ;
              }
              else if ( ch == 3 ) {
                l.setX ( i ) ;
                l.setY ( j - 1 ) ;
              }
              // std::cout << "dest:" << i << j << ":" << l.getX () << "," << l.getY () << std::endl ;
              // moveTo (i, j, l) ;
            }
          }
        }
      }
    }

    dieToAge () ;
  }

  // calculateAttributes () ;
  return 1 ;
}


/*
*
* Argument: integer, integer
* Return:
* Description:
      checks for possible moves the fish can take from its current position i, j
*
*/

int simulation::getPossibleMoves (int i, int j) {

  std::vector<int> v ;

  if ( (i == 0) && (j == 0) ) {

    if ( ! (_sea_ [i][j + 1].front () -> isRock ()) )
      v.push_back (1) ;

    if ( ! (_sea_ [i + 1][j].front () -> isRock ()) )
      v.push_back (2) ;
  }
  else if ( (i == 0) && (j > 0) ) {

    if ( ! (_sea_ [i][j + 1].front () -> isRock ()) )
      v.push_back (1) ;

    if ( ! (_sea_ [i + 1][j].front () -> isRock ()) )
      v.push_back (2) ;

    if ( ! (_sea_ [i][j - 1].front () -> isRock ()) )
      v.push_back (3) ;
  }
  else if ( (i == 0) && (j == nCollumns - 1) ) {

    if ( ! (_sea_ [i + 1][j].front () -> isRock ()) )
      v.push_back (2) ;

    if ( ! (_sea_ [i][j - 1].front () -> isRock ()) )
      v.push_back (3) ;
  }
  else if ( (i > 0) && (j == 0) ) {

    if ( ! (_sea_ [i - 1][j].front () -> isRock ()) )
      v.push_back (0) ;

    if ( ! (_sea_ [i][j + 1].front () -> isRock ()) )
      v.push_back (1) ;

    if ( ! (_sea_ [i + 1][j].front () -> isRock ()) )
      v.push_back (2) ;
  }
  else if ( (i > 0) && (j == nCollumns - 1) ) {

    if ( ! (_sea_ [i - 1][j].front () -> isRock ()) )
      v.push_back (0) ;

    if ( ! (_sea_ [i + 1][j].front () -> isRock ()) )
      v.push_back (2) ;

    if ( ! (_sea_ [i][j - 1].front () -> isRock ()) )
      v.push_back (3) ;
  }
  else if ( (i == nRows - 1) && (j == 0) ) {

    if ( ! (_sea_ [i - 1][j].front () -> isRock ()) )
      v.push_back (0) ;

    if ( ! (_sea_ [i][j + 1].front () -> isRock ()) )
      v.push_back (1) ;
  }
  else if ( (i == nRows - 1) && (j > 0) ) {

    if ( ! (_sea_ [i - 1][j].front () -> isRock ()) )
      v.push_back (0) ;

    if ( ! (_sea_ [i][j + 1].front () -> isRock ()) )
      v.push_back (1) ;

    if ( ! (_sea_ [i][j - 1].front () -> isRock ()) )
      v.push_back (3) ;
  }
  else if ( (i == nRows - 1) && (j == nCollumns - 1) ) {

    if ( ! (_sea_ [i - 1][j].front () -> isRock ()) )
      v.push_back (0) ;

    if ( ! (_sea_ [i][j - 1].front () -> isRock ()) )
      v.push_back (3) ;
  }
  else if ( (i > 0) && (j > 0) ) {

    if ( ! (_sea_ [i - 1][j].front () -> isRock ()) )
      v.push_back (0) ;

    if ( ! (_sea_ [i][j + 1].front () -> isRock ()) )
      v.push_back (1) ;

    if ( ! (_sea_ [i + 1][j].front () -> isRock ()) )
      v.push_back (2) ;

    if ( ! (_sea_ [i][j - 1].front () -> isRock ()) )
      v.push_back (3) ;
  }

  if ( v.size () ) {
    srand ( time(0) ) ;
    return v[ rand() % v.size () ] ;
  }
  else return -1 ;
}


/*
*
* Argument: integer, integer, location
* Return:
* Description:
      moves fish from i,j to dest location
*
*/

void simulation::moveTo (int i, int j, location dest)  {

  // std::cout << "Start move!" ;

  if ( _sea_ [dest.getX ()][dest.getY ()].front () -> isWater () ) {    //  destination is water

    // std::cout << "!destination is water!" ;

    if ( _sea_ [i][j].front () == _sea_ [i][j].back () ) {    //  source has only one fish

      // std::cout << "|source has only one fish|" ;

      sea* temp = _sea_ [i][j].front () ;
      _sea_ [i][j].front () = _sea_ [dest.getX ()][dest.getY ()].front () ;
      _sea_ [dest.getX ()][dest.getY ()].front () = temp ;

      _sea_ [i][j].front () -> loc.setX (i) ;
      _sea_ [i][j].front () -> loc.setY (j) ;
      _sea_ [dest.getX ()][dest.getY ()].front () -> loc.setX (dest.getX ()) ;
      _sea_ [dest.getX ()][dest.getY ()].front () -> loc.setY (dest.getY ()) ;

      // std::cout << "|finished move|" ;
    }
    else {    //  source has more than one fish (assumably reproducing)

      // std::cout << "|source has more than 1 fish|" ;

      int p ;

      for ( p = 0; p < v_water.size (); ++p) {
        if ( v_water[p] -> loc == dest )
          break ;
      }

      _sea_ [dest.getX ()][dest.getY ()].front () = _sea_ [i][j].front () ;
      _sea_ [dest.getX ()][dest.getY ()].front () -> loc.setX (dest.getX ()) ;
      _sea_ [dest.getX ()][dest.getY ()].front () -> loc.setY (dest.getY ()) ;
      _sea_ [i][j].erase ( _sea_ [i][j].begin () ) ;
      v_water.erase ( v_water.begin () + p ) ;

      // std::cout << "|finished move|" ;
    }

  }
  else if ( _sea_ [i][j].front () -> isSalmon () ) {    //  source is a salmon

    if ( _sea_ [dest.getX ()][dest.getY ()].front () -> isShark () ) {    //  destination is a shark

      int p ;

      for ( p = 0; p < v_sharks.size (); ++p) {
        if ( v_sharks[p] -> loc == (new location (dest.getX (),dest.getY ())) )
          break ;
      }

      v_sharks[p] -> incSalmonEaten () ;

      if ( _sea_ [i][j].front () == _sea_ [i][j].back () ) {    // source had only one salmon and destination is a shark

        for ( p = 0; p < v_salmons.size (); ++p) {
          if ( v_salmons[p] -> loc == (new location (i,j)) )
            break ;
        }

        v_salmons.erase ( v_salmons.begin () + p ) ;
        --nSalmons ;

        v_water.push_back (new water (i,j,0)) ;
        _sea_ [i][j].front () = ( v_water.back () -> getPointer () ) ;
      }
      else {    //  source had 2 salmons and the destination is a shark

        for ( p = 0; p < v_salmons.size (); ++p) {
          if ( v_salmons[p] -> getPointer () == _sea_ [i][j].front () )
            break ;
        }

        v_salmons.erase ( v_salmons.begin () + p ) ;
        --nSalmons ;
        _sea_ [i][j].erase (_sea_ [i][j].begin ()) ;
      }
    }
    else if ( _sea_ [dest.getX ()][dest.getY ()].front () -> isSalmon () ) {    //  destination is also a salmon

      v_water.push_back (new water (i,j,0)) ;
      _sea_ [dest.getX ()][dest.getY ()].push_back ( _sea_ [i][j].front () -> getPointer () ) ;
      _sea_ [i][j].front () = ( v_water.back () -> getPointer () ) ;

      reproduce (dest) ;
    }
  }
  else if ( _sea_ [i][j].front () -> isShark () ) {   //  source is a shark

    if ( _sea_ [dest.getX ()][dest.getY ()].front () -> isSalmon () ) {   //  destination is a salmon

      int p ;

      for ( p = 0; p < v_sharks.size (); ++p) {
        if ( v_sharks[p] -> loc == (new location (i,j)) )
          break ;
      }

      if ( _sea_ [i][j].front () == _sea_ [i][j].back () ) {    //  destination has only one salmon

        v_sharks[p] -> incSalmonEaten () ;

        for ( p = 0; p < v_salmons.size (); ++p) {
          if ( v_salmons[p] -> getPointer () == _sea_ [i][j].front () )
            break ;
        }

        v_salmons.erase ( v_salmons.begin () + p ) ;
        --nSalmons ;
      }
      else {    //  destination has 2 salmons (assumably reproducing)
        v_sharks[p] -> incSalmonEaten () ;
        v_sharks[p] -> incSalmonEaten () ;

        for ( p = 0; p < v_salmons.size (); ++p) {
          if ( v_salmons[p] -> getPointer () == _sea_ [i][j].front () )
            break ;
        }

        v_salmons.erase ( v_salmons.begin () + p ) ;

        for ( p = 0; p < v_salmons.size (); ++p) {
          if ( v_salmons[p] -> getPointer () == _sea_ [i][j].front () )
            break ;
        }

        v_salmons.erase ( v_salmons.begin () + p ) ;

        nSalmons -= 2 ;
      }

      v_water.push_back (new water (i,j,0)) ;
      _sea_ [dest.getX ()][dest.getY ()].front () = _sea_ [i][j].front () ;
      _sea_ [dest.getX ()][dest.getY ()].front () -> loc.setX (dest.getX ()) ;
      _sea_ [dest.getX ()][dest.getY ()].front () -> loc.setY (dest.getY ()) ;
      _sea_ [i][j].front () = ( v_water.back () -> getPointer () ) ;
    }
    else if ( _sea_ [dest.getX ()][dest.getY ()].front () -> isShark () ) {   //  destination is also a shark

      v_water.push_back (new water (i,j,0)) ;
      _sea_ [dest.getX ()][dest.getY ()].push_back ( _sea_ [i][j].front () -> getPointer () ) ;
      _sea_ [i][j].front () = ( v_water.back () -> getPointer () ) ;

      reproduce (dest) ;
    }
  }


}


/*
*
* Argument: location
* Return:
* Description:
      reproduce for fish at locatio 'at'
*
*/

void simulation::reproduce (location at) {

  int rrate, pos, x, y ;
  int on = nCurrentCycle ;

  if ( _sea_ [at.getX ()][at.getY ()].front () -> isSalmon () ) {

    rrate = nSalmonRRate ;

    while ( (! v_water.empty ()) && rrate ) {

      srand (time (0)) ;
      pos = rand() % v_water.size () ;

      x = v_water[pos] -> loc.getX () ;
      y = v_water[pos] -> loc.getY () ;

      // std::cout << "Loop " << i << ": Random pos : " << pos << std::endl;
      v_salmons.push_back (new salmon ( nMaxSalmonSpeed, nSalmonRRate, x, y, on)) ;
      v_water.erase (v_water.begin () + pos) ;
      _sea_ [x][y].front() = v_salmons.back () -> getPointer () ;

      ++nSalmons ;
      ++nSalmonsBorn ;
      --rrate ;
    }
  }
  else if ( _sea_ [at.getX ()][at.getY ()].front () -> isSalmon () ) {

    rrate = nSharksRRate ;

    while ( (! v_water.empty ()) && rrate ) {

      srand (time (0)) ;
      pos = rand() % v_water.size () ;

      x = v_water[pos] -> loc.getX () ;
      y = v_water[pos] -> loc.getY () ;

      // std::cout << "Loop " << i << ": Random pos : " << pos << std::endl;
      v_sharks.push_back (new shark ( nMaxSharkSpeed, nSharksRRate, x, y, on)) ;
      v_water.erase (v_water.begin () + pos) ;
      _sea_ [x][y].front() = v_sharks.back () -> getPointer () ;

      ++nSharks ;
      ++nSharksBorn ;
      --rrate ;
    }
  }
}


/*
*
* Argument:
* Return:
* Description:
      kills off fishes and rocks based on the set max age parameters
*
*/

void simulation::dieToAge () {

  // nSalmons = v_salmons.size () ;
  // nSharks = v_sharks.size () ;
  // nRocks = v_rocks.size () ;

  for (int i = 0; i < v_salmons.size (); ++i ) {

    if ( (nCurrentCycle - v_salmons[i] -> getBirthCycle ()) > nMaxSalmonAge ) {

      ++nSalmonsDead ;

      if ( nSalmonsDead + nSharksDead == nFish2Rock ) {

        v_rocks.push_back (new rock (v_salmons[i] -> loc.getX (), v_salmons[i] -> loc.getY (), nCurrentCycle)) ;
        _sea_ [v_salmons[i] -> loc.getX ()][v_salmons[i] -> loc.getY ()].front () = v_rocks.back() -> getPointer () ;
        ++nRocksCreated ;
      }
      else {

        v_water.push_back (new water (v_salmons[i] -> loc.getX (), v_salmons[i] -> loc.getY (), 0)) ;
        _sea_ [v_salmons[i] -> loc.getX ()][v_salmons[i] -> loc.getY ()].front () = v_water.back() -> getPointer () ;
      }

      v_salmons.erase (v_salmons.begin () + i) ;
    }
  }

  for (int i = 0; i < v_sharks.size (); ++i ) {

    if ( (nCurrentCycle - v_sharks[i] -> getBirthCycle ()) > nMaxSharkAge ) {

      ++nSharksDead ;

      if ( nSalmonsDead + nSharksDead == nFish2Rock ) {

        v_rocks.push_back (new rock (v_sharks[i] -> loc.getX (), v_sharks[i] -> loc.getY (), nCurrentCycle)) ;
        _sea_ [v_sharks[i] -> loc.getX ()][v_sharks[i] -> loc.getY ()].front () = v_rocks.back() -> getPointer () ;
        ++nRocksCreated ;
      }
      else {

        v_water.push_back (new water (v_sharks[i] -> loc.getX (), v_sharks[i] -> loc.getY (), 0)) ;
        _sea_ [v_sharks[i] -> loc.getX ()][v_sharks[i] -> loc.getY ()].front () = v_water.back() -> getPointer () ;
      }

      v_sharks.erase (v_sharks.begin () + i) ;
    }
  }

  for (int i = 0; i < v_rocks.size (); ++i ) {

    if ( (nCurrentCycle - v_rocks[i] -> getBirthCycle ()) > nMaxRockAge ) {

      ++nRocksRemoved ;

      v_water.push_back (new water (v_rocks[i] -> loc.getX (), v_rocks[i] -> loc.getY (), 0)) ;
      _sea_ [v_rocks[i] -> loc.getX ()][v_rocks[i] -> loc.getY ()].front () = v_water.back() -> getPointer () ;

      v_rocks.erase (v_rocks.begin () + i) ;
    }
  }
}


/*
*
* Argument:
* Return:
* Description:
      returns string with current status of the simulations environment
*
*/

std::string simulation::getStatus () {

  std::string msg ;

  msg = "" ;
  msg += "\nSimulation field : " + int2str (nRows) + "X" + int2str (nCollumns) ;
  msg += "\nCycles : " + int2str (nCycles) ;
  msg += "\nField share : Salmon - " + int2str (intFloor (float(nRows)*float(nCollumns)*(fSalmonPercentage)))
          + "; Sharks - " + int2str (intFloor (float(nRows)*float(nCollumns)*(fSharksPercentage)))
          + "; Rocks - " + int2str (intFloor (float(nRows)*float(nCollumns)*(fRocksPercentage))) ;
  msg += "\nInitialized with : " ;

  for (int i = 0; i < nRows; ++i) {
    for (int j = 0; j < nCollumns; ++j) {
      if ( _sea_ [i][j].front() -> isWater () ) {
        msg += "\n" + int2str (i) + "," + int2str (j) + ": Water [" + int2str (_sea_ [i][j].front() -> loc.getX ()) + "," + int2str (_sea_ [i][j].front() -> loc.getY ()) + ";" + int2str (_sea_ [i][j].front() -> getBirthCycle ()) + "]" ;
      }
      else if ( _sea_ [i][j].front() -> isRock () ) {
        msg += "\n" + int2str (i) + "," + int2str (j) + ": Rock [" + int2str (_sea_ [i][j].front() -> loc.getX ()) + "," + int2str (_sea_ [i][j].front() -> loc.getY ()) + ";" + int2str (_sea_ [i][j].front() -> getBirthCycle ()) + "]" ;
      }
      else if ( _sea_ [i][j].front() -> isSalmon () ) {
        msg += "\n" + int2str (i) + "," + int2str (j) + ": Salmon [" + int2str (_sea_ [i][j].front() -> loc.getX ()) + "," + int2str (_sea_ [i][j].front() -> loc.getY ()) + ";" + int2str (_sea_ [i][j].front() -> getBirthCycle ()) + "]" ;
      }
      else if ( _sea_ [i][j].front() -> isShark () ) {
        msg += "\n" + int2str (i) + "," + int2str (j) + ": Shark [" + int2str (_sea_ [i][j].front() -> loc.getX ()) + "," + int2str (_sea_ [i][j].front() -> loc.getY ()) + ";" + int2str (_sea_ [i][j].front() -> getBirthCycle ()) + "]" ;
      }
      else
        msg += "\n" + int2str (i) + "," + int2str (j) + ": Error!!!\n" ;
    }
  }

  msg += "\nWater : " + int2str (v_water.size ()) + "; Rocks : " + int2str (v_rocks.size ()) + "; Salmon : " + int2str (v_salmons.size ()) + "; Sharks : " + int2str (v_sharks.size ()) + "\n" ;

  return msg ;
}


/*
*
* Argument:
* Return:
* Description:
      returns the results for a completed simulation * To be run after simulate()
*
*/

std::string simulation::toString () {

  std::string msg = "" ;

  msg += "\n Sharks left by the end of the simulation : " + int2str (nSharks) ;
  msg += "\n Salmons left by the end of the simulation : " + int2str (nSalmons) ;
  msg += "\n Rocks left by the end of the simulation : " + int2str (nRocks) ;
  msg += "\n Salmons died by the end of the simulation : " + int2str (nSalmonsDead) ;
  msg += "\n Sharks died by the end of the simulation : " + int2str (nSharksDead) ;
  msg += "\n Salmons created newly by the end of the simulation : " + int2str (nSalmonsBorn) ;
  msg += "\n Sharks created newly by the end of the simulation : " + int2str (nSharksBorn) ;
  msg += "\n Rocks created newly by the end of the simulation : " + int2str (nRocksCreated) ;
  msg += "\n Salmons eaten by sharks by the end of the simulation : " + int2str (nSalmonsEaten) ;
  msg += "\n Do Salmons and Sharks live with each other in the end or one species vanish? " ;

  if ( nSalmons > nSharks ) {
    msg += "\n\t Yes, Salmons and Sharks can live wit heach other. \n" ;
  }
  else {
    msg += "\n\t No, Sharks dominate Salmons and Salmons vanish. \n" ;
  }

  return msg ;
}


/*
*
* Argument: int
* Return: string
* Description:
      returns the string equivalent of the passed integer digit
*
*/

std::string num2char ( int n ) {
	if ( n == 0 )
		return "0" ;
	else if ( n == 1 )
		return "1" ;
	else if ( n == 2 )
		return "2" ;
	else if ( n == 3 )
		return "3" ;
	else if ( n == 4 )
		return "4" ;
	else if ( n == 5 )
		return "5" ;
	else if ( n == 6 )
		return "6" ;
	else if ( n == 7 )
		return "7" ;
	else if ( n == 8 )
		return "8" ;
	else if ( n == 9 )
		return "9" ;
	else
		return "-" ;
}


/*
*
* Argument: int
* Return: string
* Description:
      returns the string equivalent of the passed integer number
*
*/

std::string int2str ( int n ) {

	std::string a ;
	a = "" ;

  if ( n > 0 ) {
  	while ( n ) {

  		a = num2char ( n % 10 ) + a ;
  		n /= 10 ;

  	}
  }
  else if ( n < 0 ) {

    n = n * -1 ;

    while ( n ) {

      a = num2char ( n % 10 ) + a ;
      n /= 10 ;
    }

    a = "-" + a ;
  }
  else if ( n == 0 )
    a = "0" ;
	return a ;
}


/*
*
* Argument: float
* Return: unsigned int
* Description:
      returns the integer floor value to passed floating point number
*
*/

unsigned int intFloor (float f) {
  for ( unsigned int i = 1; i <= 1000000000; i++ ) {
    if (i > f)
      return i-1 ;
  }
  return -1 ;
}
