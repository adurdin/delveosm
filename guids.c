#include <stdint.h>
#include <stdio.h>

typedef unsigned long DWORD;
typedef DWORD HMODULE;

HMODULE __stdcall GetModuleHandleA(const char *lpModuleName);

typedef int (__cdecl *MPrintfProc)(const char*, ...);
extern MPrintfProc g_pfnMPrintf;
#define printf g_pfnMPrintf

// ----

#define CINTERFACE
#define interface struct

typedef struct _GUID {
  unsigned long  Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char  Data4[8];
} GUID;

#define DEFINE_GUID(x,d1,d2,d3,d4_0,d4_1,d4_2,d4_3,d4_4,d4_5,d4_6,d4_7) \
    const struct _GUID x = { d1,d2,d3,{d4_0,d4_1,d4_2,d4_3,d4_4,d4_5,d4_6,d4_7} }

#define MAKE_LG_GUID_HIGH_DWORD(number) ((((unsigned long)number & 0xff) << 24) | (((unsigned long)number & 0xff00) << 16) | ((unsigned long)number & 0xffff))

#define DEFINE_LG_GUID(ident, number) \
    DEFINE_GUID(ident, MAKE_LG_GUID_HIGH_DWORD((number)), \
                       (0x7a80 + (number)), \
                       (0x11cf + (number)), \
                       0x83, 0x48, 0x00, 0xaa, 0x00, 0xa8, 0x2b, 0x51)

#define GET_LG_GUID(_pGuid) (*(ushort *)_pGuid)

// ----

//////////////////////////////////////////////////////////////////////////////
//
// Usage macros & classes
//

// Commonly used base macros
#ifdef __cplusplus
#define IID_TO_REFIID(id)               id
#define __COMCallFunc(p, Func)          (p)->Func
#define __COMCallFuncPtr(p, FuncPtr)    ((p)->*FuncPtr)
#define __COMThis(p)
#define __COMThis_(p)
#else
#define IID_TO_REFIID(id)               &(id)
#define __COMCallFunc(p, Func)          ((p)->lpVtbl)->Func
#define __COMCallFuncPtr(p, FuncPtr)    (*FuncPtr)
#define __COMThis(p)                    p
#define __COMThis_(p)                   p,
#endif

///////////////////////////////////////
//
// Generic macros to use when implmenting C wrapper macros.
// These will work in both C and C++ source.
//

#ifndef COMTOOL_NO_WRAPPERS

#define COMCall0(p, Func)                                           __COMCallFunc(p, Func) (__COMThis (p))
#define COMCall1(p, Func, p1)                                       __COMCallFunc(p, Func) (__COMThis_(p) p1)
#define COMCall2(p, Func, p1, p2)                                   __COMCallFunc(p, Func) (__COMThis_(p) p1, p2)
#define COMCall3(p, Func, p1, p2, p3)                               __COMCallFunc(p, Func) (__COMThis_(p) p1, p2, p3)
#define COMCall4(p, Func, p1, p2, p3, p4)                           __COMCallFunc(p, Func) (__COMThis_(p) p1, p2, p3, p4)
#define COMCall5(p, Func, p1, p2, p3, p4, p5)                       __COMCallFunc(p, Func) (__COMThis_(p) p1, p2, p3, p4, p5)
#define COMCall6(p, Func, p1, p2, p3, p4, p5, p6)                   __COMCallFunc(p, Func) (__COMThis_(p) p1, p2, p3, p4, p5, p6)
#define COMCall7(p, Func, p1, p2, p3, p4, p5, p6, p7)               __COMCallFunc(p, Func) (__COMThis_(p) p1, p2, p3, p4, p5, p6, p7)
#define COMCall8(p, Func, p1, p2, p3, p4, p5, p6, p7, p8)           __COMCallFunc(p, Func) (__COMThis_(p) p1, p2, p3, p4, p5, p6, p7, p8)
#define COMCall9(p, Func, p1, p2, p3, p4, p5, p6, p7, p8, p9)       __COMCallFunc(p, Func) (__COMThis_(p) p1, p2, p3, p4, p5, p6, p7, p8, p9)
#define COMCall10(p, Func, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) __COMCallFunc(p, Func) (__COMThis_(p) p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)

#define COMQueryInterface(p, a, b)      COMCall2(p, QueryInterface, IID_TO_REFIID(a), b)
#define COMAddRef(p)                    COMCall0(p, AddRef)
#define COMRelease(p)                   COMCall0(p, Release)

#endif /* COMTOOL_NO_WRAPPERS */

typedef long HRESULT;
typedef unsigned long ULONG;
typedef struct _GUID GUID;
typedef struct _GUID IID;
typedef struct _GUID CLSID;
#ifndef __IID_DEFINED__
#if defined(__cplusplus)
#ifndef _REFGUID_DEFINED
#define _REFGUID_DEFINED
#define REFGUID             const GUID &
#endif // !_REFGUID_DEFINED
#ifndef _REFIID_DEFINED
#define _REFIID_DEFINED
#define REFIID              const IID &
#endif // !_REFIID_DEFINED
#ifndef _REFCLSID_DEFINED
#define _REFCLSID_DEFINED
#define REFCLSID            const CLSID &
#endif // !_REFCLSID_DEFINED
#else // !__cplusplus
#ifndef _REFGUID_DEFINED
#define _REFGUID_DEFINED
#define REFGUID             const GUID * const
#endif // !_REFGUID_DEFINED
#ifndef _REFIID_DEFINED
#define _REFIID_DEFINED
#define REFIID              const IID * const
#endif // !_REFIID_DEFINED
#ifndef _REFCLSID_DEFINED
#define _REFCLSID_DEFINED
#define REFCLSID            const CLSID * const
#endif // !_REFCLSID_DEFINED
#endif // !__cplusplus
#endif // !__IID_DEFINED__

#ifndef __IUnknown_INTERFACE_DEFINED__
#define __IUnknown_INTERFACE_DEFINED__

