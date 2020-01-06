/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    DCSFBase.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-11-11 Mon 19:37:44 CST
 * <<=====================================>>
 * Last Updated: 2019-11-30 Sat 17:02:19 CST
 *           By: Hao-Kai SUN
 *     Update #: 34
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
#ifndef OMEGAXIK_SELECTOR_DCSFBASE_HPP
#define OMEGAXIK_SELECTOR_DCSFBASE_HPP

// included in the following header.
// #include "DecayChain/Function/DCSelectionFunction.h"
#include "BesDChain/BesDCSelector.h"

#include "BesDChain/CDChargedKaon.h"
#include "BesDChain/CDChargedPion.h"
#include "BesDChain/CDDecay.h"
#include "BesDChain/CDElectron.h"
#include "BesDChain/CDEta.h"
#include "BesDChain/CDKs.h"
#include "BesDChain/CDPhoton.h"
#include "BesDChain/CDPi0.h"
#include "BesDChain/CDProton.h"

typedef DCSelectionFunction<CDDecay> DCSFDecay;
typedef DCSelectionFunction<CDElectron> DCSFElectron;
typedef DCSelectionFunction<CDEta> DCSFEta;
typedef DCSelectionFunction<CDChargedKaon> DCSFKaon;
typedef DCSelectionFunction<CDChargedPion> DCSFPion;
typedef DCSelectionFunction<CDKs> DCSFKs;
typedef DCSelectionFunction<CDPi0> DCSFPi0;
typedef DCSelectionFunction<CDProton> DCSFProton;

typedef BesDCSelector<CDPhoton> BDCSPhoton;

#endif /* OMEGAXIK_SELECTOR_DCSFBASE_HPP */
/* ===================================================================<<< */
/* ======================= DCSFBase.hpp ends here ======================= */
