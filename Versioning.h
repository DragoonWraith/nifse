static const UInt8 alpha = 0;
static const UInt8 beta = 4;
static const UInt8 minor = 8;
static const UInt8 major = 16;

#define VERSION(majorV, minorV, betaV, alphaV) ((0x ## majorV)<<major | (0x ## minorV)<<minor | (0x ## betaV)<<beta | (0x ## alphaV)<<alpha)
#define CURRENT_VERSION VERSION(1, 0, 5, F)

UInt8  getAlphaV(const UInt32 ver = CURRENT_VERSION);
void setAlphaV(UInt8 a, UInt32 ver = CURRENT_VERSION);
bool isAlpha(const UInt32 ver = CURRENT_VERSION);

UInt8   getBetaV(const UInt32 ver = CURRENT_VERSION);
void setBetaV(UInt8 b, UInt32 ver = CURRENT_VERSION);
bool isBeta(const UInt32 ver = CURRENT_VERSION);

UInt8  getMinorV(const UInt32 ver = CURRENT_VERSION);
void setMinorV(UInt8 m, UInt32 ver = CURRENT_VERSION);

UInt16 getMajorV(const UInt32 ver = CURRENT_VERSION);
void setMajorV(UInt16 M, UInt32 ver = CURRENT_VERSION);
