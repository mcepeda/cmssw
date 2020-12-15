#ifndef __l1t_emtftrackfwd_h__
#define __l1t_emtftrackfwd_h__

#include "DataFormats/L1Trigger/interface/BXVector.h"
#include "DataFormats/L1Trigger/interface/L1TObjComparison.h"

namespace l1t {
  class EMTFTrack;
  typedef std::vector<EMTFTrack> EMTFTrackCollection;

  typedef edm::Ref<EMTFTrackCollection> EMTFTrackRef;
  typedef edm::RefVector<EMTFTrackCollection> EMTFTrackRefVector;
  typedef std::vector<EMTFTrackRef> EMTFTrackVectorRef;

}  // namespace l1t

#endif /* define __l1t_emtftrackfwd_h__ */