DEFINE_GUID(IID_IUnknown, 0x00000000L, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

#ifdef CONST_VTABLE
#define CONST_VTBL const
#else
#define CONST_VTBL
#endif

typedef struct IUnknown  IUnknown;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface IUnknown
    {
    public:
        virtual HRESULT __stdcall QueryInterface(
            /* [in] */ REFIID riid,
            /* [out] */ void  **ppvObject) = 0;

        virtual ULONG __stdcall AddRef( void) = 0;

        virtual ULONG __stdcall Release( void) = 0;

    };

#else   /* C style interface */

    typedef struct IUnknownVtbl
    {

        HRESULT ( __stdcall  *QueryInterface )(
            IUnknown  * This,
            /* [in] */ REFIID riid,
            /* [out] */ void  **ppvObject);

        ULONG ( __stdcall  *AddRef )(
            IUnknown  * This);

        ULONG ( __stdcall  *Release )(
            IUnknown  * This);

    } IUnknownVtbl;

    interface IUnknown
    {
        CONST_VTBL struct IUnknownVtbl  *lpVtbl;
    };

#endif
#endif

#ifndef __cplusplus
#define IUnknown_QueryInterface(This,riid,ppvObject)    \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUnknown_AddRef(This)   \
    (This)->lpVtbl -> AddRef(This)

#define IUnknown_Release(This)  \
    (This)->lpVtbl -> Release(This)

#else
#define IUnknown_QueryInterface(p, a, b)   COMQueryInterface(p, a, b)
#define IUnknown_AddRef(p)                 COMAddRef(p)
#define IUnknown_Release(p)                COMRelease(p)
#endif

// ----

#if _MSC_VER > 1000
#pragma once
#endif

// Common macros gleamed from COMPOBJ.H

#ifdef __cplusplus
    #define EXTERN_C    extern "C"
#else
    #define EXTERN_C    extern
#endif

#ifdef _WIN32

// Win32 doesn't support __export

#define STDMETHODCALLTYPE       __stdcall
#define STDMETHODVCALLTYPE      __cdecl

#define STDAPICALLTYPE          __stdcall
#define STDAPIVCALLTYPE         __cdecl

#else

#define STDMETHODCALLTYPE       __export __stdcall
#define STDMETHODVCALLTYPE      __export __cdecl

#define STDAPICALLTYPE          __export __stdcall
#define STDAPIVCALLTYPE         __export __cdecl

#endif

#define STDAPI                  EXTERN_C HRESULT STDAPICALLTYPE
#define STDAPI_(type)           EXTERN_C type STDAPICALLTYPE

#define STDMETHODIMP            HRESULT STDMETHODCALLTYPE
#define STDMETHODIMP_(type)     type STDMETHODCALLTYPE

// The 'V' versions allow Variable Argument lists.

#define STDAPIV                 EXTERN_C HRESULT STDAPIVCALLTYPE
#define STDAPIV_(type)          EXTERN_C type STDAPIVCALLTYPE

#define STDMETHODIMPV           HRESULT STDMETHODVCALLTYPE
#define STDMETHODIMPV_(type)    type STDMETHODVCALLTYPE

/****** Interface Declaration ***********************************************/

/*
 *      These are macros for declaring interfaces.  They exist so that
 *      a single definition of the interface is simulataneously a proper
 *      declaration of the interface structures (C++ abstract classes)
 *      for both C and C++.
 *
 *      DECLARE_INTERFACE(iface) is used to declare an interface that does
 *      not derive from a base interface.
 *      DECLARE_INTERFACE_(iface, baseiface) is used to declare an interface
 *      that does derive from a base interface.
 *
 *      By default if the source file has a .c extension the C version of
 *      the interface declaratations will be expanded; if it has a .cpp
 *      extension the C++ version will be expanded. if you want to force
 *      the C version expansion even though the source file has a .cpp
 *      extension, then define the macro "CINTERFACE".
 *      eg.     cl -DCINTERFACE file.cpp
 *
 *      Example Interface declaration:
 *
 *          #undef  INTERFACE
 *          #define INTERFACE   IClassFactory
 *
 *          DECLARE_INTERFACE_(IClassFactory, IUnknown)
 *          {
 *              // *** IUnknown methods ***
 *              STDMETHOD(QueryInterface) (THIS_
 *                                        REFIID riid,
 *                                        LPVOID FAR* ppvObj) PURE;
 *              STDMETHOD_(ULONG,AddRef) (THIS) PURE;
 *              STDMETHOD_(ULONG,Release) (THIS) PURE;
 *
 *              // *** IClassFactory methods ***
 *              STDMETHOD(CreateInstance) (THIS_
 *                                        LPUNKNOWN pUnkOuter,
 *                                        REFIID riid,
 *                                        LPVOID FAR* ppvObject) PURE;
 *          };
 *
 *      Example C++ expansion:
 *
 *          struct FAR IClassFactory : public IUnknown
 *          {
 *              virtual HRESULT STDMETHODCALLTYPE QueryInterface(
 *                                                  IID FAR& riid,
 *                                                  LPVOID FAR* ppvObj) = 0;
 *              virtual HRESULT STDMETHODCALLTYPE AddRef(void) = 0;
 *              virtual HRESULT STDMETHODCALLTYPE Release(void) = 0;
 *              virtual HRESULT STDMETHODCALLTYPE CreateInstance(
 *                                              LPUNKNOWN pUnkOuter,
 *                                              IID FAR& riid,
 *                                              LPVOID FAR* ppvObject) = 0;
 *          };
 *
 *          NOTE: Our documentation says '#define interface class' but we use
 *          'struct' instead of 'class' to keep a lot of 'public:' lines
 *          out of the interfaces.  The 'FAR' forces the 'this' pointers to
 *          be far, which is what we need.
 *
 *      Example C expansion:
 *
 *          typedef struct IClassFactory
 *          {
 *              const struct IClassFactoryVtbl FAR* lpVtbl;
 *          } IClassFactory;
 *
 *          typedef struct IClassFactoryVtbl IClassFactoryVtbl;
 *
 *          struct IClassFactoryVtbl
 *          {
 *              HRESULT (STDMETHODCALLTYPE * QueryInterface) (
 *                                                  IClassFactory FAR* This,
 *                                                  IID FAR* riid,
 *                                                  LPVOID FAR* ppvObj) ;
 *              HRESULT (STDMETHODCALLTYPE * AddRef) (IClassFactory FAR* This) ;
 *              HRESULT (STDMETHODCALLTYPE * Release) (IClassFactory FAR* This) ;
 *              HRESULT (STDMETHODCALLTYPE * CreateInstance) (
 *                                                  IClassFactory FAR* This,
 *                                                  LPUNKNOWN pUnkOuter,
 *                                                  IID FAR* riid,
 *                                                  LPVOID FAR* ppvObject);
 *              HRESULT (STDMETHODCALLTYPE * LockServer) (
 *                                                  IClassFactory FAR* This,
 *                                                  BOOL fLock);
 *          };
 */

#define FAR

#if defined(__cplusplus) && !defined(CINTERFACE)
//#define interface               struct FAR

#ifdef COM_STDMETHOD_CAN_THROW
#define COM_DECLSPEC_NOTHROW
#else
#define COM_DECLSPEC_NOTHROW DECLSPEC_NOTHROW
#endif

#define __STRUCT__ struct
#define interface __STRUCT__
#define STDMETHOD(method)        virtual COM_DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type,method)  virtual COM_DECLSPEC_NOTHROW type STDMETHODCALLTYPE method
#define STDMETHODV(method)       virtual COM_DECLSPEC_NOTHROW HRESULT STDMETHODVCALLTYPE method
#define STDMETHODV_(type,method) virtual COM_DECLSPEC_NOTHROW type STDMETHODVCALLTYPE method
#define PURE                    = 0
#define THIS_
#define THIS                    void
#define DECLARE_INTERFACE(iface)    interface DECLSPEC_NOVTABLE iface
#define DECLARE_INTERFACE_(iface, baseiface)    interface DECLSPEC_NOVTABLE iface : public baseiface

#define IFACEMETHOD(method)         __override STDMETHOD(method)
#define IFACEMETHOD_(type,method)   __override STDMETHOD_(type,method)
#define IFACEMETHODV(method)        __override STDMETHODV(method)
#define IFACEMETHODV_(type,method)  __override STDMETHODV_(type,method)

#else

#define interface               struct

#define STDMETHOD(method)       HRESULT (STDMETHODCALLTYPE * method)
#define STDMETHOD_(type,method) type (STDMETHODCALLTYPE * method)
#define STDMETHODV(method)       HRESULT (STDMETHODVCALLTYPE * method)
#define STDMETHODV_(type,method) type (STDMETHODVCALLTYPE * method)

#define IFACEMETHOD(method)         __override STDMETHOD(method)
#define IFACEMETHOD_(type,method)   __override STDMETHOD_(type,method)
#define IFACEMETHODV(method)        __override STDMETHODV(method)
#define IFACEMETHODV_(type,method)  __override STDMETHODV_(type,method)



#define PURE
#define THIS_                   INTERFACE FAR* This,
#define THIS                    INTERFACE FAR* This
#ifdef CONST_VTABLE
#define DECLARE_INTERFACE(iface)    typedef interface iface { \
                                    const struct iface##Vtbl FAR* lpVtbl; \
                                } iface; \
                                typedef const struct iface##Vtbl iface##Vtbl; \
                                const struct iface##Vtbl
#else
#define DECLARE_INTERFACE(iface)    typedef interface iface { \
                                    struct iface##Vtbl FAR* lpVtbl; \
                                } iface; \
                                typedef struct iface##Vtbl iface##Vtbl; \
                                struct iface##Vtbl
#endif
#define DECLARE_INTERFACE_(iface, baseiface)    DECLARE_INTERFACE(iface)

#endif

// ----

#define CDECL

// Forward declare an interface
#define F_DECLARE_INTERFACE(iface) \
    interface iface; \
    typedef interface iface iface; \
    EXTERN_C const GUID CDECL FAR IID_##iface

#define DECLARE_UNKNOWN_PURE() \
    \
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, void ** ppvObj) PURE; \
    STDMETHOD_(ULONG,AddRef)  (THIS)  PURE; \
    STDMETHOD_(ULONG,Release) (THIS) PURE

// ----

