/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorSecondaryProtonSelector.h
#   Created Time  : 2019-10-23 15:46
#   Last Modified : 2019-10-23 15:46
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_secondaryProton_SELECTOR_H
#define BeSelector_secondaryProton_SELECTOR_H

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

class BeSelectorSecondaryProtonSelector : public DCSelectionFunction<CDProton> {
   public:
    BeSelectorSecondaryProtonSelector();

    bool operator()(CDProton& aProton);

   private:
    BeSelectorSecondaryProtonSelector(const BeSelectorSecondaryProtonSelector&);
    const BeSelectorSecondaryProtonSelector& operator=(
        const BeSelectorSecondaryProtonSelector&);
    int m_pidtype;
    bool m_PID;
    double m_VrCut, m_VzCut, m_CosThetaCut;
    double m_minP, m_maxP;
};

extern BeSelectorSecondaryProtonSelector beSelectorSecondaryProtonSelector;

#endif
