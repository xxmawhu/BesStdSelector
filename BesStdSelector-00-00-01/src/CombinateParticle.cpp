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

#include "BesStdSelector/BesStdSelector.h"
#include "BesStdSelector/CombinateParticle.h"

using BesStdSelector::CombinateParticle;
CombinateParticle::CombinateParticle(const string& selector_name,
                                     const double& minMass,
                                     const double& maxMass) {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("MinMass", m_minMass = minMass);
    m_propMgr.declareProperty("MaxMass", m_maxMass = maxMass);

    jobSvc->setMyProperties(selector_name, &m_propMgr);
}

bool CombinateParticle::operator()(CDDecay& aComb) {
    double mass = aComb.mass();
    if (mass < m_minMass || mass > m_maxMass) {
        return false;
    }
    return true;
}

CombinateParticle BesStdSelector::EtaPtoPiPiEtaSelector("EtaPtoPiPiEtaSelector");
CombinateParticle BesStdSelector::EtaPtoPiPiGSelector("EtaPtoPiPiGSelector");
CombinateParticle BesStdSelector::etatoPiPiPi0Selector("EtatoPiPiPi0Selector");
CombinateParticle BesStdSelector::omegaSelector("omegaSelector");
CombinateParticle BesStdSelector::phiSelector("phiSelector");
CombinateParticle BesStdSelector::Sigma0Selector("Sigma0Selector");
CombinateParticle BesStdSelector::Xi0Selector("Xi0Selector");
CombinateParticle BesStdSelector::XimSelector("XimSelector");
CombinateParticle BesStdSelector::SigmapSelector("SigmapSelector");
CombinateParticle BesStdSelector::OmegaSelector("OmegaSelector");
/* ===================================================================<<< */
/* ========================= CombinateParticle.cpp ends here
 * ========================= */
