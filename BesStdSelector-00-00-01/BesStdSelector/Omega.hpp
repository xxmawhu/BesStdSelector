/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Omega.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-07 Sat 14:24:34 CST
 * <<=====================================>>
 * Last Updated: 2019-11-23 Sat 16:17:06 CST
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
#ifndef OMEGAXIK_SELECTOR_OMEGA_HPP
#define OMEGAXIK_SELECTOR_OMEGA_HPP

#include "OmegaXiKAlg/Namespace.hpp"
// #include "BesDChain/CDDecay.h"
// #include "DecayChain/Function/DCSelectionFunction.h"
#include "OmegaXiKAlg/selector/DCSFBase.hpp"

class OmegaXiKSLT::Omega : public DCSFDecay {
   public:
    Omega();

    bool operator()(CDDecay& aOmega);

   private:
    Omega(const Omega&);
    const Omega& operator=(const Omega&);

    double m_minMass;
    double m_maxMass;
    double m_maxChisq;

    bool m_use2ndVFit;
    double m_maxVFitChisq;

    bool m_useFlightSig;
    double m_minFlightSig;
};

extern OmegaXiKSLT::Omega omegaXiKSelectorOmega;

#endif /* OMEGAXIK_SELECTOR_OMEGA_HPP */
/* ===================================================================<<< */
/* ======================== Omega.hpp ends here ========================= */
