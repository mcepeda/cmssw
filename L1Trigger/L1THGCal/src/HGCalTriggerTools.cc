#include "L1Trigger/L1THGCal/interface/HGCalTriggerTools.h"


#include "L1Trigger/L1THGCal/interface/HGCalTriggerGeometryBase.h"

#include "DataFormats/ForwardDetId/interface/HGCalDetId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "SimDataFormats/CaloTest/interface/HGCalTestNumbering.h"
#include "Geometry/HcalCommonData/interface/HcalHitRelabeller.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/EventSetup.h"


namespace {
  template<typename DDD>
  inline void check_ddd(const DDD* ddd) {
    if( nullptr == ddd ) {
      throw cms::Exception("hgcal::HGCalTriggerTools")
        << "DDDConstants not accessible to hgcal::HGCalTriggerTools!";
    }
  }

  template<typename GEOM>
  inline void check_geom(const GEOM* geom) {
    if( nullptr == geom ) {
      throw cms::Exception("hgcal::HGCalTriggerTools")
        << "Geometry not provided yet to hgcal::HGCalTriggerTools!";
    }
  }
}

void 
HGCalTriggerTools::
eventSetup(const edm::EventSetup& es)
{
  edm::ESHandle<HGCalTriggerGeometryBase> triggerGeometry_;
  es.get<CaloGeometryRecord>().get(triggerGeometry_);
  geom_ = triggerGeometry_.product();

  eeLayers_ = geom_->eeTopology().dddConstants().layers(true);
  fhLayers_ = geom_->fhTopology().dddConstants().layers(true);
  if(geom_->isV9Geometry())
  {
    bhLayers_ = geom_->hscTopology().dddConstants().layers(true);
    totalLayers_ =  eeLayers_ + fhLayers_;
  }
  else
  {
    bhLayers_ = geom_->bhTopology().dddConstants()->getMaxDepth(1);
    totalLayers_ =  eeLayers_ + fhLayers_ + bhLayers_;
  }
}

GlobalPoint HGCalTriggerTools::getTCPosition(const DetId& id) const {
  if(id.det() == DetId::Hcal) {
    throw cms::Exception("hgcal::HGCalTriggerTools")
      << "method getTCPosition called for DetId not belonging to a TC";
    // FIXME: this would actually need a better test...but at the moment I can not think to anything better
    // to distinguish a TC detId
  }

  GlobalPoint position = geom_->getTriggerCellPosition(id);
  return position;
}


unsigned
HGCalTriggerTools::
layers(ForwardSubdetector type) const
{
  unsigned layers = 0;
  switch(type)
  {
    case ForwardSubdetector::HGCEE:
      layers = eeLayers_;
      break;
    case ForwardSubdetector::HGCHEF:
      layers = fhLayers_;
      break;
    case ForwardSubdetector::HGCHEB:
      layers = bhLayers_;
      break;
    case ForwardSubdetector::ForwardEmpty:
      layers = totalLayers_;
      break;
    default:
      break;
  };
  return layers;
}

unsigned
HGCalTriggerTools::
layers(DetId::Detector type) const
{
  unsigned layers = 0;
  switch (type)
  {
    case DetId::HGCalEE:
      layers = eeLayers_;
      break;
    case DetId::HGCalHSi:
      layers = fhLayers_;
      break;
    case DetId::HGCalHSc:
      layers = bhLayers_;
      break;
    case DetId::Forward:
      layers = totalLayers_;
      break;
    default:
      break;
  }
  return layers;
}


unsigned
HGCalTriggerTools::
layer(const DetId& id) const {
  unsigned int layer = std::numeric_limits<unsigned int>::max();
  if (id.det() == DetId::Forward) {
    layer = HGCalDetId(id).layer();
  } else if (id.det() == DetId::Hcal && id.subdetId() == HcalEndcap) {
    layer = HcalDetId(id).depth();
  } else if (id.det() == DetId::HGCalEE || id.det() == DetId::HGCalHSi) {
    layer = HGCSiliconDetId(id).layer();
  } else if (id.det() == DetId::HGCalHSc) {
    layer = HGCScintillatorDetId(id).layer();
  }
  return layer;
}

unsigned 
HGCalTriggerTools::
layerWithOffset(const DetId& id) const {
  unsigned int l = layer(id);
  if( id.det() == DetId::Forward && id.subdetId() == HGCHEF ) {
    l += eeLayers_;
  } else if( (id.det() == DetId::Hcal && id.subdetId() == HcalEndcap) ||
             (id.det() == DetId::Forward && id.subdetId() == HGCHEB) ) {
    if(geom_->isV9Geometry()) l += eeLayers_;
    else l += eeLayers_ + fhLayers_;
  }
  return l;
}

int
HGCalTriggerTools::
zside(const DetId& id) const {
  int zside = 0;
  if (id.det() == DetId::Forward) {
    zside = HGCalDetId(id).zside();
  } else if( id.det() == DetId::Hcal && id.subdetId() == HcalEndcap) {
    zside = HcalDetId(id).zside();
  } else if (id.det() == DetId::HGCalEE || id.det() == DetId::HGCalHSi) {
    zside = HGCSiliconDetId(id).zside();
  } else if (id.det() == DetId::HGCalHSc) {
    zside = HGCScintillatorDetId(id).zside();
  }
  return zside;
}