DEFINE_LG_GUID(IID_IBoolProperty, 0x77);
DEFINE_LG_GUID(IID_IBrushProperty, 0x7d);
DEFINE_LG_GUID(IID_IFloatProperty, 0x142);
DEFINE_LG_GUID(IID_IGlobalIDProperty, 0x7f);
DEFINE_LG_GUID(IID_IIntProperty, 0x7b);
DEFINE_LG_GUID(IID_IInvStringProperty, 0x15a);
DEFINE_LG_GUID(IID_ILabelProperty, 0x7c);
DEFINE_LG_GUID(IID_IProperty, 0x74);
DEFINE_LG_GUID(IID_IPropertyManager, 0x78);
DEFINE_LG_GUID(IID_IPropertyNetworking, 0x20f);
DEFINE_LG_GUID(IID_IPropertyStats, 0x1fd);
DEFINE_LG_GUID(IID_IPropertyStore, 0x139);
DEFINE_LG_GUID(IID_IStringProperty, 0x159);
DEFINE_LG_GUID(IID_IVectorProperty, 0x79);
DEFINE_LG_GUID(CLSID_ActiveMoviePlayer, 0x60);
DEFINE_LG_GUID(CLSID_cAISubCombat, 0x167);
DEFINE_LG_GUID(GUID_AppNet, 0x206);
DEFINE_LG_GUID(GUID_Frob, 0x1fc);
DEFINE_LG_GUID(GUID_lrCache, 0x4f);
DEFINE_LG_GUID(GUID_PhysNet, 0x207);
DEFINE_LG_GUID(GUID_ResCache, 0x8b);
DEFINE_LG_GUID(IID_Editor, 0x28);
DEFINE_LG_GUID(IID_Game, 0x2d);
DEFINE_LG_GUID(IID_Gr2d, 0x1c);
DEFINE_LG_GUID(IID_Gr3d, 0x26);
DEFINE_LG_GUID(IID_IAcousticsProperty, 0xcc);
DEFINE_LG_GUID(IID_IActReactEditors, 0xbc);
DEFINE_LG_GUID(IID_IAdvPickSoundCfgProperty, 0x3a3);
DEFINE_LG_GUID(IID_IAdvPickStateCfgProperty, 0x3a4);
DEFINE_LG_GUID(IID_IAdvPickTransCfgProperty, 0x3a2);
DEFINE_LG_GUID(IID_IAggregate, 0xa);
DEFINE_LG_GUID(IID_IAggregateMemberControl, 0xb);
DEFINE_LG_GUID(IID_IAI, 0xe4);
DEFINE_LG_GUID(IID_IAIAbility, 0x105);
DEFINE_LG_GUID(IID_IAIAction, 0x13b);
DEFINE_LG_GUID(IID_IAIActor, 0x263);
DEFINE_LG_GUID(IID_IAIAlertCapProperty, 0x1a1);
DEFINE_LG_GUID(IID_IAIAlertnessProperty, 0x155);
DEFINE_LG_GUID(IID_IAIAlertResponseProperty, 0x1b1); // DUPLICATE!!
DEFINE_LG_GUID(IID_IAIAlertSenseMultsProperty, 0x219);
DEFINE_LG_GUID(IID_IAIAppServices, 0x215);
DEFINE_LG_GUID(IID_IAIAwareCapProperty, 0x176);
DEFINE_LG_GUID(IID_IAIAwareDelayProperty, 0x21a);
DEFINE_LG_GUID(IID_IAIBehaviorSet, 0x13e);
DEFINE_LG_GUID(IID_IAIBodyResponseProperty, 0x21e);
DEFINE_LG_GUID(IID_IAIBroadcastProperty, 0x19a);
DEFINE_LG_GUID(IID_IAICameraProperty, 0x1a6);
DEFINE_LG_GUID(IID_IAICombatTimingProperty, 0x299);
DEFINE_LG_GUID(IID_IAIComponent, 0x104);
DEFINE_LG_GUID(IID_IAIConversation, 0x1e0);
DEFINE_LG_GUID(IID_IAIConversationManager, 0x1e3);
DEFINE_LG_GUID(IID_IAIConversationProperty, 0x1de);
DEFINE_LG_GUID(IID_IAIConverse, 0x1e4);
DEFINE_LG_GUID(IID_IAIDeviceProperty, 0x1a2);
DEFINE_LG_GUID(IID_IAIEfficiencyProperty, 0x14c);
DEFINE_LG_GUID(IID_IAIFleeConditionsProperty, 0x183);
DEFINE_LG_GUID(IID_IAIFrozenProperty, 0x1fe);
DEFINE_LG_GUID(IID_IAIFrustratedProperty, 0x37d);
DEFINE_LG_GUID(IID_IAIGunDescProperty, 0x16f);
DEFINE_LG_GUID(IID_IAIIdleDirsProperty, 0x195);
DEFINE_LG_GUID(IID_IAIIdleOriginProperty, 0x1ef);
DEFINE_LG_GUID(IID_IAIInform, 0x1ed);
DEFINE_LG_GUID(IID_IAIInformResponseProperty, 0x1ee);
DEFINE_LG_GUID(IID_IAIInvestKindProperty, 0x186);
DEFINE_LG_GUID(IID_IAIManager, 0xe3);
DEFINE_LG_GUID(IID_IAIMarkerBiasesProperty, 0x171);
DEFINE_LG_GUID(IID_IAIModeProperty, 0x157);
DEFINE_LG_GUID(IID_IAIMoveEnactor, 0x102);
DEFINE_LG_GUID(IID_IAIMoveRegulator, 0x101);
DEFINE_LG_GUID(IID_IAINetManager, 0x2af);
DEFINE_LG_GUID(IID_IAINetServices, 0x2b0);
DEFINE_LG_GUID(IID_IAINonCombatDmgRespProperty, 0x250);
DEFINE_LG_GUID(IID_IAINonHostilityProperty, 0x187);
DEFINE_LG_GUID(IID_IAIObjectAvoidProperty, 0x1d2);
DEFINE_LG_GUID(IID_IAIPath, 0x202);
DEFINE_LG_GUID(IID_IAIPathfindControl, 0x20a);
DEFINE_LG_GUID(IID_IAIPathfinder, 0x201);
DEFINE_LG_GUID(IID_IAIPathQuery, 0x21d);
DEFINE_LG_GUID(IID_IAIProperty, 0x93);
DEFINE_LG_GUID(IID_IAIRangedApplicabilitiesProperty, 0x283);
DEFINE_LG_GUID(IID_IAIRangedFleeProperty, 0x282);
DEFINE_LG_GUID(IID_IAIRangedProperty, 0x170);
DEFINE_LG_GUID(IID_IAIRangedRangesProperty, 0x27b);
DEFINE_LG_GUID(IID_IAIRangedShootProperty, 0x286);
DEFINE_LG_GUID(IID_IAIRangedWoundProperty, 0x27c); // DUPLICATE!
DEFINE_LG_GUID(IID_IAIRangedWoundSoundProperty, 0x27c); // DUPLICATE!
DEFINE_LG_GUID(IID_IAIRatingProperty, 0x14d);
DEFINE_LG_GUID(IID_IAIReservedProperty, 0x94);
DEFINE_LG_GUID(IID_IAISenseCombatResponseProperty, 0x1ea);
DEFINE_LG_GUID(IID_IAISenses, 0x100);
DEFINE_LG_GUID(IID_IAISignalResponseProperty, 0x1ac);
DEFINE_LG_GUID(IID_IAISoundEnactor, 0x13c);
DEFINE_LG_GUID(IID_IAISoundTypeProperty, 0x154);
DEFINE_LG_GUID(IID_IAISubability, 0x251);
DEFINE_LG_GUID(IID_IAISuspiciousResponseProperty, 0x414);
DEFINE_LG_GUID(IID_IAIThreatResponseProperty, 0x1b0);
DEFINE_LG_GUID(IID_IAITurretProperty, 0x1a3);
DEFINE_LG_GUID(IID_IAIVisCtrlProperty, 0x175);
DEFINE_LG_GUID(IID_IAIVisibilityModProperty, 0x1b1); // DUPLICATE!
DEFINE_LG_GUID(IID_IAIVisibilityProperty, 0x156);
DEFINE_LG_GUID(IID_IAIVisionDescProperty, 0x174);
DEFINE_LG_GUID(IID_IAIWatchPointProperty, 0x192);
DEFINE_LG_GUID(IID_IAltLinkProperty, 0x384);
DEFINE_LG_GUID(IID_IAmbientProperty, 0xc8);
DEFINE_LG_GUID(IID_IAmbientSoundProperty, 0xa1);
DEFINE_LG_GUID(IID_IAngleLimitProperty, 0x19d);
DEFINE_LG_GUID(IID_IAnimLightProperty, 0xb9);
DEFINE_LG_GUID(IID_IAnimTexProperty, 0x172);
DEFINE_LG_GUID(IID_IAppAdviseSink, 0x8);
DEFINE_LG_GUID(IID_IApplication, 0x9);
DEFINE_LG_GUID(IID_IAsyncReadControl, 0x65);
DEFINE_LG_GUID(IID_IAsyncReadFulfiller, 0x6a);
DEFINE_LG_GUID(IID_IAsyncReadQueue, 0x67);
DEFINE_LG_GUID(IID_IAsyncStreamer, 0x66);
DEFINE_LG_GUID(IID_IAutomapProperty, 0xc9);
DEFINE_LG_GUID(IID_IAvatar, 0x221);
DEFINE_LG_GUID(IID_IBaseGunDescProperty, 0xd5);
DEFINE_LG_GUID(IID_IBashParamsProperty, 0x18a);
DEFINE_LG_GUID(IID_IBeltLinkProperty, 0x383);
DEFINE_LG_GUID(IID_IBipedLengthsProperty, 0x47);
DEFINE_LG_GUID(IID_IBipedModelProperty, 0x4a);
DEFINE_LG_GUID(IID_IBipedProperty, 0x48);
DEFINE_LG_GUID(IID_IBitmapWorldspaceProperty, 0x430);
DEFINE_LG_GUID(IID_IBreathProperty, 0x173);
DEFINE_LG_GUID(IID_ICache, 0x89);
DEFINE_LG_GUID(IID_ICampaign, 0x1e5);
DEFINE_LG_GUID(IID_ICannisterProperty, 0xdc);
DEFINE_LG_GUID(IID_ICDPlayer, 0x227);
DEFINE_LG_GUID(IID_IChat, 0x1e8);
DEFINE_LG_GUID(IID_IColorProperty, 0x180);
DEFINE_LG_GUID(IID_IContainSys, 0x148);
DEFINE_LG_GUID(IID_ICoronaProperty, 0x3f4);
DEFINE_LG_GUID(IID_ICoverPtProperty, 0x19c);
DEFINE_LG_GUID(IID_ICreaturePoseProperty, 0x1a4);
DEFINE_LG_GUID(IID_ICreatureProperty, 0xbf);
DEFINE_LG_GUID(IID_IDamageModel, 0x9a);
DEFINE_LG_GUID(IID_IDataOps, 0x134);
DEFINE_LG_GUID(IID_IDataOpsFile, 0x135); // DUPLICATE!
DEFINE_LG_GUID(IID_IDataOpsMemFile, 0x135); // DUPLICATE!
DEFINE_LG_GUID(IID_IDebugMalloc, 0xa2);
DEFINE_LG_GUID(IID_IDeviceBitmap, 0x79);
DEFINE_LG_GUID(IID_IDeviceComposeBitmap, 0x7a);
DEFINE_LG_GUID(IID_IDisplayDevice, 0x07);
DEFINE_LG_GUID(IID_IDonorCache, 0xa5);
DEFINE_LG_GUID(IID_IDonorQuery, 0x92);
DEFINE_LG_GUID(IID_IDynTexture, 0x27d);
DEFINE_LG_GUID(IID_IEditTools, 0xba);
DEFINE_LG_GUID(IID_IEditTrait, 0xd1);
DEFINE_LG_GUID(IID_IESndTagProperty, 0x13d);
DEFINE_LG_GUID(IID_IExtraLightProperty, 0x14a);
DEFINE_LG_GUID(IID_IFaceProperty, 0x32c);
DEFINE_LG_GUID(IID_IFaceStateProperty, 0x3d4);
DEFINE_LG_GUID(IID_IFlowGroupProperty, 0x1ab);
DEFINE_LG_GUID(IID_IFrameAnimationConfigProperty, 0x166);
DEFINE_LG_GUID(IID_IFrameAnimationStateProperty, 0x165);
DEFINE_LG_GUID(IID_IFrobInfoProperty, 0x54);
DEFINE_LG_GUID(IID_IGameShell, 0x1);
DEFINE_LG_GUID(IID_IGameShellAdviseSink, 0x2);
DEFINE_LG_GUID(IID_IGameStrings, 0x194);
DEFINE_LG_GUID(IID_IGameTools, 0xf3);
DEFINE_LG_GUID(IID_IGunAnimProperty, 0x17c);
DEFINE_LG_GUID(IID_IGunKickProperty, 0x1b7);
DEFINE_LG_GUID(IID_IGunReliabilityProperty, 0x1b3);
DEFINE_LG_GUID(IID_IGunStateProperty, 0xf9);
DEFINE_LG_GUID(IID_IHeartbeatListProperty, 0x273);
DEFINE_LG_GUID(IID_IHeatDiskProperty, 0xad);
DEFINE_LG_GUID(IID_IHostObjIDProperty, 0x1f7);
DEFINE_LG_GUID(IID_IImageSource, 0x109);
DEFINE_LG_GUID(IID_IInputBinder, 0x1f3);
DEFINE_LG_GUID(IID_IInputDevices, 0x5);
DEFINE_LG_GUID(IID_IInterfaceSet, 0xc);
DEFINE_LG_GUID(IID_IInternalAI, 0xff);
DEFINE_LG_GUID(IID_IInventory, 0x15e);
DEFINE_LG_GUID(IID_IInvRenderProperty, 0x168);
DEFINE_LG_GUID(IID_IJointPosProperty, 0x80);
DEFINE_LG_GUID(IID_IKeyInfoProperty, 0xf5);
DEFINE_LG_GUID(IID_IKeySys, 0x177);
DEFINE_LG_GUID(IID_ILGSurface, 0x25e);
DEFINE_LG_GUID(IID_ILightProperty, 0xb8);
DEFINE_LG_GUID(IID_ILinkDataStore, 0x88);
DEFINE_LG_GUID(IID_ILinkManager, 0x82);
DEFINE_LG_GUID(IID_ILinkManagerInternal, 0x85);
DEFINE_LG_GUID(IID_ILinkQuery, 0x83);
DEFINE_LG_GUID(IID_ILinkQueryDatabase, 0x86);
DEFINE_LG_GUID(IID_ILinkStore, 0x87);
DEFINE_LG_GUID(IID_ILoop, 0x5d);
DEFINE_LG_GUID(IID_ILoopClient, 0x18);
DEFINE_LG_GUID(IID_ILoopClientFactory, 0x5c);
DEFINE_LG_GUID(IID_ILoopDispatch, 0x70);
DEFINE_LG_GUID(IID_ILoopManager, 0x1a);
DEFINE_LG_GUID(IID_ILoopMode, 0x19);
DEFINE_LG_GUID(IID_ILoopWatcher, 0x5e);
DEFINE_LG_GUID(IID_ILootProperty, 0x17e);
DEFINE_LG_GUID(IID_IMeshAttachProperty, 0x137);
DEFINE_LG_GUID(IID_IMeshTexProperty, 0x38e); // DUPLICATE!
DEFINE_LG_GUID(IID_IMessageDispatch, 0x208);
DEFINE_LG_GUID(IID_IMidiSequence, 0x13);
DEFINE_LG_GUID(IID_IMidiSequencer, 0x12);
DEFINE_LG_GUID(IID_IMotActorTagListProperty, 0x138);
DEFINE_LG_GUID(IID_IMotGaitDescProperty, 0x136);
DEFINE_LG_GUID(IID_IMotionTable, 0x12d);
DEFINE_LG_GUID(IID_IMotPhysLimitsProperty, 0x131);
DEFINE_LG_GUID(IID_IMotPlayerLimbOffsetsProperty, 0x15b);
DEFINE_LG_GUID(IID_IMoviePlayer1, 0x5f);
DEFINE_LG_GUID(IID_IMovingTerrainProperty, 0x12e);
DEFINE_LG_GUID(IID_INet, 0x166);
DEFINE_LG_GUID(IID_INetAppServices, 0x334);
DEFINE_LG_GUID(IID_INetManager, 0x1a5);
DEFINE_LG_GUID(IID_INetPlayerProperty, 0x1f1);
DEFINE_LG_GUID(IID_INetStats, 0x23d);
DEFINE_LG_GUID(IID_IObjectNetworking, 0x218);
DEFINE_LG_GUID(IID_IObjectQuery, 0x8c);
DEFINE_LG_GUID(IID_IObjectSystem, 0x90);
DEFINE_LG_GUID(IID_IObjEditor, 0xd2);
DEFINE_LG_GUID(IID_IObjEditors, 0xd3);
DEFINE_LG_GUID(IID_IObjIDManager, 0x425);
DEFINE_LG_GUID(IID_IObjIDSink, 0x433);
DEFINE_LG_GUID(IID_IPanelMode, 0x10b);
DEFINE_LG_GUID(IID_IParticleGroupProperty, 0x158);
DEFINE_LG_GUID(IID_IPeriodicPropagator, 0x1b5);
DEFINE_LG_GUID(IID_IPGroupLaunchInfoProperty, 0x1f2);
DEFINE_LG_GUID(IID_IPhysAttrProperty, 0x179);
DEFINE_LG_GUID(IID_IPhysControlProperty, 0x17a);
DEFINE_LG_GUID(IID_IPhysDimsProperty, 0x17b);
DEFINE_LG_GUID(IID_IPhysExplodeProperty, 0x2d5);
DEFINE_LG_GUID(IID_IPhysPPlateProperty, 0x188);
DEFINE_LG_GUID(IID_IPhysRopeProperty, 0x185);
DEFINE_LG_GUID(IID_IPhysStateProperty, 0x7e);
DEFINE_LG_GUID(IID_IPhysTypeProperty, 0x178);
DEFINE_LG_GUID(IID_IPickCfgProperty, 0x112);
DEFINE_LG_GUID(IID_IPickStateProperty, 0x118);
DEFINE_LG_GUID(IID_IPlayerGunDescProperty, 0x16e);
DEFINE_LG_GUID(IID_IPositionProperty, 0x12c);
DEFINE_LG_GUID(IID_IPrimaryInputDevicesSink, 0x6);
DEFINE_LG_GUID(IID_IProjectileProperty, 0x190);
DEFINE_LG_GUID(IID_IPropagation, 0xac);
DEFINE_LG_GUID(IID_IPropagator, 0xa9);
DEFINE_LG_GUID(IID_IPropagatorQuery, 0xab);
DEFINE_LG_GUID(IID_IPuppetProperty, 0xfa);
DEFINE_LG_GUID(IID_IQuestData, 0x14e);
DEFINE_LG_GUID(IID_IQuestDataIter, 0x14f);
DEFINE_LG_GUID(IID_IQuestVarProperty, 0x198);
DEFINE_LG_GUID(IID_IRangedCombatProperty, 0x19e);
DEFINE_LG_GUID(IID_IReactionQuery, 0xbb);
DEFINE_LG_GUID(IID_IReactions, 0xb0);
DEFINE_LG_GUID(IID_IReceptronQuery, 0xa8);
DEFINE_LG_GUID(IID_IRecorder, 0x61);
DEFINE_LG_GUID(IID_IRelation, 0x84);
DEFINE_LG_GUID(IID_IRenderG, 0x292);
DEFINE_LG_GUID(IID_IRendFlashProperty, 0x169);
DEFINE_LG_GUID(IID_IRG_CPUID, 0x2f3);
DEFINE_LG_GUID(IID_IRGBillboard, 0x312);
DEFINE_LG_GUID(IID_IRGCanvas, 0x287);
DEFINE_LG_GUID(IID_IRGCore, 0x2a3);
DEFINE_LG_GUID(IID_IRGDisplayCanvas, 0x290);
DEFINE_LG_GUID(IID_IRGFontSys, 0x291);
DEFINE_LG_GUID(IID_IRGGraphicCaps, 0x2e7);
DEFINE_LG_GUID(IID_IRGObjFactory, 0x30b);
DEFINE_LG_GUID(IID_IRGOverlay, 0x306);
DEFINE_LG_GUID(IID_IRGOverlays, 0x305);
DEFINE_LG_GUID(IID_IRGOverlaySys, 0x346 );
DEFINE_LG_GUID(IID_IRGShader, 0x30f );
DEFINE_LG_GUID(IID_IRGTexDriver, 0x310 );
DEFINE_LG_GUID(IID_IRGTexMng, 0x307);
DEFINE_LG_GUID(IID_IRGTexRectangle, 0x345 );
DEFINE_LG_GUID(IID_IRGView, 0x308);
DEFINE_LG_GUID(IID_IRoomGravityProperty, 0x143);
DEFINE_LG_GUID(IID_IRoomScriptProperty, 0xca);
DEFINE_LG_GUID(IID_IRotDoorProperty, 0xde);
DEFINE_LG_GUID(IID_IScaleProperty, 0x92);
DEFINE_LG_GUID(IID_ISchemaLoopParamsProperty, 0x98);
DEFINE_LG_GUID(IID_ISchemaPlayParamsProperty, 0x96);
DEFINE_LG_GUID(IID_ISchemaTagConstraintProperty, 0x9b);
DEFINE_LG_GUID(IID_IScript, 0xd0);
DEFINE_LG_GUID(IID_IScriptMan, 0xcf);
DEFINE_LG_GUID(IID_IScriptModule, 0xd4);
DEFINE_LG_GUID(IID_IScriptNet, 0x23e);
DEFINE_LG_GUID(IID_IScriptProperty, 0xe1);
DEFINE_LG_GUID(IID_ISharedCache, 0x8a);
DEFINE_LG_GUID(IID_ISimManager, 0x149);
DEFINE_LG_GUID(IID_ISndMixer, 0x11);
DEFINE_LG_GUID(IID_ISndSample, 0x10);
DEFINE_LG_GUID(IID_ISong, 0x259);
DEFINE_LG_GUID(IID_ISongEvent, 0x25c);
DEFINE_LG_GUID(IID_ISongGoto, 0x25d);
DEFINE_LG_GUID(IID_ISongPlayer, 0x26a);
DEFINE_LG_GUID(IID_ISongSample, 0x25b);
DEFINE_LG_GUID(IID_ISongSection, 0x25a);
DEFINE_LG_GUID(IID_ISparkProperty, 0xb2);
DEFINE_LG_GUID(IID_ISpeechProperty, 0x99);
DEFINE_LG_GUID(IID_IStimSensorQuery, 0xb4);
DEFINE_LG_GUID(IID_IStimSensors, 0xa6);
DEFINE_LG_GUID(IID_IStimSourceQuery, 0xb3);
DEFINE_LG_GUID(IID_IStimSources, 0xa7);
DEFINE_LG_GUID(IID_IStimulator, 0xb1);
DEFINE_LG_GUID(IID_IStimuli, 0xaa);
DEFINE_LG_GUID(IID_IStructDescTools, 0xbd);
DEFINE_LG_GUID(IID_IStructEditor, 0xbe);
DEFINE_LG_GUID(IID_ISuspiciousProperty, 0x415);
DEFINE_LG_GUID(IID_ITagFile, 0x38);
DEFINE_LG_GUID(IID_ITagFileIter, 0xc0);
DEFINE_LG_GUID(IID_IThreadManager, 0x6f);
DEFINE_LG_GUID(IID_ITrait, 0x8d);
DEFINE_LG_GUID(IID_ITraitManager, 0x8f);
DEFINE_LG_GUID(IID_ITransDoorProperty, 0xe2);
DEFINE_LG_GUID(IID_ITweqEmitterProperty, 0x59); // DUPLICATE!
DEFINE_LG_GUID(IID_ITweqJointsProperty, 0x53);
DEFINE_LG_GUID(IID_ITweqJointsStateProperty, 0x75);
DEFINE_LG_GUID(IID_ITweqLockProperty, 0x17f);
DEFINE_LG_GUID(IID_ITweqLockStateProperty, 0x181);
DEFINE_LG_GUID(IID_ITweqModelsProperty, 0x56);
DEFINE_LG_GUID(IID_ITweqSimpleProperty, 0x51);
DEFINE_LG_GUID(IID_ITweqSimpleStateProperty, 0x52);
DEFINE_LG_GUID(IID_ITweqVectorProperty, 0x55);
DEFINE_LG_GUID(IID_ITweqVectorStateProperty, 0x4e);
DEFINE_LG_GUID(IID_IVantagePtProperty, 0x19b);
DEFINE_LG_GUID(IID_IVoiceOverSys, 0x1da);
DEFINE_LG_GUID(IID_IWaterColorProperty, 0x1e2);
DEFINE_LG_GUID(IID_IWeaponOffsetProperty, 0x38a);
DEFINE_LG_GUID(IID_IWeatherProperty, 0x38e); // DUPLICATE!
DEFINE_LG_GUID(IID_IWinApp, 0x3);
DEFINE_LG_GUID(IID_IWinAppAdviseSink, 0x4);
DEFINE_LG_GUID(IID_IWinDisplayDevice, 0x62);
DEFINE_LG_GUID(IID_IWinShell, 0x5b);
DEFINE_LG_GUID(IID_LoopApp, 0x1f);
DEFINE_LG_GUID(IID_Portal, 0x27);
DEFINE_LG_GUID(IID_Res, 0x1d);
DEFINE_LG_GUID(IID_Snd, 0x37);
DEFINE_LG_GUID(IID_UI, 0x24);
DEFINE_LG_GUID(LOOPID_ActReact, 0x4d);
DEFINE_LG_GUID(LOOPID_AI, 0x39);
DEFINE_LG_GUID(LOOPID_AllClients, 0x35);
DEFINE_LG_GUID(LOOPID_AnimTexture, 0x16d);
DEFINE_LG_GUID(LOOPID_AutomapClient, 0x11a);
DEFINE_LG_GUID(LOOPID_Base, 0x2f);
DEFINE_LG_GUID(LOOPID_BaseMode, 0x2e);
DEFINE_LG_GUID(LOOPID_Biped, 0x34); // DUPLICATE!
DEFINE_LG_GUID(LOOPID_BrushList, 0x3a);
DEFINE_LG_GUID(LOOPID_CreatureWeapon, 0x3a9);
DEFINE_LG_GUID(LOOPID_DarkBaseClients, 0xa0);
DEFINE_LG_GUID(LOOPID_DarkGameClients, 0x9f);
DEFINE_LG_GUID(LOOPID_DarkPanel, 0x197);
DEFINE_LG_GUID(LOOPID_DarkRender, 0x9e);
DEFINE_LG_GUID(LOOPID_DarkSim, 0x9d);
DEFINE_LG_GUID(LOOPID_Debrief, 0x18f);
DEFINE_LG_GUID(LOOPID_DebugMode, 0x20);
DEFINE_LG_GUID(LOOPID_Dialog, 0x59); // DUPLICATE!
DEFINE_LG_GUID(LOOPID_DialogMode, 0x58);
DEFINE_LG_GUID(LOOPID_Display, 0x4b);
DEFINE_LG_GUID(LOOPID_EditGeom, 0x29);
DEFINE_LG_GUID(LOOPID_EditMode, 0x22);
DEFINE_LG_GUID(LOOPID_Editor, 0x2a);
DEFINE_LG_GUID(LOOPID_EngineFeatures, 0x103);
DEFINE_LG_GUID(LOOPID_EngineFeaturesClients, 0x107);
DEFINE_LG_GUID(LOOPID_EngineFeaturesRend, 0x106);
DEFINE_LG_GUID(LOOPID_FileVar, 0x182);
DEFINE_LG_GUID(LOOPID_Game, 0x2c);
DEFINE_LG_GUID(LOOPID_GameMode, 0x2b);
DEFINE_LG_GUID(LOOPID_Ghost, 0x2c8);
DEFINE_LG_GUID(LOOPID_LevelTrans, 0x247);
DEFINE_LG_GUID(LOOPID_LinkMan, 0x31);
DEFINE_LG_GUID(LOOPID_MetaGame, 0x11c);
DEFINE_LG_GUID(LOOPID_MetaGameClients, 0x11d);
DEFINE_LG_GUID(LOOPID_Mission, 0x1ad);
DEFINE_LG_GUID(LOOPID_MovieClient, 0x10f);
DEFINE_LG_GUID(LOOPID_NetPhysics, 0x3c);
DEFINE_LG_GUID(LOOPID_Network, 0x1a7);
DEFINE_LG_GUID(LOOPID_NetworkReset, 0x298);
DEFINE_LG_GUID(LOOPID_NetworkSim, 0x2ae);
DEFINE_LG_GUID(LOOPID_ObjNet, 0x268);
DEFINE_LG_GUID(LOOPID_ObjSys, 0x36);
DEFINE_LG_GUID(LOOPID_Panel, 0x10a);
DEFINE_LG_GUID(LOOPID_People, 0x34); // DUPLICATE!
DEFINE_LG_GUID(LOOPID_Physics, 0x3b);
DEFINE_LG_GUID(LOOPID_PhysicsBase, 0x1ce);
DEFINE_LG_GUID(LOOPID_Player, 0x3d);
DEFINE_LG_GUID(LOOPID_Quest, 0x151);
DEFINE_LG_GUID(LOOPID_Render, 0x45);
DEFINE_LG_GUID(LOOPID_RenderBase, 0x147);
DEFINE_LG_GUID(LOOPID_Res, 0x23);
DEFINE_LG_GUID(LOOPID_Room, 0x50);
DEFINE_LG_GUID(LOOPID_Schema, 0x97);
DEFINE_LG_GUID(LOOPID_ScrnMan, 0x1e);
DEFINE_LG_GUID(LOOPID_SimFinish, 0x3f);
DEFINE_LG_GUID(LOOPID_SimTime, 0x4c);
DEFINE_LG_GUID(LOOPID_Sound, 0x44);
DEFINE_LG_GUID(LOOPID_Test, 0x21);
DEFINE_LG_GUID(LOOPID_UI, 0x25);
DEFINE_LG_GUID(LOOPID_Wr, 0x49);
DEFINE_LG_GUID(LOOPMODE_Automap, 0x119);
DEFINE_LG_GUID(LOOPMODE_DarkPanel, 0x196);
DEFINE_LG_GUID(LOOPMODE_Debrief, 0x18e);
DEFINE_LG_GUID(LOOPMODE_EndGame, 0x11e);
DEFINE_LG_GUID(LOOPMODE_LevelTrans, 0x248);
DEFINE_LG_GUID(LOOPMODE_MetaGame, 0x11b);
DEFINE_LG_GUID(LOOPMODE_Mission, 0x1ae);
DEFINE_LG_GUID(LOOPMODE_Movie, 0x110);
DEFINE_LG_GUID(LOOPMODE_StaticImagePanel, 0x10c);
DEFINE_LG_GUID(SCRNMAN_PRESERVE_DDRAW, 0x12a);
DEFINE_LG_GUID(SIM_Loot, 0x1eb);
DEFINE_LG_GUID(SIMID_MediaPropagator, 0x1b6);
DEFINE_LG_GUID(UUID_AIApp, 0x32);
DEFINE_LG_GUID(UUID_Dark, 0x9c);
DEFINE_LG_GUID(UUID_Dispatch, 0x30);
DEFINE_LG_GUID(UUID_InputLib, 0x6e);
DEFINE_LG_GUID(UUID_Res, 0x71);

