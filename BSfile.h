class BSfile
{
public:
   
    // members
    //void**    m_vtbl;         // 000
    void*       m_readProc;     // 004 - function pointer
    void*       m_writeProc;    // 008 - function pointer
    UInt32      m_bufSize;      // 00C
    UInt32      m_unk010;       // 010 - init'd to m_bufSize
    UInt32      m_unk014;       // 014
    void*       m_buf;          // 018
    FILE*       m_file;         // 01C
    UInt32      m_writeAccess;  // 020
    UInt8       m_good;         // 024
    UInt8       m_pad025[3];    // 025
    UInt8       m_unk028;       // 028
    UInt8       m_pad029[3];    // 029
    UInt32      m_unk02C;       // 02C
    UInt32      m_pos;          // 030
    UInt32      m_unk034;       // 034
    UInt32      m_unk038;       // 038
    char        m_path[0x104];  // 03C
    UInt32      m_unk140;       // 140
    UInt32      m_unk144;       // 144
    UInt32      m_pos2;         // 148 - used if m_pos is 0xFFFFFFFF
    UInt32      m_unk14C;       // 14C
    UInt32      m_fileSize;     // 150
   
    // virtual methods
    virtual /*00*/ void     Destructor(bool freeMemory);
    virtual /*04*/ void     Unk04(void);
    virtual /*08*/ void     Unk08(void);
    virtual /*0C*/ void     Unk0C(void);
    virtual /*10*/ void     Unk10(void);
    virtual /*14*/ void     Unk14(void);   
    virtual /*18*/ void     Unk1C(void);
    virtual /*1C*/ UInt32   GetSize();
    virtual /*20*/ void     Unk20(void);
    virtual /*24*/ void     Unk24(void);
    virtual /*28*/ void     Unk28(void);
    virtual /*2C*/ void     Unk2C(void);
    virtual /*30*/ void     Unk30(void);   
    virtual /*34*/ void     Unk34(void);
    virtual /*38*/ UInt32   Read(void* buffer, UInt32 length);
    virtual /*3C*/ void     Write(void);
};

typedef BSfile* (*LoadBSfile)(const char* fileName, UInt32 access, UInt32 bufferSize);
LoadBSfile loadBSfile = (LoadBSfile)0x00431690;
