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
### chared tracks 

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


