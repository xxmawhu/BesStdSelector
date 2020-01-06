/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorPrimaryProtonSelector.h
#   Created Time  : 2019-10-23 15:46
#   Last Modified : 2019-10-23 15:46
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_PrimaryProton_SELECTOR_H
#define BeSelector_PrimaryProton_SELECTOR_H

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

class BeSelectorPrimaryProtonSelector : public DCSelectionFunction<CDProton> {
   public:
    BeSelectorPrimaryProtonSelector();

    bool operator()(CDProton& aProton);

   private:
    BeSelectorPrimaryProtonSelector(const BeSelectorPrimaryProtonSelector&);
    const BeSelectorPrimaryProtonSelector& operator=(
        const BeSelectorPrimaryProtonSelector&);

    int m_pidtype;

    double m_VrCut;
    double m_VzCut;
    double m_CosThetaCut;

    double m_minP;
    double m_maxP;

    bool m_PID;
};

extern BeSelectorPrimaryProtonSelector beSelectorPrimaryProtonSelector;

#endif
