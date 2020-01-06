/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Signal.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-12-06 Fri 14:35:52 CST
 * <<=====================================>>
 * Last Updated: 2019-12-11 Wed 13:35:57 CST
 *           By: Hao-Kai SUN
 *     Update #: 36
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
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"

#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/PropertyMgr.h"

#include "OmegaXiKAlg/selector/Omega.hpp"
#include "OmegaXiKAlg/selector/Signal.hpp"

using CLHEP::HepLorentzVector;

OmegaXiKSLT::Signal::Signal()
    : m_Ecm(-999.0), m_minRecMass(1.264), m_maxRecMass(1.364)
{
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("EcmUsedInSignal", m_Ecm);
    // Xi0: 1314.86    Xi-: 1321.71
    m_propMgr.declareProperty("MinRecMass", m_minRecMass);
    m_propMgr.declareProperty("MaxRecMass", m_maxRecMass);

    jobSvc->setMyProperties("OmegaXiKSelectorSignal", &m_propMgr);
}

bool OmegaXiKSLT::Signal::operator()(CDDecay& aSignal)
{
    if (m_Ecm < 0.) {
        std::cout << "Invalid E_cm in Selector Signal -> " << m_Ecm
                  << std::endl;
        return false;
    }

    HepLorentzVector p4Beam(0., 0., 0., m_Ecm);
    HepLorentzVector p4OmegaKs = aSignal.p4();
    p4OmegaKs.boost(-0.011, 0., 0.);
    // std::cout << "Ecm in Selector Signal -> " << m_Ecm << std::endl;
    // std::cout << "(" << p4OmegaKs[0] << ", " << p4OmegaKs[1] << ", "
    //           << p4OmegaKs[2] << ", " << p4OmegaKs[3] << ")" << std::endl;
    double mass = (p4Beam - p4OmegaKs).m();
    // std::cout << "Recolling mass in Selector Signal -> " << mass <<
    // std::endl;
    return mass > m_minRecMass && mass < m_maxRecMass;
}

OmegaXiKSLT::Signal omegaXiKSelectorSignal;
/* ===================================================================<<< */
/* ======================== Signal.cpp ends here ======================== */
