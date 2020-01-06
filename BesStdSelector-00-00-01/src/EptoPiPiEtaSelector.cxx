/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : BeSelectorEptoPiPiEtaSelector.cxx
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
#include "BeSelector/Selector/BeSelectorEptoPiPiEtaSelector.h"

BeSelectorEptoPiPiEtaSelector::BeSelectorEptoPiPiEtaSelector() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    // Declare the properties
    m_propMgr.declareProperty("minMassEptoPiPiEta", m_minMass = 0.938);
    m_propMgr.declareProperty("maxMassEptoPiPiEta", m_maxMass = 0.978);

    jobSvc->setMyProperties("BeSelectorEptoPiPiEtaSelector", &m_propMgr);
}

bool BeSelectorEptoPiPiEtaSelector::operator()(CDDecay& aEp) {

    aEp.setUserTag(1);
    double mass = aEp.mass();
    if (mass >= m_minMass && mass <= m_maxMass) {
        return true;
    } else {
        return false;
    }
}

BeSelectorEptoPiPiEtaSelector beSelectorEptoPiPiEtaSelector;
