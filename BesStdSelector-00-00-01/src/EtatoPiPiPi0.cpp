/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    EtatoPiPiPi0.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-20 Sun 18:20:59 CST
 * <<=====================================>>
 * Last Updated: 2019-12-11 Wed 13:49:52 CST
 *           By: Hao-Kai SUN
 *     Update #: 11
 * <<======== COPYRIGHT && LICENSE =======>>
 *
 * Copyright © 2019 SUN Hao-Kai <spin.hk@outlook.com>. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <https://www.gnu.org/licenses/>.
 *
 * ============================== CODES ==============================>>> */
// #include "EventModel/EventHeader.h"
// #include "EventModel/EventModel.h"
// #include "EvtRecEvent/EvtRecEvent.h"
// #include "EvtRecEvent/EvtRecTrack.h"
// #include "ParticleID/ParticleID.h"

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "OmegaXiKAlg/selector/EtatoPiPiPi0.hpp"

OmegaXiKSLT::EtatoPiPiPi0::EtatoPiPiPi0() : m_minMass(0.40), m_maxMass(0.70)
{
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("MinMass", m_minMass);
    m_propMgr.declareProperty("MaxMass", m_maxMass);

    jobSvc->setMyProperties("OmegaXiKSelectorEtatoPiPiPi0", &m_propMgr);
}

bool OmegaXiKSLT::EtatoPiPiPi0::operator()(CDDecay& aEta)
{
    aEta.setUserTag(1);
    double mass = aEta.mass();
    return (mass >= m_minMass) && (mass <= m_maxMass);
}

OmegaXiKSLT::EtatoPiPiPi0 omegaXiKSelectorEtatoPiPiPi0;
/* ===================================================================<<< */
/* ===================== EtatoPiPiPi0.cpp ends here ===================== */