// ----

typedef struct _IIDINFO {
    REFIID refiid;
    const char *name;
} IIDINFO;

#define IIDINFO(x) { &x, #x }

static IIDINFO IIDInfo[] = {
    IIDINFO(IID_IBoolProperty),
    IIDINFO(IID_IBrushProperty),
    IIDINFO(IID_IFloatProperty),
    IIDINFO(IID_IGlobalIDProperty),
    IIDINFO(IID_IIntProperty),
    IIDINFO(IID_IInvStringProperty),
    IIDINFO(IID_ILabelProperty),
    IIDINFO(IID_IProperty),
    IIDINFO(IID_IPropertyManager),
    IIDINFO(IID_IPropertyNetworking),
    IIDINFO(IID_IPropertyStats),
    IIDINFO(IID_IPropertyStore),
    IIDINFO(IID_IStringProperty),
    IIDINFO(IID_IVectorProperty),
    IIDINFO(CLSID_ActiveMoviePlayer),
    IIDINFO(CLSID_cAISubCombat),
    IIDINFO(GUID_AppNet),
    IIDINFO(GUID_Frob),
    IIDINFO(GUID_lrCache),
    IIDINFO(GUID_PhysNet),
    IIDINFO(GUID_ResCache),
    IIDINFO(IID_Editor),
    IIDINFO(IID_Game),
    IIDINFO(IID_Gr2d),
    IIDINFO(IID_Gr3d),
    IIDINFO(IID_IAcousticsProperty),
    IIDINFO(IID_IActReactEditors),
    IIDINFO(IID_IAdvPickSoundCfgProperty),
    IIDINFO(IID_IAdvPickStateCfgProperty),
    IIDINFO(IID_IAdvPickTransCfgProperty),
    IIDINFO(IID_IAggregate),
    IIDINFO(IID_IAggregateMemberControl),
    IIDINFO(IID_IAI),
    IIDINFO(IID_IAIAbility),
    IIDINFO(IID_IAIAction),
    IIDINFO(IID_IAIActor),
    IIDINFO(IID_IAIAlertCapProperty),
    IIDINFO(IID_IAIAlertnessProperty),
    IIDINFO(IID_IAIAlertResponseProperty),
    IIDINFO(IID_IAIAlertSenseMultsProperty),
    IIDINFO(IID_IAIAppServices),
    IIDINFO(IID_IAIAwareCapProperty),
    IIDINFO(IID_IAIAwareDelayProperty),
    IIDINFO(IID_IAIBehaviorSet),
    IIDINFO(IID_IAIBodyResponseProperty),
    IIDINFO(IID_IAIBroadcastProperty),
    IIDINFO(IID_IAICameraProperty),
    IIDINFO(IID_IAICombatTimingProperty),
    IIDINFO(IID_IAIComponent),
    IIDINFO(IID_IAIConversation),
    IIDINFO(IID_IAIConversationManager),
    IIDINFO(IID_IAIConversationProperty),
    IIDINFO(IID_IAIConverse),
    IIDINFO(IID_IAIDeviceProperty),
    IIDINFO(IID_IAIEfficiencyProperty),
    IIDINFO(IID_IAIFleeConditionsProperty),
    IIDINFO(IID_IAIFrozenProperty),
    IIDINFO(IID_IAIFrustratedProperty),
    IIDINFO(IID_IAIGunDescProperty),
    IIDINFO(IID_IAIIdleDirsProperty),
    IIDINFO(IID_IAIIdleOriginProperty),
    IIDINFO(IID_IAIInform),
    IIDINFO(IID_IAIInformResponseProperty),
    IIDINFO(IID_IAIInvestKindProperty),
    IIDINFO(IID_IAIManager),
    IIDINFO(IID_IAIMarkerBiasesProperty),
    IIDINFO(IID_IAIModeProperty),
    IIDINFO(IID_IAIMoveEnactor),
    IIDINFO(IID_IAIMoveRegulator),
    IIDINFO(IID_IAINetManager),
    IIDINFO(IID_IAINetServices),
    IIDINFO(IID_IAINonCombatDmgRespProperty),
    IIDINFO(IID_IAINonHostilityProperty),
    IIDINFO(IID_IAIObjectAvoidProperty),
    IIDINFO(IID_IAIPath),
    IIDINFO(IID_IAIPathfindControl),
    IIDINFO(IID_IAIPathfinder),
    IIDINFO(IID_IAIPathQuery),
    IIDINFO(IID_IAIProperty),
    IIDINFO(IID_IAIRangedApplicabilitiesProperty),
    IIDINFO(IID_IAIRangedFleeProperty),
    IIDINFO(IID_IAIRangedProperty),
    IIDINFO(IID_IAIRangedRangesProperty),
    IIDINFO(IID_IAIRangedShootProperty),
    IIDINFO(IID_IAIRangedWoundProperty),
    IIDINFO(IID_IAIRangedWoundSoundProperty),
    IIDINFO(IID_IAIRatingProperty),
    IIDINFO(IID_IAIReservedProperty),
    IIDINFO(IID_IAISenseCombatResponseProperty),
    IIDINFO(IID_IAISenses),
    IIDINFO(IID_IAISignalResponseProperty),
    IIDINFO(IID_IAISoundEnactor),
    IIDINFO(IID_IAISoundTypeProperty),
    IIDINFO(IID_IAISubability),
    IIDINFO(IID_IAISuspiciousResponseProperty),
    IIDINFO(IID_IAIThreatResponseProperty),
    IIDINFO(IID_IAITurretProperty),
    IIDINFO(IID_IAIVisCtrlProperty),
    IIDINFO(IID_IAIVisibilityModProperty),
    IIDINFO(IID_IAIVisibilityProperty),
    IIDINFO(IID_IAIVisionDescProperty),
    IIDINFO(IID_IAIWatchPointProperty),
    IIDINFO(IID_IAltLinkProperty),
    IIDINFO(IID_IAmbientProperty),
    IIDINFO(IID_IAmbientSoundProperty),
    IIDINFO(IID_IAngleLimitProperty),
    IIDINFO(IID_IAnimLightProperty),
    IIDINFO(IID_IAnimTexProperty),
    IIDINFO(IID_IAppAdviseSink),
    IIDINFO(IID_IApplication),
    IIDINFO(IID_IAsyncReadControl),
    IIDINFO(IID_IAsyncReadFulfiller),
    IIDINFO(IID_IAsyncReadQueue),
    IIDINFO(IID_IAsyncStreamer),
    IIDINFO(IID_IAutomapProperty),
    IIDINFO(IID_IAvatar),
    IIDINFO(IID_IBaseGunDescProperty),
    IIDINFO(IID_IBashParamsProperty),
    IIDINFO(IID_IBeltLinkProperty),
    IIDINFO(IID_IBipedLengthsProperty),
    IIDINFO(IID_IBipedModelProperty),
    IIDINFO(IID_IBipedProperty),
    IIDINFO(IID_IBitmapWorldspaceProperty),
    IIDINFO(IID_IBreathProperty),
    IIDINFO(IID_ICache),
    IIDINFO(IID_ICampaign),
    IIDINFO(IID_ICannisterProperty),
    IIDINFO(IID_ICDPlayer),
    IIDINFO(IID_IChat),
    IIDINFO(IID_IColorProperty),
    IIDINFO(IID_IContainSys),
    IIDINFO(IID_ICoronaProperty),
    IIDINFO(IID_ICoverPtProperty),
    IIDINFO(IID_ICreaturePoseProperty),
    IIDINFO(IID_ICreatureProperty),
    IIDINFO(IID_IDamageModel),
    IIDINFO(IID_IDataOps),
    IIDINFO(IID_IDataOpsFile),
    IIDINFO(IID_IDataOpsMemFile),
    IIDINFO(IID_IDebugMalloc),
    IIDINFO(IID_IDeviceBitmap),
    IIDINFO(IID_IDeviceComposeBitmap),
    IIDINFO(IID_IDisplayDevice),
    IIDINFO(IID_IDonorCache),
    IIDINFO(IID_IDonorQuery),
    IIDINFO(IID_IDynTexture),
    IIDINFO(IID_IEditTools),
    IIDINFO(IID_IEditTrait),
    IIDINFO(IID_IESndTagProperty),
    IIDINFO(IID_IExtraLightProperty),
    IIDINFO(IID_IFaceProperty),
    IIDINFO(IID_IFaceStateProperty),
    IIDINFO(IID_IFlowGroupProperty),
    IIDINFO(IID_IFrameAnimationConfigProperty),
    IIDINFO(IID_IFrameAnimationStateProperty),
    IIDINFO(IID_IFrobInfoProperty),
    IIDINFO(IID_IGameShell),
    IIDINFO(IID_IGameShellAdviseSink),
    IIDINFO(IID_IGameStrings),
    IIDINFO(IID_IGameTools),
    IIDINFO(IID_IGunAnimProperty),
    IIDINFO(IID_IGunKickProperty),
    IIDINFO(IID_IGunReliabilityProperty),
    IIDINFO(IID_IGunStateProperty),
    IIDINFO(IID_IHeartbeatListProperty),
    IIDINFO(IID_IHeatDiskProperty),
    IIDINFO(IID_IHostObjIDProperty),
    IIDINFO(IID_IImageSource),
    IIDINFO(IID_IInputBinder),
    IIDINFO(IID_IInputDevices),
    IIDINFO(IID_IInterfaceSet),
    IIDINFO(IID_IInternalAI),
    IIDINFO(IID_IInventory),
    IIDINFO(IID_IInvRenderProperty),
    IIDINFO(IID_IJointPosProperty),
    IIDINFO(IID_IKeyInfoProperty),
    IIDINFO(IID_IKeySys),
    IIDINFO(IID_ILGSurface),
    IIDINFO(IID_ILightProperty),
    IIDINFO(IID_ILinkDataStore),
    IIDINFO(IID_ILinkManager),
    IIDINFO(IID_ILinkManagerInternal),
    IIDINFO(IID_ILinkQuery),
    IIDINFO(IID_ILinkQueryDatabase),
    IIDINFO(IID_ILinkStore),
    IIDINFO(IID_ILoop),
    IIDINFO(IID_ILoopClient),
    IIDINFO(IID_ILoopClientFactory),
    IIDINFO(IID_ILoopDispatch),
    IIDINFO(IID_ILoopManager),
    IIDINFO(IID_ILoopMode),
    IIDINFO(IID_ILoopWatcher),
    IIDINFO(IID_ILootProperty),
    IIDINFO(IID_IMeshAttachProperty),
    IIDINFO(IID_IMeshTexProperty),
    IIDINFO(IID_IMessageDispatch),
    IIDINFO(IID_IMidiSequence),
    IIDINFO(IID_IMidiSequencer),
    IIDINFO(IID_IMotActorTagListProperty),
    IIDINFO(IID_IMotGaitDescProperty),
    IIDINFO(IID_IMotionTable),
    IIDINFO(IID_IMotPhysLimitsProperty),
    IIDINFO(IID_IMotPlayerLimbOffsetsProperty),
    IIDINFO(IID_IMoviePlayer1),
    IIDINFO(IID_IMovingTerrainProperty),
    IIDINFO(IID_INet),
    IIDINFO(IID_INetAppServices),
    IIDINFO(IID_INetManager),
    IIDINFO(IID_INetPlayerProperty),
    IIDINFO(IID_INetStats),
    IIDINFO(IID_IObjectNetworking),
    IIDINFO(IID_IObjectQuery),
    IIDINFO(IID_IObjectSystem),
    IIDINFO(IID_IObjEditor),
    IIDINFO(IID_IObjEditors),
    IIDINFO(IID_IObjIDManager),
    IIDINFO(IID_IObjIDSink),
    IIDINFO(IID_IPanelMode),
    IIDINFO(IID_IParticleGroupProperty),
    IIDINFO(IID_IPeriodicPropagator),
    IIDINFO(IID_IPGroupLaunchInfoProperty),
    IIDINFO(IID_IPhysAttrProperty),
    IIDINFO(IID_IPhysControlProperty),
    IIDINFO(IID_IPhysDimsProperty),
    IIDINFO(IID_IPhysExplodeProperty),
    IIDINFO(IID_IPhysPPlateProperty),
    IIDINFO(IID_IPhysRopeProperty),
    IIDINFO(IID_IPhysStateProperty),
    IIDINFO(IID_IPhysTypeProperty),
    IIDINFO(IID_IPickCfgProperty),
    IIDINFO(IID_IPickStateProperty),
    IIDINFO(IID_IPlayerGunDescProperty),
    IIDINFO(IID_IPositionProperty),
    IIDINFO(IID_IPrimaryInputDevicesSink),
    IIDINFO(IID_IProjectileProperty),
    IIDINFO(IID_IPropagation),
    IIDINFO(IID_IPropagator),
    IIDINFO(IID_IPropagatorQuery),
    IIDINFO(IID_IPuppetProperty),
    IIDINFO(IID_IQuestData),
    IIDINFO(IID_IQuestDataIter),
    IIDINFO(IID_IQuestVarProperty),
    IIDINFO(IID_IRangedCombatProperty),
    IIDINFO(IID_IReactionQuery),
    IIDINFO(IID_IReactions),
    IIDINFO(IID_IReceptronQuery),
    IIDINFO(IID_IRecorder),
    IIDINFO(IID_IRelation),
    IIDINFO(IID_IRenderG),
    IIDINFO(IID_IRendFlashProperty),
    IIDINFO(IID_IRG_CPUID),
    IIDINFO(IID_IRGBillboard),
    IIDINFO(IID_IRGCanvas),
    IIDINFO(IID_IRGCore),
    IIDINFO(IID_IRGDisplayCanvas),
    IIDINFO(IID_IRGFontSys),
    IIDINFO(IID_IRGGraphicCaps),
    IIDINFO(IID_IRGObjFactory),
    IIDINFO(IID_IRGOverlay),
    IIDINFO(IID_IRGOverlays),
    IIDINFO(IID_IRGOverlaySys),
    IIDINFO(IID_IRGShader),
    IIDINFO(IID_IRGTexDriver),
    IIDINFO(IID_IRGTexMng),
    IIDINFO(IID_IRGTexRectangle),
    IIDINFO(IID_IRGView),
    IIDINFO(IID_IRoomGravityProperty),
    IIDINFO(IID_IRoomScriptProperty),
    IIDINFO(IID_IRotDoorProperty),
    IIDINFO(IID_IScaleProperty),
    IIDINFO(IID_ISchemaLoopParamsProperty),
    IIDINFO(IID_ISchemaPlayParamsProperty),
    IIDINFO(IID_ISchemaTagConstraintProperty),
    IIDINFO(IID_IScript),
    IIDINFO(IID_IScriptMan),
    IIDINFO(IID_IScriptModule),
    IIDINFO(IID_IScriptNet),
    IIDINFO(IID_IScriptProperty),
    IIDINFO(IID_ISharedCache),
    IIDINFO(IID_ISimManager),
    IIDINFO(IID_ISndMixer),
    IIDINFO(IID_ISndSample),
    IIDINFO(IID_ISong),
    IIDINFO(IID_ISongEvent),
    IIDINFO(IID_ISongGoto),
    IIDINFO(IID_ISongPlayer),
    IIDINFO(IID_ISongSample),
    IIDINFO(IID_ISongSection),
    IIDINFO(IID_ISparkProperty),
    IIDINFO(IID_ISpeechProperty),
    IIDINFO(IID_IStimSensorQuery),
    IIDINFO(IID_IStimSensors),
    IIDINFO(IID_IStimSourceQuery),
    IIDINFO(IID_IStimSources),
    IIDINFO(IID_IStimulator),
    IIDINFO(IID_IStimuli),
    IIDINFO(IID_IStructDescTools),
    IIDINFO(IID_IStructEditor),
    IIDINFO(IID_ISuspiciousProperty),
    IIDINFO(IID_ITagFile),
    IIDINFO(IID_ITagFileIter),
    IIDINFO(IID_IThreadManager),
    IIDINFO(IID_ITrait),
    IIDINFO(IID_ITraitManager),
    IIDINFO(IID_ITransDoorProperty),
    IIDINFO(IID_ITweqEmitterProperty),
    IIDINFO(IID_ITweqJointsProperty),
    IIDINFO(IID_ITweqJointsStateProperty),
    IIDINFO(IID_ITweqLockProperty),
    IIDINFO(IID_ITweqLockStateProperty),
    IIDINFO(IID_ITweqModelsProperty),
    IIDINFO(IID_ITweqSimpleProperty),
    IIDINFO(IID_ITweqSimpleStateProperty),
    IIDINFO(IID_ITweqVectorProperty),
    IIDINFO(IID_ITweqVectorStateProperty),
    IIDINFO(IID_IVantagePtProperty),
    IIDINFO(IID_IVoiceOverSys),
    IIDINFO(IID_IWaterColorProperty),
    IIDINFO(IID_IWeaponOffsetProperty),
    IIDINFO(IID_IWeatherProperty),
    IIDINFO(IID_IWinApp),
    IIDINFO(IID_IWinAppAdviseSink),
    IIDINFO(IID_IWinDisplayDevice),
    IIDINFO(IID_IWinShell),
    IIDINFO(IID_LoopApp),
    IIDINFO(IID_Portal),
    IIDINFO(IID_Res),
    IIDINFO(IID_Snd),
    IIDINFO(IID_UI),
    IIDINFO(LOOPID_ActReact),
    IIDINFO(LOOPID_AI),
    IIDINFO(LOOPID_AllClients),
    IIDINFO(LOOPID_AnimTexture),
    IIDINFO(LOOPID_AutomapClient),
    IIDINFO(LOOPID_Base),
    IIDINFO(LOOPID_BaseMode),
    IIDINFO(LOOPID_Biped),
    IIDINFO(LOOPID_BrushList),
    IIDINFO(LOOPID_CreatureWeapon),
    IIDINFO(LOOPID_DarkBaseClients),
    IIDINFO(LOOPID_DarkGameClients),
    IIDINFO(LOOPID_DarkPanel),
    IIDINFO(LOOPID_DarkRender),
    IIDINFO(LOOPID_DarkSim),
    IIDINFO(LOOPID_Debrief),
    IIDINFO(LOOPID_DebugMode),
    IIDINFO(LOOPID_Dialog),
    IIDINFO(LOOPID_DialogMode),
    IIDINFO(LOOPID_Display),
    IIDINFO(LOOPID_EditGeom),
    IIDINFO(LOOPID_EditMode),
    IIDINFO(LOOPID_Editor),
    IIDINFO(LOOPID_EngineFeatures),
    IIDINFO(LOOPID_EngineFeaturesClients),
    IIDINFO(LOOPID_EngineFeaturesRend),
    IIDINFO(LOOPID_FileVar),
    IIDINFO(LOOPID_Game),
    IIDINFO(LOOPID_GameMode),
    IIDINFO(LOOPID_Ghost),
    IIDINFO(LOOPID_LevelTrans),
    IIDINFO(LOOPID_LinkMan),
    IIDINFO(LOOPID_MetaGame),
    IIDINFO(LOOPID_MetaGameClients),
    IIDINFO(LOOPID_Mission),
    IIDINFO(LOOPID_MovieClient),
    IIDINFO(LOOPID_NetPhysics),
    IIDINFO(LOOPID_Network),
    IIDINFO(LOOPID_NetworkReset),
    IIDINFO(LOOPID_NetworkSim),
    IIDINFO(LOOPID_ObjNet),
    IIDINFO(LOOPID_ObjSys),
    IIDINFO(LOOPID_Panel),
    IIDINFO(LOOPID_People),
    IIDINFO(LOOPID_Physics),
    IIDINFO(LOOPID_PhysicsBase),
    IIDINFO(LOOPID_Player),
    IIDINFO(LOOPID_Quest),
    IIDINFO(LOOPID_Render),
    IIDINFO(LOOPID_RenderBase),
    IIDINFO(LOOPID_Res),
    IIDINFO(LOOPID_Room),
    IIDINFO(LOOPID_Schema),
    IIDINFO(LOOPID_ScrnMan),
    IIDINFO(LOOPID_SimFinish),
    IIDINFO(LOOPID_SimTime),
    IIDINFO(LOOPID_Sound),
    IIDINFO(LOOPID_Test),
    IIDINFO(LOOPID_UI),
    IIDINFO(LOOPID_Wr),
    IIDINFO(LOOPMODE_Automap),
    IIDINFO(LOOPMODE_DarkPanel),
    IIDINFO(LOOPMODE_Debrief),
    IIDINFO(LOOPMODE_EndGame),
    IIDINFO(LOOPMODE_LevelTrans),
    IIDINFO(LOOPMODE_MetaGame),
    IIDINFO(LOOPMODE_Mission),
    IIDINFO(LOOPMODE_Movie),
    IIDINFO(LOOPMODE_StaticImagePanel),
    IIDINFO(SCRNMAN_PRESERVE_DDRAW),
    IIDINFO(SIM_Loot),
    IIDINFO(SIMID_MediaPropagator),
    IIDINFO(UUID_AIApp),
    IIDINFO(UUID_Dark),
    IIDINFO(UUID_Dispatch),
    IIDINFO(UUID_InputLib),
    IIDINFO(UUID_Res),
};
static const int IIDInfoCount = (sizeof(IIDInfo)/sizeof(IIDInfo[0]));