int
HGCalTriggerTools::
thicknessIndex(const DetId& id) const {
  unsigned det = id.det();
  int thickness = 0;
  // For the v8 geometry
  if(det==DetId::Forward)
  {
    switch(id.subdetId())
    { 
      case ForwardSubdetector::HGCEE:
        thickness = geom_->eeTopology().dddConstants().waferTypeL(HGCalDetId(id).wafer())-1;
        break;
      case ForwardSubdetector::HGCHEF:
        thickness = geom_->fhTopology().dddConstants().waferTypeL(HGCalDetId(id).wafer())-1;
        break;
      default:
        break;
    };
  }
  // For the v9 geometry
  else if(det==DetId::HGCalEE || det==DetId::HGCalHSi)
  {
    thickness = HGCSiliconDetId(id).type();
  }
  return thickness;
}

float HGCalTriggerTools::getEta(const GlobalPoint& position, const float& vertex_z) const {
  GlobalPoint corrected_position = GlobalPoint(position.x(), position.y(), position.z()-vertex_z);
  return corrected_position.eta();
}

float HGCalTriggerTools::getTCEta(const DetId& id, const float& vertex_z) const {
  GlobalPoint position = getTCPosition(id);
  return getEta(position, vertex_z);
}

float HGCalTriggerTools::getPhi(const GlobalPoint& position) const {
  float phi = atan2(position.y(),position.x());
  return phi;
}

float HGCalTriggerTools::getTCPhi(const DetId& id) const {
  GlobalPoint position = getTCPosition(id);
  return getPhi(position);
}

float HGCalTriggerTools::getPt(const GlobalPoint& position, const float& hitEnergy, const float& vertex_z) const {
  float eta = getEta(position, vertex_z);
  float pt = hitEnergy / cosh(eta);
  return pt;
}

float HGCalTriggerTools::getTCPt(const DetId& id, const float& hitEnergy, const float& vertex_z) const {
  GlobalPoint position = getTCPosition(id);
  return getPt(position, hitEnergy, vertex_z);
}

float HGCalTriggerTools::getLayerZ(const unsigned& layerWithOffset) const {
  int subdet = ForwardSubdetector::HGCEE;
  unsigned offset = 0;
  if(layerWithOffset > lastLayerEE() && layerWithOffset <= lastLayerFH()) {
    subdet = ForwardSubdetector::HGCHEF;
    offset = lastLayerEE();
  } else if(layerWithOffset > lastLayerFH()) {
    subdet = HcalSubdetector::HcalEndcap;
    offset = lastLayerFH();
  }
  return getLayerZ(subdet, layerWithOffset - offset);
}

float HGCalTriggerTools::getLayerZ(const int& subdet, const unsigned& layer) const {
  float layerGlobalZ = 0.;
  if(subdet == ForwardSubdetector::HGCEE) {
    layerGlobalZ = geom_->eeTopology().dddConstants().waferZ(layer, true);
  } else if(subdet == ForwardSubdetector::HGCHEF) {
    layerGlobalZ = geom_->fhTopology().dddConstants().waferZ(layer, true);
  } else if(subdet == HcalSubdetector::HcalEndcap || subdet == ForwardSubdetector::HGCHEB) {
    if(geom_->isV9Geometry())
    {
      layerGlobalZ = geom_->hscTopology().dddConstants().waferZ(layer, true);
    }
    else
    {
      layerGlobalZ = geom_->bhTopology().dddConstants()->getRZ(
          HcalSubdetector::HcalEndcap,
          geom_->bhTopology().dddConstants()->getEtaRange(1).second,
          layer);
    }
  }
  return layerGlobalZ;
}


DetId
HGCalTriggerTools::
simToReco(const DetId& simid, const HGCalTopology& topo) const 
{
  DetId recoid(0);
  const auto& dddConst = topo.dddConstants();
  // V9
  if (dddConst.geomMode() == HGCalGeometryMode::Hexagon8 ||
      dddConst.geomMode() == HGCalGeometryMode::Hexagon8Full ||
      dddConst.geomMode() == HGCalGeometryMode::Trapezoid)
  {
    recoid = simid;
  }
  // V8
  else
  {
    int subdet(simid.subdetId());
    int layer=0, cell=0, sec=0, subsec=0, zp=0;
    HGCalTestNumbering::unpackHexagonIndex(simid, subdet, zp, layer, sec, subsec, cell);
    //sec is wafer and subsec is celltype
    //skip this hit if after ganging it is not valid
    auto recoLayerCell = dddConst.simToReco(cell,layer,sec,topo.detectorType());
    cell  = recoLayerCell.first;
    layer = recoLayerCell.second;
    if (layer>=0 && cell>=0) 
    {
      recoid = HGCalDetId((ForwardSubdetector)subdet,zp,layer,subsec,sec,cell);
    }
  }
  return recoid;
}


DetId
HGCalTriggerTools::
simToReco(const DetId& simid, const HcalTopology& topo) const 
{
  DetId recoid(0);
  const auto& dddConst = topo.dddConstants();
  HcalDetId id = HcalHitRelabeller::relabel(simid,dddConst);
  if (id.subdet()==int(HcalEndcap)) recoid = id;
  return recoid;
}
