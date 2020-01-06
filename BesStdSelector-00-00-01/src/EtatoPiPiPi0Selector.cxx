/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorEtatoPiPiPi0Selector.cxx
#   Created Time  : 2019-10-23 15:35
#   Last Modified : 2019-10-23 15:35
#   Describe      :
#
# ====================================================*/

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "EventModel/EventModel.h"
#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "ParticleID/ParticleID.h"
#include "BeSelector/Selector/BeSelectorEtatoPiPiPi0Selector.h"

BeSelectorEtatoPiPiPi0Selector::BeSelectorEtatoPiPiPi0Selector() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    // Declare the properties
    m_propMgr.declareProperty("minMassEtatoPiPiPi0", m_minMass = 0.40);
    m_propMgr.declareProperty("maxMassEtatoPiPiPi0", m_maxMass = 0.70);

    jobSvc->setMyProperties("BeSelectorEtatoPiPiPi0Selector", &m_propMgr);
}

bool BeSelectorEtatoPiPiPi0Selector::operator()(CDDecay& aEta) {

    aEta.setUserTag(1);
    double mass = aEta.mass();
    if (mass >= m_minMass && mass <= m_maxMass) {
        return true;
    } else {
        return false;
    }
}
BeSelectorEtatoPiPiPi0Selector beSelectorEtatoPiPiPi0Selector;
