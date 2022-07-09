#ifndef G4ARGS_HH
#define G4ARGS_HH
#include "G4RunManager.hh" /* Run */
#include <cstdlib>
#include <iostream>

class MyG4Args 
{

public:
    MyG4Args(int, char**);
    ~MyG4Args();

    G4String GetOutName() const {return OutName;}
    G4String GetMacName() const {return MacName;}
    G4double GetVov() const {return Detection[0];}
    G4int Getnrep() const {return nrep;}
    G4double GetLYSO_Yield() const {return LYSOProps[0];}
    G4double GetLYSO_ScaleResolution() const {return LYSOProps[1];}
    G4double GetLYSO_RiseT() const {return LYSOProps[2];}
    G4double GetLYSO_DecayT() const {return LYSOProps[3];}
    G4int GetRnd_true() const {return RndGen[0];}
    G4int GetRnd_Part() const {return RndGen[1];}
    G4int GetRnd_Geom() const {return RndGen[2];}
    G4int GetTree_Detected() const {return MainTrees[1];}
    G4int GetTree_Stepping() const {return MainTrees[2];}
    G4int GetTree_Tracking() const {return MainTrees[3];}
    G4int GetTree_EndOfEvent() const {return MainTrees[4];}

private:

    // Default values modifiable by arguments and able to be returned!!!
    G4int Oin=0; 
    G4int nrep=1; 
    G4int MainTrees[5]={1, 1, 1, 1, 1};// Options to write(1)/orNot(0) the different output trees {Arrivals,Detected,Tracking,EndOfEvent}
    G4double LYSOProps[4]={40000.,0.,60.,39.1};//Options to modify default LYSO properties {Yield,ScaleResolution,RiseTime,DecayTime}
    G4int RndGen[3]={1,1,1};             // Options regarding the random generator {Init,Particle,Geometry}
    G4double GeomProps[2]={1,1};//Options to modify default Geom properties {...}
    G4String OutName, MacName;
    G4double Detection[2]={0.35,1};//Options to modify photon detection
    G4String DefOutName="DefaultOutputName_Run";
    G4int KillSim[4]={0,0,0,0}; // Options on how to kill the simulation {Method(0 = all tracks have been killed, 1= nphotons have been detected at each SiPM, 2= x time has passed, 3= kills all photons after x local time, 4= use all parameters to kill the simulation) ,nphotons, global time, local time...}

};

#endif
