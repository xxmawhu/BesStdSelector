/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Ks.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-07 Sat 12:51:35 CST
 * <<=====================================>>
 * Last Updated: 2019-11-21 Thu 21:11:31 CST
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
#ifndef OMEGAXIK_SELECTOR_KS_HPP
#define OMEGAXIK_SELECTOR_KS_HPP

#include "OmegaXiKAlg/Namespace.hpp"
// #include "BesDChain/CDKs.h"
// #include "DecayChain/Function/DCSelectionFunction.h"
#include "OmegaXiKAlg/selector/DCSFBase.hpp"

class OmegaXiKSLT::Ks : public DCSFKs {
   public:
    Ks();

    bool operator()(CDKs& aKs);

   private:
    Ks(const Ks&);
    const Ks& operator=(const Ks&);

    double m_minMass;
    double m_maxMass;
    double m_maxChisq;

    bool m_use2ndVFit;
    double m_maxVFitChisq;
    double m_minFlightSig;
};

extern OmegaXiKSLT::Ks omegaXiKSelectorKs;

#endif /* OMEGAXIK_SELECTOR_KS_HPP */
/* ===================================================================<<< */
/* ========================== Ks.hpp ends here ========================== */