// ----

/*
Aggregated interfaces are:

    IID_IPropertyManager
    IID_IAggregate
    IID_IAIAppServices
    IID_IAIManager
    IID_IAINetManager
    IID_IAINetServices
    IID_IApplication
    IID_ICampaign
    IID_ICDPlayer
    IID_IContainSys
    IID_IDamageModel
    IID_IDisplayDevice
    IID_IDonorCache
    IID_IDynTexture
    IID_IEditTools
    IID_IFrameAnimationConfigProperty
    IID_IGameShell
    IID_IGameStrings
    IID_IGameTools
    IID_IInputBinder
    IID_IInputDevices
    IID_IInventory
    IID_IKeySys
    IID_ILinkManager
    IID_ILinkManagerInternal
    IID_ILoop
    IID_ILoopManager
    IID_IMoviePlayer1
    IID_INet
    IID_INetAppServices
    IID_INetManager
    IID_INetStats
    IID_IObjectNetworking
    IID_IObjectSystem
    IID_IObjEditors
    IID_IObjIDManager
    IID_IPropagation
    IID_IQuestData
    IID_IReactions
    IID_IScriptMan
    IID_IScriptNet
    IID_ISharedCache
    IID_ISimManager
    IID_IStimSensors
    IID_IStimSources
    IID_IStimulator
    IID_IStimuli
    IID_IStructDescTools
    IID_ITraitManager
    IID_IVoiceOverSys
    IID_IWinApp
    IID_IWinDisplayDevice
*/

