#pragma once///Include guard

///see http://www.t13.org/ ATA attachment
///see http://www.scs.stanford.edu/11wi-cs140/pintos/specs/ata-3-std.pdf
#define numSMART_FWbytes 8///words 23-26 = 4 words each 2 bytes, p.53
#define numSMARTmodelBytes 40///27-46 = 20 words each 2 bytes
#define numSMART_SNbytes 20///words 10-19 = 20 bytes

///https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
/// v. 23:34, 1. Jun. 2020 : "raw value [...] has 48 bits"
#define numSMARTrawValB 6
///https://en.wikipedia.org/wiki/S.M.A.R.T. :1 till 254 = 254 different
#define numDifferentSMART_IDs 254
