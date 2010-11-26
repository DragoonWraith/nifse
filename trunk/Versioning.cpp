#include "Versioning.h"

UInt8  getAlphaV(const UInt32 ver) { return (ver & 0x0000000F) >> alpha; }
void setAlphaV(UInt8 a, UInt32 ver) { ver = (ver & 0xFFFFFFF0) | ((a & 0xF) << alpha); }
bool isAlpha(const UInt32 ver) { return (getAlphaV(ver) != 0xF); }

UInt8   getBetaV(const UInt32 ver) { return (ver & 0x000000F0) >> beta; }
void setBetaV(UInt8 b, UInt32 ver) { ver = (ver & 0xFFFFFF0F) | ((b & 0xF) << beta); }
bool isBeta(const UInt32 ver) { return (getBetaV(ver) != 0xF) && !isAlpha(); }

UInt8  getMinorV(const UInt32 ver) { return (ver & 0x0000FF00) >> minor; }
void setMinorV(UInt8 m, UInt32 ver) { ver = (ver & 0xFFFF00FF) | (m << minor); }

UInt16 getMajorV(const UInt32 ver) { return (ver & 0xFFFF0000) >> major; }
void setMajorV(UInt16 M, UInt32 ver) { ver = (ver & 0x0000FFFF) | (M << major); }
