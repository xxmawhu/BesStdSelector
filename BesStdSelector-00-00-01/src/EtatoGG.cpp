/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    EtatoGG.cpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-20 Sun 18:17:22 CST
 * <<=====================================>>
 * Last Updated: 2019-12-11 Wed 13:49:39 CST
 *           By: Hao-Kai SUN
 *     Update #: 12
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
#include "EvtRecEvent/EvtRecEtaToGG.h"

#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IJobOptionsSvc.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/PropertyMgr.h"

#include "BesStdSelector/EtatoGG.hpp"

OmegaXiKSLT::EtatoGG::EtatoGG() {
    IJobOptionsSvc* jobSvc;
    Gaudi::svcLocator()->service("JobOptionsSvc", jobSvc);

    PropertyMgr m_propMgr;

    m_propMgr.declareProperty("MinMass", m_minMass=0.40);
    m_propMgr.declareProperty("MaxMass", m_maxMass=0.70);
    m_propMgr.declareProperty("MaxChisq", m_maxChisq=200);

    jobSvc->setMyProperties("OmegaXiKSelectorEtatoGG", &m_propMgr);
}

bool OmegaXiKSLT::EtatoGG::operator()(CDEta& aEta) {
    EvtRecEtaToGG* eta = const_cast<EvtRecEtaToGG*>(aEta.navEta());

    double mass = eta->unconMass();
    double chi2 = eta->chisq();
    if ((mass > m_minMass) && (mass < m_maxMass) && (chi2 < m_maxChisq)){
        return false;
    }

    return true;
}

BesStdSelector::EtatoGG omegaXiKSelectorEtatoGG;
/* ===================================================================<<< */
/* ======================== EtatoGG.cpp ends here ======================= */
