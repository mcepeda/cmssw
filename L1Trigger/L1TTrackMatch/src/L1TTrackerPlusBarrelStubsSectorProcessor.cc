#include "L1Trigger/L1TTrackMatch/interface/L1TTrackerPlusBarrelStubsSectorProcessor.h"
double pi=Geom::pi();

L1TTrackerPlusBarrelStubsSectorProcessor::L1TTrackerPlusBarrelStubsSectorProcessor(const edm::ParameterSet& iConfig, int sector): 
  verbose_(iConfig.getParameter<int>("verbose")),
  station_(iConfig.getParameter<std::vector<int> > ("stationsToProcess")),
  tol_(iConfig.getParameter<int>("tolerance")),
  phi1_(iConfig.getParameter<std::vector<double> > ("phi1")),
  phi2_(iConfig.getParameter<std::vector<double> > ("phi2")),
  propagation_(iConfig.getParameter<std::vector<double> > ("propagationConstants")),
  etaHighm2_(iConfig.getParameter<std::vector<double> > ("etaHighm2")),
  etaHighm1_(iConfig.getParameter<std::vector<double> > ("etaHighm1")),
  etaHigh0_(iConfig.getParameter<std::vector<double> > ("etaHigh0")),
  etaHigh1_(iConfig.getParameter<std::vector<double> > ("etaHigh1")),
  etaHigh2_(iConfig.getParameter<std::vector<double> > ("etaHigh2")),
  etaLowm2_(iConfig.getParameter<std::vector<double> > ("etaLowm2")),
  etaLowm1_(iConfig.getParameter<std::vector<double> > ("etaLowm1")),
  etaLow0_(iConfig.getParameter<std::vector<double> > ("etaLow0")),
  etaLow1_(iConfig.getParameter<std::vector<double> > ("etaLow1")),
  etaLow2_(iConfig.getParameter<std::vector<double> > ("etaLow2")),
  alpha_(iConfig.getParameter<std::vector<double> > ("alpha")),
  beta_(iConfig.getParameter<std::vector<double> > ("beta"))
{
  sector_=sector;
  //find the previous and the next processor
  if (sector==11) {
    previousSector_=10;
    nextSector_=0;
  } 
  else if (sector==0) {
    previousSector_=11;
    nextSector_=1;
  } 
  else {
    previousSector_=sector-1;
    nextSector_=sector+1;
  }
}

L1TTrackerPlusBarrelStubsSectorProcessor::~L1TTrackerPlusBarrelStubsSectorProcessor() {}

