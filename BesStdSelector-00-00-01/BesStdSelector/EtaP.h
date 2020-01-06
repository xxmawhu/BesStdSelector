/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    EtaP.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-07 Sat 13:43:28 CST
 * <<=====================================>>
 * Last Updated: 2019-11-16 Sat 18:30:53 CST
 *           By: Hao-Kai SUN
 *     Update #: 17
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
#ifndef BesStdSelector_ETAP_HPP
#define BesStdSelector_ETAP_HPP

#include "BesStdSelector/Namespace.hpp"
// #include "BesDChain/CDDecay.h"
// #include "DecayChain/Function/DCSelectionFunction.h"
#include "BesStdSelector/selector/DCSFBase.hpp"

/* Main Decay Channels for Selecting EtaPrime.
 * 1. pi+ pi- eta, mass cut, PDG 957.78  0.196  MeV        42.6%
 *
 * 2. rho0 gamma, not implemented yet, rho0 -> pi+ pi-     28.9%
 *
 * 3. pi0 pi0 eta, not implemented yet.                    22.8%
 */
class BesStdSelector::EtaP : public DCSFDecay {
   public:
    EtaP();

    bool operator()(CDDecay& aEtaP);

   private:
    EtaP(const EtaP&);
    const EtaP& operator=(const EtaP&);

    double m_minMass;
    double m_maxMass;
};

extern BesStdSelector::EtaP omegaXiKSelectorEtaP;

#endif /* BesStdSelector_ETAP_HPP */
/* ===================================================================<<< */
/* ========================= EtaP.hpp ends here ========================= */