// ----

#define PRINT_GUID(x) print_guid(#x,x)
void print_guid(const char *name, GUID guid) {
    printf("%s: %08lx-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x\n",
        name, guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
}

// ----

static IUnknown* pAppAggregate;

IUnknown *_AppGetAggregated(REFIID iid)
{
    if (pAppAggregate) {
        IUnknown* pReturn;
        if (IUnknown_QueryInterface(pAppAggregate, iid, (void**)(&pReturn)) == 0)
            return pReturn;
    }
    return NULL;
}

#define AppGetObj(INTERFACE)     ((INTERFACE *)(_AppGetAggregated(IID_TO_REFIID( IID_ ## INTERFACE ))))

// ----

#include "ISndMixer.h"

static ISndMixer* pSndMixer;

ISndSample* CreateSineWaveSample(ISndMixer* pMixer)
{
    ISndSample* pSample;
    sSndAttribs attribs;

    attribs.dataType = kSndDataPCM;
    attribs.sampleRate = 22050;
    attribs.bitsPerSample = 16;
    attribs.nChannels = 1;
    int totalSamples = (1*attribs.sampleRate);
    int bytesPerSample = (attribs.nChannels*attribs.bitsPerSample/8);
    int totalBytes = (totalSamples*bytesPerSample);
    attribs.bytesPerBlock = totalBytes;
    attribs.samplesPerBlock = totalSamples;
    attribs.numSamples = totalSamples;

    static int16_t sine[16] = {
        0, 12540, 23170, 30274, 32767, 30274, 23170, 12540,
        0, -12540, -23170, -30274, -32767, -30274, -23170, -12540,
    };
    static int16_t samples[22050];
    static int initialized = 0;
    if (! initialized) {
        initialized = 1;
        for (int i=0; i<22050; ++i) {
            samples[i] = sine[i%16];
        }
    }

    pSample = ISndMixer_CreateRawSample(pMixer, kSndSampleNormal,
        (void*)&samples, sizeof(samples), attribs.numSamples, &attribs );
    // pSample = ISndMixer_CreateRawSample(pMixer, kSndSampleStream, NULL,
    //                                     finalDataLen, totalSamples, &attribs );
    return pSample;
}

void explore_sndmixer(void)
{
    g_pfnMPrintf("Delving into ISndMixer...!\n");

    DWORD offset_ppSndMixer = 0x16e07a0UL; // Dromed ND 1.27
    // DWORD offset_ppSndMixer = 0x5cdd30UL; // Thief2 ND 1.27
    DWORD baseAddress = (DWORD)GetModuleHandleA(0);
    ISndMixer** ppSndMixer = (ISndMixer**)(offset_ppSndMixer+baseAddress);
    pSndMixer = *ppSndMixer;
    if (! pSndMixer) {
        g_pfnMPrintf("pSndMixer is NULL!\n");
        return;
    }
    g_pfnMPrintf("pSndMixer is %p\n", pSndMixer);

    int32_t volume = ISndMixer_GetMasterVolume(pSndMixer);
    printf("Master volume is 0x%08x\n", volume);
    // STDMETHOD_(int32,   SetMasterVolume)(THIS_  int32 vol) PURE;
    // STDMETHOD_(int32,   GetMasterVolume)(THIS) PURE;

    ISndSample* pSample = CreateSineWaveSample(pSndMixer);
    if (pSample) {
        printf("Created sample...\n");
        printf("  volume: %d\n", ISndSample_GetVolume(pSample));
        printf("  pan: %d\n", ISndSample_GetPan(pSample));
        printf("  frequency: %u\n", ISndSample_GetFrequency(pSample));
        printf("  group: %d\n", ISndSample_GetGroup(pSample));
        ISndSample_Play(pSample);
        ISndSample_Fade(pSample, kSndFadeVolume, kSndMinVolume, 1000, kSndFadeStop);
    } else {
        printf("Sample was not created :(\n");
    }
}

// ----

#include "IApplication.h"

void explore_guids(void)
{
    g_pfnMPrintf("Delving...!\n");

    DWORD offset_pAppAggregate = 0x16a4314UL; // Dromed ND 1.27
    // DWORD offset_pAppAggregate = 0x1928ecUL; // Thief2 ND 1.27
    DWORD baseAddress = (DWORD)GetModuleHandleA(0);
    IUnknown** ppAppAggregate = (IUnknown**)(offset_pAppAggregate+baseAddress);
    pAppAggregate = *ppAppAggregate;
    if (! pAppAggregate) {
        g_pfnMPrintf("pAppAggregate is NULL!\n");
        return;
    }
    g_pfnMPrintf("pAppAggregate is %p\n", pAppAggregate);

#if 0
    // Query for each interface in turn

    for (int i=0; i<IIDInfoCount; ++i) {
        IIDINFO info = IIDInfo[i];
        IUnknown* iface = _AppGetAggregated(info.refiid);
        if (iface) {
            printf("%s: ok\n", info.name);
            IUnknown_Release(iface);
        } else {
            printf("%s: not aggregated\n", info.name);
        }
    }
#endif

    IApplication* pApplication = AppGetObj(IApplication);
    if (pApplication) {
        // Unimplemented call!
        //IApplication_MessageBox(pApplication, "Hello world!", "Injection", 0);

        // This one works:
        const char *title = IApplication_GetCaption(pApplication);
        printf("Application title was: %s\n", title);

        // Unimplemented call!
        // IApplication_SetCaption(pApplication, "Benny lives!! Hahahahaaa!!");
    } else {
        printf("pApplication was NULL\n");
    }
}
