/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    Sigma0.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-10-21 Mon 19:06:16 CST
 * <<=====================================>>
 * Last Updated: 2019-12-01 Sun 18:54:10 CST
 *           By: Hao-Kai SUN
 *     Update #: 15
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
#ifndef OMEGAXIK_SELECTOR_SIGMA0_HPP
#define OMEGAXIK_SELECTOR_SIGMA0_HPP

#include "OmegaXiKAlg/Namespace.hpp"
// #include "BesDChain/CDDecay.h"
// #include "DecayChain/Function/DCSelectionFunction.h"
#include "OmegaXiKAlg/selector/DCSFBase.hpp"

class OmegaXiKSLT::Sigma0 : public DCSFDecay
{
  public:
    Sigma0();

    bool operator()(CDDecay& aSigma);

  private:
    Sigma0(const Sigma0&);
    const Sigma0& operator=(const Sigma0&);

    double m_minMass;
    double m_maxMass;

    double m_minMassTight;
    double m_maxMassTight;
};

extern OmegaXiKSLT::Sigma0 omegaXiKSelectorSigma0;

#endif /* OMEGAXIK_SELECTOR_SIGMA0_HPP */
/* ===================================================================<<< */
/* ======================== Sigma0.hpp ends here ======================== */
