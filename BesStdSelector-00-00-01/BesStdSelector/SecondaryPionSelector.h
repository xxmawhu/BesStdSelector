/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorSecondaryPionSelector.h
#   Created Time  : 2019-10-23 15:47
#   Last Modified : 2019-10-23 15:47
#   Describe      :
#
# ====================================================*/

#ifndef BeSelector_SecondaryPion_SELECTOR_H
#define BeSelector_SecondaryPion_SELECTOR_H

#include "BesDChain/CDChargedPion.h"
#include "DecayChain/Function/DCSelectionFunction.h"

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EventModel/EventModel.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"

#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"

class BeSelectorSecondaryPionSelector
    : public DCSelectionFunction<CDChargedPion> {
   public:
    BeSelectorSecondaryPionSelector();

    bool operator()(CDChargedPion& aSecondaryPion);
    void setpidtype(bool type = true);

   private:
    BeSelectorSecondaryPionSelector(const BeSelectorSecondaryPionSelector&);
    const BeSelectorSecondaryPionSelector& operator=(
        const BeSelectorSecondaryPionSelector&);

    int m_pidtype;

    double m_minP;
    double m_VrCut;
    double m_VzCut;
    double m_CosThetaCut;

    bool m_useSimplePID, m_DoPID;
    bool m_useDedx;
    bool m_useTof1;
    bool m_useTof2;
    bool m_useTofE;
    bool m_useTofQ;
    bool m_useEmc;
    bool m_useMuc;

    bool m_probability;
    double m_PidProbCut;
    bool m_rejectKaon;
    bool m_rejectProton;

    bool m_likelihood;
    bool m_neuronNetwork;
    std::vector<double> m_neuronValCut;
};

extern BeSelectorSecondaryPionSelector beSelectorSecondaryPionSelector;

#endif