std::vector<l1t::L1TkMuonParticle> L1TTrackerPlusBarrelStubsSectorProcessor::process(const TrackPtrVector& tracks,const L1MuKBMTCombinedStubRefVector& stubsAll) {
  //Output collection
  std::vector<l1t::L1TkMuonParticle> out;
  //First thing first. Keep only the stubs on this processor
  L1MuKBMTCombinedStubRefVector stubs;

  for (const auto& stub: stubsAll) 
    if (stub->scNum()==sector_ || stub->scNum()==previousSector_ || stub->scNum()==nextSector_)
      stubs.push_back(stub);
  
  //Next loop on tracks
  for (const auto& track : tracks) {
    //Create a muon particle from the track:
    l1t::L1TkMuonParticle::LorentzVector vec(track->getMomentum().x(),
					track->getMomentum().y(),
					track->getMomentum().z(),
					track->getMomentum().mag());
    l1t::L1TkMuonParticle muon (vec,track);
    
    //Set muon charge
    int charge=1;
    if (track->getRInv()<0)
      charge=-1;
    muon.setCharge(charge);
    int k=8192*muon.charge()/muon.pt();
    
    //You need some logic to see if track is in this sector here:
    //Easiest to check if muon is outside of the sector and tell the sector processor to move on
    if (sector_!=0 && (muon.phi()<=phi1_[sector_] || muon.phi()>=phi2_[sector_])) {
      continue;
    }
    if (sector_==0 && (muon.phi()<=phi1_[sector_] && muon.phi()>=phi2_[sector_])) {
      continue;
    }

    L1MuKBMTCombinedStubRefVector stubsPass; 
    for (const auto& stub : stubs) {
      //Do the matching (propagate the muon)
      int phi=stubPhi(stub);
      int st=stub->stNum();
      int wh=stub->whNum();
      double deltaPhiTPull=-1;

      //Check if eta value of track matches the station and wheel that the stub is in
      if (wh==-2 && muon.eta()>=etaLowm2_[st-1] && muon.eta()<=etaHighm2_[st-1]) {
        deltaPhiTPull=pull(k,phiProp(muon.phi(),k,sector_,st)-phi,st);
      }
      else if (wh==-1 && muon.eta()>=etaLowm1_[st-1] && muon.eta()<=etaHighm1_[st-1]) {
        deltaPhiTPull=pull(k,phiProp(muon.phi(),k,sector_,st)-phi,st);
      }
      else if (wh==0 && muon.eta()>=etaLow0_[st-1] && muon.eta()<=etaHigh0_[st-1]) {
        deltaPhiTPull=pull(k,phiProp(muon.phi(),k,sector_,st)-phi,st);
      }
      else if (wh==1 && muon.eta()>=etaLow1_[st-1] && muon.eta()<=etaHigh1_[st-1]) {
        deltaPhiTPull=pull(k,phiProp(muon.phi(),k,sector_,st)-phi,st);
      }
      else if (wh==2 && muon.eta()>=etaLow2_[st-1] && muon.eta()<=etaHigh2_[st-1]) {
        deltaPhiTPull=pull(k,phiProp(muon.phi(),k,sector_,st)-phi,st);
      }

      if (deltaPhiTPull>=0 && deltaPhiTPull<tol_) {
        stubsPass.push_back(stub);
      }
    }

    //pt phi and eta can be accesed by vec.phi(),vec.eta(),vec.pt()
    //propagate and match here 
    L1MuKBMTCombinedStubRefVector stubsFilter=select(stubsPass,muon,k);

    //You only need to add stubs to the muons  at this stage
    //To do that just do:
    if (stubsFilter.size()>0) {
      for (const auto& stub : stubsFilter) {
        muon.addBarrelStub(stub);
      }

      //If the muon has no stubs, do not write it out-so do this here 
      out.push_back(muon);
    }

  }

  return out;
}

//Define delta phi function
int L1TTrackerPlusBarrelStubsSectorProcessor::deltaPhi(double p1,double p2) {
  double res=p1-p2;
  while (res>pi) {
    res-=2*pi;
  }
  while (res<-pi) {
    res+=2*pi;
  }
  
  return res;
}

//Define phi propagation
int L1TTrackerPlusBarrelStubsSectorProcessor::phiProp(double muPhi,int k,int sc,int st) {
  //Shift phi of the track to be with respect to the sector
  double phi=muPhi-(-pi+sc*pi/6.0);
  if (phi>pi) {
    phi-=2*pi;
  }
  else if (phi<-pi) {
    phi+=2*pi;
  }

  //Convert phi to integer value and propagate
  int phiInt=phi*2048*6/pi;
  int propPhi=phiInt+propagation_[st-1]*k;
  
  return propPhi;
}

//Define pull function
double L1TTrackerPlusBarrelStubsSectorProcessor::pull(int k,int dphi,int st) {
  double pullfunc=abs(dphi/sqrt(alpha_[st-1]*pow(k,2)+beta_[st-1]));
  
  return pullfunc;
}

//Get integer value for phi of the stub
int L1TTrackerPlusBarrelStubsSectorProcessor::stubPhi(const L1MuKBMTCombinedStubRef& stub) {
  int phi=stub->phi();
  if (stub->scNum()==previousSector_) {
    phi-=2047;
  }
  if (stub->scNum()==nextSector_) {
    phi+=2047;
  }

  return phi;
}

