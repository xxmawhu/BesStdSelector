/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Pi0.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-07 Sat 17:16:28 CST
 * <<=====================================>>
 * Last Updated: 2019-11-30 Sat 15:39:46 CST
 *           By: Hao-Kai SUN
 *     Update #: 9
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
#ifndef OMEGAXIK_SELECTOR_PI0_HPP
#define OMEGAXIK_SELECTOR_PI0_HPP

#include "OmegaXiKAlg/Namespace.hpp"
// #include "BesDChain/CDPi0.h"
// #include "DecayChain/Function/DCSelectionFunction.h"
#include "OmegaXiKAlg/selector/DCSFBase.hpp"

class OmegaXiKSLT::Pi0 : public DCSFPi0
{
  public:
    Pi0();

    bool operator()(CDPi0& aPi0);

  private:
    Pi0(const Pi0&);
    const Pi0& operator=(const Pi0&);

    double m_minMass;
    double m_maxMass;
    double m_maxChisq;

    double m_minRho;
};

extern OmegaXiKSLT::Pi0 omegaXiKSelectorPi0;

#endif /* OMEGAXIK_SELECTOR_PI0_HPP */
/* ===================================================================<<< */
/* ========================= Pi0.hpp ends here ========================== */
