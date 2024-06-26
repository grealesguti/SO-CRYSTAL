#include "tracking.hh"

MyTrackingAction::MyTrackingAction(MyEventAction *eventAction,MyG4Args *MainArgs)
{
    PassArgs=MainArgs;

    fEventAction = eventAction;
}

MyTrackingAction::~MyTrackingAction()
{}

void MyTrackingAction::PreUserTrackingAction(const G4Track*)
{

}

void MyTrackingAction::PostUserTrackingAction(const G4Track*)
{
    // The user tracking action class holds the pointer to the tracking manager:
    // fpTrackingManager
    G4ThreeVector TranslVol;
    // From the tracking manager we can retrieve the secondary track vector,
    // which is a container class for tracks:
    G4TrackVector* secTracks = fpTrackingManager -> GimmeSecondaries();
    // You can use the secTracks vector to retrieve the number of secondary 
    // electrons
      if (secTracks) { 
         size_t nmbSecTracks = (*secTracks).size();       

         for (size_t i = 0; i < nmbSecTracks; i++) { 
            if ((*secTracks)[i]->GetDefinition() == G4OpticalPhoton::Definition()) {
				
                // Get the momentum of the photon
                G4double photonMomentumMag = (*secTracks)[i]->GetMomentum().mag();
                // Calculate the wavelength in nanometers
                G4double wavelength = (1.239841939 * eV / photonMomentumMag) * 1E+03; // nanometers
                
                if (PassArgs->GetGeomConfig()==3){
                    TranslVol     =  (*secTracks)[i]->GetVertexPosition();
                    if(TranslVol[0]/mm<-0.09&&  TranslVol[0]/mm>-3.1){
                        PassArgs->AddTP();
                    }
                }else{
                    PassArgs->AddTP();
                    PassArgs->AddTPwlen(1/wavelength);
                }

            }
        }
    }
}
