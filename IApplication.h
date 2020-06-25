F_DECLARE_INTERFACE(IAppAdviseSink);

#undef  INTERFACE
#define INTERFACE IApplication

DECLARE_INTERFACE_(IApplication, IUnknown)
{
    //
    // IUnknown methods
    //
    DECLARE_UNKNOWN_PURE();

    //
    // Quit the application (conditional, non-error), return non-zero to not quit
    //
    STDMETHOD (QueryQuit)(THIS) PURE;

    //
    // Quit the application (unconditional, non-error)
    //
    STDMETHOD_(void, Quit)(THIS) PURE;

    //
    // Quit the application (unconditional, error)
    //
    STDMETHOD_(void, Abort)(THIS_ const char * pszReason) PURE;

    //
    // Get/Set application name, as displayed in title bar
    //
    STDMETHOD_(void, SetCaption)(THIS_ const char *) PURE;
    STDMETHOD_(const char *, GetCaption)(THIS) PURE;

    //
    // Get/Set default path for file access
    //
    STDMETHOD_(void, SetDefaultFilePath)(THIS_ const char *) PURE;
    STDMETHOD_(const char *, GetDefaultFilePath)(THIS) PURE;

    //
    // Get the full path of the application .EXE
    // i.e., c:\foo\bar.exe
    //
    STDMETHOD_(const char *, GetFullName)(THIS) PURE;

    //
    // Get the full path of the application .EXE
    // i.e., c:\foo
    //
    STDMETHOD_(const char *, GetPath)(THIS) PURE;

    //
    // Display a message box
    //
    STDMETHOD_(int, MessageBox)(THIS_ const char * pszMessage, const char * pszCaption, int fFlags) PURE;

    //
    // Advise/Unadvise for sink/holder protocol
    //
    STDMETHOD (Advise)(THIS_ IAppAdviseSink * pSink, DWORD * pCookie) PURE;
    STDMETHOD (Unadvise)(THIS_ DWORD cookie) PURE;
    
    //
    // Fire a command
    //
    STDMETHOD_(void, AppCommand)(THIS_ unsigned nCmdId) PURE;

};

///////////////////////////////////////

#define IApplication_QueryInterface(p, a, b)    COMQueryInterface(p, a, b)
#define IApplication_AddRef(p)                  COMAddRef(p)
#define IApplication_Release(p)                 COMRelease(p)
#define IApplication_QueryQuit(p)               COMCall0(p, QueryQuit)
#define IApplication_Quit(p)                    COMCall0(p, Quit)
#define IApplication_Abort(p, a)                COMCall1(p, Abort, a)
#define IApplication_SetCaption(p, a)           COMCall1(p, SetCaption, a)
#define IApplication_GetCaption(p)              COMCall0(p, GetCaption)
#define IApplication_SetDefaultFilePath(p, a)   COMCall1(p, SetDefaultFilePath, a)
#define IApplication_GetDefaultFilePath(p)      COMCall0(p, GetDefaultFilePath)
#define IApplication_GetFullName(p)             COMCall0(p, GetFullName)
#define IApplication_GetPath(p)                 COMCall0(p, GetPath)
#define IApplication_MessageBox(p, a, b, c)     COMCall3(p, MessageBox, a, b, c)
#define IApplication_Advise(p, a, b)            COMAdvise(p, a, b)
#define IApplication_Unadvise(p, a)             COMUnadvise(p, a)
