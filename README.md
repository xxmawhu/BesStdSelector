#BesStdSelector
## Why call it BesStdSelector

Ihe package collects most selectors used in the BESIII physic analysis frame.
What's more, the exactly conditions are obtained from the publications. So I
call it as StdSelector.

## What do the selectors select

Select the chared tracks, select the showers, select the long lifetime
particles. Now, the following selectors are available
```c++
GoodChrTrkSelector;
soloPhotonSelector;
primaryProtonSelector;
secondaryProtonSelector;
primaryKaonSelector;
secondaryKaonSelector;
primaryPionSelector;
secondaryPionSelector;
primaryElectronSelector;
secondaryElectronSelector;
lambdaSelector;
ksSelector;
pi0Selector;
etatoGGSelector;
omegaSelector;
phiSelector;
Xi0Selector;
XipSelector;
Sigma0Selector;
SigmapSelector;
OmegaSelector;
etatoPiPiPi0Selector;
EtaPtoPiPiEtaSelector;
EtaPtoPiPiGSelector;
typicalTagSelector;
```
### Charged tracks 

Only five chared tracks, "proton", "pion", "kaon", "electron", "muon"
In this package, the chared tracks are divided into two categories mainly.
* primary
> This track come from IP, which is the primary vertex. 
* secondary
> This track does not come from IP, may be secondary vertex, or third vertex,
> such as the "Ks" vertex, "Xi-" vertex... 
The mainly difference between the two categories is the requirement on the
"Vxy" and "Vz"

#### Which particles are reconstructed from secondary track?

All particles with decay length larger than 1cm, such "Ks", "Lambda", "Omega-"
"Xi-", "Xi0"...
The others are reconstructed from primary tracks.


## Why only cut the mass of Xi-?  
Not only for Xi0, but also for all hyperons except Lambda. Because you should
only constraint a wide mass window for them, leaving enough sideband for further
study. Wether cut on the decay length or others? You should study the MC
sample carefully, the decision the next step. Another important reason is that
speeding the event selection procedures in order to save CPU. 

## How to use the selectors?

### Install and Make

* *Copy it into your `workarea`
```bash
git clone https://github.com/xxmawhu/BesStdSelector.git 
```
> Recommend you put it in one directory named "Utilities"

* Make
```bash
cd BesStdSelector/BesStdSelector-00-00-01/cmt
cmt config
cmt make
```

* Register
> Add "use BesStdSelector BesStdSelector-* Utilities" to the requirement in
"TestRelease/TestRelease-*/cmt"

### Use it in your project

Most experimenters use the for-in-for style to reconstruct signal list.
With the help of BesDChain, the reconsruction becomes very easy and intuitive.
* Please include the header file. 
```c++
#include "BesStdSelector/Selector.h"
using namespace BesStdSelector;
```
* Some instances
```c++
SmartDataPtr<EvtRecTrackCol> evtRecTrackCol(eventSvc(), "/Event/EvtRec/EvtRecTrackCol");
EvtRecTrackIterator track_begin = evtRecTrackCol->begin();
EvtRecTrackIterator track_end =  evtRecTrackCol->begin() + totalCharged;

// select the proton
CDProtonList m_ProtonList;
m_ProtonList = CDProtonList(track_begin, track_end, secondaryProtonSelector);

// select the pion
CDChargedPionList m_PionAllList;
m_PionAllList = CDChargedPionList(track_begin, track_end, secondaryPionSelector);

// select the pi0 candidates
CDPi0List Pi0List(BesStdSelector::pi0Selector);
SmartDataPtr<EvtRecPi0Col> recPi0Col(eventSvc(), "/Event/EvtRec/EvtRecPi0Col");
dc_fill(Pi0List, recPi0Col->begin(), recPi0Col->end());

// combination them into Lambda
CDDecayList Lambda(lambdaSelector);
Lambda = m_ProtonAllList.plus() * m_PionAllList.minus();

// combination the pi0 and Lambda
CDDecayList Xi0(Xi0Selector);
Xi0 = Lambda * Pi0List;
```
Best!

