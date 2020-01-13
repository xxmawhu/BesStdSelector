/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    CombinateParticle.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-20 Sun 13:44:44 CST
 * <<=====================================>>
 * Last Updated: 2019-12-11 Wed 13:49:26 CST
 *           By: Hao-Kai SUN
 *     Update #: 18
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

#include "BesStdSelector/CombinateParticle.h"

BesStdSelector::CombinateParticle::CombinateParticle(
    const string& selector_name, const double& minMass, const double& maxMass) {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("MinMass", m_minMass = minMass);
    m_propMgr.declareProperty("MaxMass", m_maxMass = maxMass);

    jobSvc->setMyProperties(selector_name, &m_propMgr);
}

bool BesStdSelector::CombinateParticle::operator()(CDDecay& aComb) {
    double mass = aComb.mass();
    if (mass < m_minMass || mass > m_maxMass) {
        return false;
    }
    return true;
}

BesStdSelector::CombinateParticle EtaPtoPiPiEtaSelector(
    "EtaPtoPiPiEtaSelector");
BesStdSelector::CombinateParticle EtaPtoPiPiGSelector("EtaPtoPiPiGSelector");
BesStdSelector::CombinateParticle etatoPiPiPi0Selector("EtatoPiPiPi0Selector");
BesStdSelector::CombinateParticle omegaSelector("omegaSelector");
BesStdSelector::CombinateParticle phiSelector("phiSelector");
BesStdSelector::CombinateParticle Sigma0Selector("Sigma0Selector");
BesStdSelector::CombinateParticle Xi0Selector("Xi0Selector");
BesStdSelector::CombinateParticle XipSelector("XipSelector");
BesStdSelector::CombinateParticle SigmapSelector("SigmapSelector");
BesStdSelector::CombinateParticle OmegaSelector("OmegaSelector");
/* ===================================================================<<< */
/* ========================= CombinateParticle.cpp ends here
 * ========================= */