//Select best stubs
L1MuKBMTCombinedStubRefVector L1TTrackerPlusBarrelStubsSectorProcessor::select(const L1MuKBMTCombinedStubRefVector& stubsPass, const l1t::L1TkMuonParticle& muon,int k) {
  //Create vectors for sorting stubs
  L1MuKBMTCombinedStubRefVector stubsSelectSt1;
  L1MuKBMTCombinedStubRefVector stubsSelectSt2;
  L1MuKBMTCombinedStubRefVector stubsSelectSt3;
  L1MuKBMTCombinedStubRefVector stubsSelectSt4;
  L1MuKBMTCombinedStubRefVector stubsSelect;

  //Sort stubs by station number
  if (stubsPass.size()>0) {
    for (const auto& stub: stubsPass) {
      if (stub->stNum()==1) {
        stubsSelectSt1.push_back(stub);
      }
      if (stub->stNum()==2) {
        stubsSelectSt2.push_back(stub);
      }
      if (stub->stNum()==3) {
        stubsSelectSt3.push_back(stub);
      }
      if (stub->stNum()==4) {
        stubsSelectSt4.push_back(stub);
      }
    }
  }

  //Select stub with the lowest pull value at each station
  if (stubsSelectSt1.size()>0) {
    double pullSt1=pull(k,phiProp(muon.phi(),k,sector_,1)-stubsSelectSt1[0]->phi(),1);
    int bestStub=-1;
    for (uint i=0;i<stubsSelectSt1.size();i++) {
      double pullStub=pull(k,phiProp(muon.phi(),k,sector_,1)-stubsSelectSt1[i]->phi(),1);
      if (pullStub<pullSt1) {
        bestStub=i;
	pullSt1=pullStub;
      }
    }
    if (bestStub>0)
      stubsSelect.push_back(stubsSelectSt1[uint(bestStub)]);
    else
      stubsSelect.push_back(stubsSelectSt1[0]);
  }
  if (stubsSelectSt2.size()>0) {
    double pullSt2=pull(k,phiProp(muon.phi(),k,sector_,2)-stubsSelectSt2[0]->phi(),2);
    int bestStub=-1;
    for (uint i=0;i<stubsSelectSt2.size();i++) {
      double pullStub=pull(k,phiProp(muon.phi(),k,sector_,2)-stubsSelectSt2[i]->phi(),2);
      if (pullStub<pullSt2) {
        bestStub=i;
	pullSt2=pullStub;
      }
    }
    if (bestStub>0)
      stubsSelect.push_back(stubsSelectSt2[uint(bestStub)]);
    else
      stubsSelect.push_back(stubsSelectSt2[0]);
  }
  if (stubsSelectSt3.size()>0) {
    double pullSt3=pull(k,phiProp(muon.phi(),k,sector_,3)-stubsSelectSt3[0]->phi(),3);
    int bestStub=-1;
    for (uint i=0;i<stubsSelectSt3.size();i++) {
      double pullStub=pull(k,phiProp(muon.phi(),k,sector_,3)-stubsSelectSt3[i]->phi(),3);
      if (pullStub<pullSt3) {
        bestStub=i;
	pullSt3=pullStub;
      }
    }
    if (bestStub>0)
      stubsSelect.push_back(stubsSelectSt3[uint(bestStub)]);
    else
      stubsSelect.push_back(stubsSelectSt3[0]);
  }
  if (stubsSelectSt4.size()>0) {
    double pullSt4=pull(k,phiProp(muon.phi(),k,sector_,4)-stubsSelectSt4[0]->phi(),4);
    int bestStub=-1;
    for (uint i=0;i<stubsSelectSt4.size();i++) {
      double pullStub=pull(k,phiProp(muon.phi(),k,sector_,4)-stubsSelectSt4[i]->phi(),4);
      if (pullStub<pullSt4) {
	bestStub=i;
	pullSt4=pullStub;
      }
    }
    if (bestStub>0)
      stubsSelect.push_back(stubsSelectSt4[uint(bestStub)]);
    else
      stubsSelect.push_back(stubsSelectSt4[0]);
  }
  
  return stubsSelect;
}

