/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : ProtonSelector.h
#   Created Time  : 2019-10-23 15:46
#   Last Modified : 2019-10-23 15:46
#   Describe      :
#
# ====================================================*/

#ifndef BesStdelector_Proton_SELECTOR_H
#define BesStdelector_Proton_SELECTOR_H

#include "BesDChain/CDProton.h"
#include "DecayChain/Function/DCSelectionFunction.h"

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"
#include "BesDChain/CDProton.h"

#include "EventModel/EventModel.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"

#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"
#include <string>
namespace BesStdSelector{
class ProtonSelector : public DCSelectionFunction<CDProton> {
   public:
    ProtonSelector();
    // the default name is "ProtonSelector"
    ProtonSelector(const string& name);

    bool operator()(CDProton& aProton);

   private:
    ProtonSelector(const ProtonSelector&);
    const ProtonSelector& operator=( const ProtonSelector&);

    int m_pidtype;

    double m_VrCut;
    double m_VzCut;
    double m_CosThetaCut;

    double m_minP;
    double m_maxP;

    bool m_PID;
};
}

extern BesStdSelector::ProtonSelector primaryProtonSelector;
extern BesStdSelector::ProtonSelector secondaryProtonSelector;

#endif
