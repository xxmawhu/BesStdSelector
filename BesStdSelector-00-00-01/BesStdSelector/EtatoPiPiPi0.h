/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    EtatoPiPiPi0.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-07 Sat 18:19:50 CST
 * <<=====================================>>
 * Last Updated: 2019-11-18 Mon 20:06:34 CST
 *           By: Hao-Kai SUN
 *     Update #: 6
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
#ifndef BesStdSelector_ETATOPIPIPI0_HPP
#define BesStdSelector_ETATOPIPIPI0_HPP

#include "BesStdSelector/Namespace.hpp"
// #include "BesDChain/CDDecay.h"
// #include "DecayChain/Function/DCSelectionFunction.h"
#include "BesStdSelector/selector/DCSFBase.hpp"

class BesStdSelector::EtatoPiPiPi0 : public DCSFDecay {
   public:
    EtatoPiPiPi0();

    bool operator()(CDDecay& aEta3p);

   private:
    EtatoPiPiPi0(const EtatoPiPiPi0&);
    const EtatoPiPiPi0& operator=(const EtatoPiPiPi0&);

    double m_minMass;
    double m_maxMass;
};

extern BesStdSelector::EtatoPiPiPi0 omegaXiKSelectorEtatoPiPiPi0;

#endif /* BesStdSelector_ETATOPIPIPI0_HPP */
/* ===================================================================<<< */
/* =========== EtatoPiPiPi0.hpp ends here ============ */
