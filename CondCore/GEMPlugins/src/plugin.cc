/*
 *  plugin.cc
 *  CMSSW
 *
 *  Created by Marcello Maggi --INFN
 *    based on template by Chris Jones on 7/24/05.
 *
 */

#include "CondCore/PluginSystem/interface/registration_macros.h"
#include "CondFormats/GEMObjects/interface/GEMEMap.h"
#include "CondFormats/DataRecord/interface/GEMEMapRcd.h"


REGISTER_PLUGIN(GEMEMapRcd,GEMEMap);

