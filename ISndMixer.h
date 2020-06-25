F_DECLARE_INTERFACE(ISndMixer);
F_DECLARE_INTERFACE(ISndSample);

typedef enum eSndError {
    kSndUnknownError = -1,
    kSndOk,
    kSndCantInit,
    kSndInitAlready,
    kSndNoFreeChannels,
    kSndNoMemory,
    kSndInvalidData,
    kSndDeviceAlready,
    kSndCantCreateDevice,
    kSndCantSetupDevice,
    kSndBadGroup,
    kSndOnly8Bit,
    kUnknownFormat,
    kSnd3DInitFailure,
} eSndError;

typedef enum eSndState {
    kSndStateCreated,
    kSndStateInited,
    kSndStatePlaying,
    kSndStateStopped,
    kSndStateDestroyed,
} eSndState;

typedef enum eSndStateFlags {
    kSndFlagPaused = (1 << 0),
    kSndFlagMuted = (1 << 1),
    kSndFlagLooped = (1 << 2),
    kSndFlagStream = (1 << 3),
    kSndFlagAudible = (1 << 4),
    kSndFlagHWBuffer = (1 << 5),
    kSndFlagFadeStop = (1 << 8),
    kSndFlagPreempted = (1 << 9),
    kSndFlagEndOfData = (1 << 10),
    kSndFlagNone = 0,
} eSndStateFlags;

typedef uint32_t eSndFlagSet;

typedef enum eSndFadeFlags {
    kSndFadeNone,
    kSndFadeStop,
    kSndFadeReverse,
    kSndFadeCallback,
} eSndFadeFlags;

typedef enum eSndSampleCreateFlags {
    kSndSampleInternal = 1,
    kSndSampleNormal = 2,
    kSndSampleStream = 4,
    kSndSampleHardware = 8,
} eSndSampleCreateFlags;

typedef uint32_t eSndSampleCreateFlagSet;

typedef enum eSndFormat {
    kSndVocFile,
    kSndWaveFile,
    kSndLgFile,
    kSndPcmFile,
    kSndNoFile,
} eSndFormat;

typedef enum eSndFaders {
    kSndFadeVolume,
    kSndFadePan,
    kSndFadeFrequency,
    kSndNumFaders,
} eSndFaders;

typedef enum eSndSquelchMode {
    kSndSquelchStop,
    kSndSquelchMute,
} eSndSquelchMode;

typedef enum eSndDataType {
    kSndDataPCM,
    kSndDataIMAADPCM,
} eSndDataType;

typedef enum _eSndTraceEvent {
    kSndSampleStarted,
    kSndSampleStopped,
    kSndSamplePaused,
    kSndSampleResumed,
    kSndSampleDestroyed,
    kSndSampleMuted,
    kSndSampleCreated,
    kSndMixerDestroyed,
    kSndMixerUpdateStart,
    kSndMixerUpdateEnd,
    kSndThreadUpdateStart,
    kSndThreadUpdateEnd,
    kSndBufferAllocate,
    kSndBufferFree,
} eSndTraceEvent;

typedef enum {
    kSnd3DMethodNone = 0,
    kSnd3DMethodPanVol = 1,
    kSnd3DMethodSoftware = 2,
    kSnd3DMethodHardware = 4,
} eSnd3DMethod;

typedef enum {
    kSnd3DModeNone,
    kSnd3DModeNormal,
    kSnd3DModeHeadRelative,
} eSnd3DMode;

typedef struct sSndAttribs {
    eSndDataType dataType;
    int32_t sampleRate;
    int32_t bitsPerSample;
    int32_t nChannels;
    int32_t bytesPerBlock;
    int32_t samplesPerBlock;
    uint32_t numSamples;
} sSndAttribs;

typedef struct sSndSetup {
    void* hwnd;
} sSndSetup, *pSndSetup;

typedef struct sSndMixerCaps {
    int32_t maxVolume;
    int32_t minVolume;
    int32_t panLeft;
    int32_t panRight;
    int32_t maxSampleRate;
    int32_t minSampleRate;
} sSndMixerCaps;

typedef struct sSndVector {
    float x;
    float y;
    float z;
} sSndVector;

typedef struct sSndEnvironment {
    float dopplerFactor;
    float distanceFactor;
    float rolloffFactor;
} sSndEnvironment;

typedef enum eReverbInitResult
{
    kREVERB_InitFail,
    kREVERB_InitOK_HW,
    kREVERB_InitOK_SW,
} eReverbInitResult;

#define kREVERB_Generic          0
#define kREVERB_PaddedCell       1
#define kREVERB_Room             2
#define kREVERB_Bathroom         3
#define kREVERB_LivingRoom       4
#define kREVERB_StoneRoom        5
#define kREVERB_Auditorium       6
#define kREVERB_ConcertHall      7
#define kREVERB_Cave             8
#define kREVERB_Arena            9
#define kREVERB_Hangar           10
#define kREVERB_CarpetedHallway  11
#define kREVERB_Hallway          12
#define kREVERB_StoneCorridor    13
#define kREVERB_Alley            14
#define kREVERB_Forest           15
#define kREVERB_City             16
#define kREVERB_Mountains        17
#define kREVERB_Quarry           18
#define kREVERB_Plain            19
#define kREVERB_ParkingLot       20
#define kREVERB_SewerPipe        21
#define kREVERB_UnderWater       22
#define kREVERB_Drugged          23
#define kREVERB_Dizzy            24
#define kREVERB_Psychotic        25
#define kREVERB_COUNT            26

#define kREVERB_FlagType         (1 << 0)
#define kREVERB_FlagLevel        (1 << 1)
#define kREVERB_FlagDecay        (1 << 2)
#define kREVERB_FlagDamping      (1 << 3)

typedef struct ReverbSettings
{
    uint32_t flags;
    int32_t type;
    float level;
    float decay;
    float damping;
} ReverbSettings;

#define kSndMinVolume -10000
#define kSndMaxVolume -1

#define kSndPanLeft     -10000
#define kSndPanCenter   0
#define kSndPanRight    10000

#define kSndMinFrequency 100
#define kSndMaxFrequency 100000

#define kSndNumGroups   16

#define kSndAnyGroup    (~0)

#define kSndMasterGroup 65536

#define kSndMinDoppler 0.0
#define kSndMaxDoppler 10.0

#define kSndMinRolloff 0.0
#define kSndMaxRolloff 10.0

typedef uint8_t* SndSampleBuffer;

typedef ISndSample* (*SndMixerCallback)(ISndMixer*, ISndSample*, void*);
typedef _Bool (*SndPriorityCallback)(ISndMixer*, ISndSample*, void*);
typedef void (*SndSampleCallback)(ISndSample*);
typedef void (*SndEndCallback)(ISndSample*, void*);
typedef void (*SndFreeChannelCallback)(ISndMixer*, void*);
typedef void (*SndFillCallback)(ISndSample*, void*, uint32_t);
typedef void* (*SndLoadFunction)(void* pCBData, void* pDst, uint32_t);
typedef void (*SndTraceCallback)(ISndSample*, eSndTraceEvent);

#undef INTERFACE
#define INTERFACE ISndMixer

DECLARE_INTERFACE_(ISndMixer, IUnknown)
{
    // Comtools macro to declare IUnknown methods
    DECLARE_UNKNOWN_PURE();

    // call this bad boy to create a mixer
    STDMETHOD_(eSndError, Init)(THIS_ sSndSetup *setup, uint32_t numChannels, sSndAttribs *attr) PURE;

    // how to create a new sample to be played.  flags determines what kind of sample it will be
    STDMETHOD_(ISndSample *, CreateSampleFromRez)(THIS_ eSndSampleCreateFlagSet flags, void *data, uint32_t len) PURE;

    STDMETHOD_(ISndSample *, CreateRawSample)(THIS_ eSndSampleCreateFlagSet flags, void *dat, uint32_t len,
                                             uint32_t nsamps, sSndAttribs *attribs ) PURE;

    STDMETHOD_(uint32_t,  FreeChannelCount)(THIS) PURE;

    // some callbacks.  This might get replaced with more elegant designed things
    STDMETHOD_(void,     RegisterPriorityCallback)(THIS_ SndPriorityCallback func, void *pCBData) PURE;

    // a general purpose interator for sound of a certain type
    STDMETHOD_(void,        DoForAllSamples)(THIS_ SndMixerCallback func, void *pCBData) PURE;
    STDMETHOD_(void,        DoForGroupSamples)(THIS_ uint32_t group, SndMixerCallback func, void *pCBData) PURE;

    // this must get called as ofen as the app needs to have everything run smoothly...
    STDMETHOD_(void,        Update)(THIS) PURE;

    STDMETHOD_(int32_t,   SetMasterVolume)(THIS_  int32_t vol) PURE;
    STDMETHOD_(int32_t,   GetMasterVolume)(THIS) PURE;

    STDMETHOD_(int32_t,   SetGroupVolume)(THIS_  uint32_t group, int32_t vol) PURE;
    STDMETHOD_(int32_t,   GetGroupVolume)(THIS_ uint32_t group) PURE;
    STDMETHOD_(void,        FadeGroupVolume)(THIS_ uint32_t group, int32_t vol, int32_t time, eSndFadeFlags flags) PURE;
    STDMETHOD_(void,     RegisterGroupFadeCallback)(THIS_ uint32_t group, SndEndCallback cBack, void *p) PURE;

    STDMETHOD_(void,     StopAllSamples)(THIS) PURE;

    STDMETHOD_(ISndSample *, First)(THIS_ uint32_t group, eSndFlagSet tflags, eSndFlagSet fflags) PURE;
    STDMETHOD_(ISndSample *, Next)(THIS) PURE;

    STDMETHOD_(void,     Pause)(THIS) PURE;
    STDMETHOD_(void,     Resume)(THIS) PURE;
    STDMETHOD_(uint32_t,   SetTimeout)(THIS_ uint32_t mSecs ) PURE;
    STDMETHOD_(void,     RegisterFreeChannelCallback)(THIS_ SndFreeChannelCallback func, void *pCBData) PURE;
    STDMETHOD_(void,     RegisterTraceCallback)(THIS_ SndTraceCallback f) PURE;
    STDMETHOD_(void,    GetAttribs)(THIS_ sSndAttribs *pAttribs) PURE;

    STDMETHOD_(void,     Set3DPosition)(THIS_ sSndVector *pPosition) PURE;
    STDMETHOD_(void,     Get3DPosition)(THIS_ sSndVector *pPosition) PURE;
    STDMETHOD_(void,     Set3DOrientation)(THIS_ sSndVector *pFront, sSndVector *pTop) PURE;
    STDMETHOD_(void,     Get3DOrientation)(THIS_ sSndVector *pFront, sSndVector *pTop) PURE;
    STDMETHOD_(void,     Set3DVelocity)(THIS_ sSndVector *pVel) PURE;
    STDMETHOD_(void,     Get3DVelocity)(THIS_ sSndVector *pVel) PURE;
    STDMETHOD_(void,     Set3DEnvironment)(THIS_ sSndEnvironment *pParams) PURE;
    STDMETHOD_(void,     Get3DEnvironment)(THIS_ sSndEnvironment *pParams) PURE;
    STDMETHOD_(void,     Set3DMethod)(THIS_ eSnd3DMethod method) PURE;
    STDMETHOD_(void,     Get3DMethodCapabilities)(THIS_ uint32_t *pMethods) PURE;
    STDMETHOD_(int32_t,    Get3DDistanceVolume)(THIS_ float dist) PURE;
    STDMETHOD_(float,    Get3DDistanceFromVolume)(THIS_ int32_t vol) PURE;
    STDMETHOD_(int32_t,    Get3DPositionVolume)(THIS_ sSndVector *pSrcPos) PURE;
    STDMETHOD_(void,     Get3DPositionPanVolume)(THIS_ sSndVector *pSrcPos, int32_t *pPan, int32_t *pVol) PURE;
    STDMETHOD_(void,     Set3DDeferMode)(THIS_ _Bool deferOn) PURE;
    STDMETHOD_(void,       FreeHWChannelCount)(THIS_ int32_t *pHWChans, int32_t *p3DHWChans) PURE;
    STDMETHOD_(int32_t,    Init3DReverb)(THIS) PURE;
    STDMETHOD_(void,     Shutdown3DReverb)(THIS) PURE;
    STDMETHOD_(_Bool,     Have3DReverb)(THIS) PURE;
    STDMETHOD_(_Bool,     CanDo3DReverb)(THIS) PURE;
    STDMETHOD_(_Bool,     Set3DReverbSettings)(THIS_ ReverbSettings *pReverbSettings) PURE;
    STDMETHOD_(_Bool,     Get3DReverbSettings)(THIS_ ReverbSettings *pReverbSettings) PURE;
    STDMETHOD_(_Bool,     Have3DOcclusion)(THIS) PURE;
    STDMETHOD_(int32_t,    Kludge)(THIS_ int kludgeSelector, void *pKludgeStruct, int32_t sizeKludgeStruct ) PURE;
};

#define ISndMixer_Init(p, a, b, c)                      COMCall3(p, Init, a, b, c)
#define ISndMixer_CreateSampleFromRez(p,a,b,c)     COMCall3(p, CreateSampleFromRez, a, b, c)
#define ISndMixer_CreateRawSample(p,a,b,c,d,e)      COMCall5(p, CreateRawSample, a,b,c,d,e)
#define ISndMixer_FreeChannelCount(p)                   COMCall0(p, FreeChannelCount)
#define ISndMixer_RegisterPriorityCallback(p,a,b)  COMCall2(p, RegisterPriorityCallback, a, b)
#define ISndMixer_DoForAllSamples(p, a, b)          COMCall2(p, DoForAllSamples, a, b)
#define ISndMixer_DoForGroupSamples(p,a,b,c)       COMCall3(p, DoForGroupSamples, a, b, c)
#define ISndMixer_Update(p)                             COMCall0(p, Update)
#define ISndMixer_SetMasterVolume(p, a)             COMCall1(p, SetMasterVolume, a)
#define ISndMixer_GetMasterVolume(p)                    COMCall0(p, GetMasterVolume)
#define ISndMixer_SetGroupVolume(p, a, b)               COMCall2(p, SetGroupVolume, a, b)
#define ISndMixer_GetGroupVolume(p, a)                  COMCall1(p, GetGroupVolume, a)
#define ISndMixer_FadeGroupVolume(p,a,b,c,d)       COMCall4(p, FadeGroupVolume,a,b,c,d)
#define ISndMixer_RegisterGroupFadeCallback(p,g,f,a) COMCall3(p, RegisterFadeCallback, g, f, a)
//#define ISndMixer_GroupFadeActive(p,a)             COMCall1(p, GroupFadeActive, a)
#define ISndMixer_StopAllSamples(p)                     COMCall0(p, StopAllSamples)
#define ISndMixer_First(p,a)                                COMCall1(p, First, a)
#define ISndMixer_Next(p,a)                             COMCall1(p, Next, a)
#define ISndMixer_Pause(p)                                  COMCall0(p, Pause)
#define ISndMixer_Resume(p)                             COMCall0(p, Resume)
#define ISndMixer_Release(p)                       COMCall0(p, Release)
#define ISndMixer_SetTimeout(p,a)                       COMCall1(p, SetTimeout, a)
#define ISndMixer_RegisterFreeChannelCallback(p,a,b)  COMCall2(p, RegisterFreeChannelCallback, a, b)
#define ISndMixer_RegisterTraceCallback(p,a)       COMCall1(p, RegisterTraceCallback, a)
#define ISndMixer_GetAttribs(p,a)                  COMCall1(p, GetAttribs, a)

#define ISndMixer_Set3DPosition(p, a)              COMCall1(p, Set3DPosition, a)
#define ISndMixer_Get3DPosition(p, a)              COMCall1(p, Get3DPosition, a)
#define ISndMixer_Set3DOrientation(p, a, b)        COMCall2(p, Set3DOrientation, a, b)
#define ISndMixer_Get3DOrientation(p, a, b)        COMCall2(p, Get3DOrientation, a, b)
#define ISndMixer_Set3DVelocity(p, a)              COMCall1(p, Set3DVelocity, a)
#define ISndMixer_Get3DVelocity(p, a)              COMCall1(p, Get3DVelocity, a)
#define ISndMixer_Set3DEnvironment(p, a)           COMCall1(p, Set3DEnvironment, a)
#define ISndMixer_Get3DEnvironment(p, a)           COMCall1(p, Get3DEnvironment, a)
#define ISndMixer_Set3DMethod(p, a)                COMCall1(p, Set3DMethod, a)
#define ISndMixer_Get3DMethodCapabilities(p, a)    COMCall1(p, Get3DMethodCapabilities, a)
#define ISndMixer_Get3DDistanceVolume(p, a)        COMCall1(p, Get3DDistanceVolume, a)
#define ISndMixer_Get3DDistanceFromVolume(p, a)    COMCall1(p, Get3DDistanceFromVolume, a)
#define ISndMixer_Get3DPositionVolume(p, a)        COMCall1(p, Get3DPositionVolume, a)
#define ISndMixer_Get3DPositionPanVolume(p, a, b, c)     COMCall3(p, Get3DPositionPanVolume, a, b, c)
#define ISndMixer_Set3DDeferMode(p, a)                 COMCall1(p, Set3DDeferMode, a)
#define ISndMixer_FreeHWChannelCount(p, a, b)      COMCall2(p, FreeHWChannelCount, a, b)
#define ISndMixer_Init3DReverb(p)                  COMCall0(p)
#define ISndMixer_Shutdown3DReverb(p)              COMCall0(p)
#define ISndMixer_Have3DReverb(p)                  COMCall0(p)
#define ISndMixer_CanDo3DReverb(p)                 COMCall0(p)
#define ISndMixer_Set3DReverbSettings(p, a)        COMCall1(p, Set3DReverbSettings, a)
#define ISndMixer_Get3DReverbSettings(p, a)        COMCall1(p, Get3DReverbSettings, a)
#define ISndMixer_Have3DOcclusion(p)               COMCall0(p)
#define ISndMixer_Kludge(p, a, b, c)               COMCall3(p, Kludge, a, b, c)

#undef INTERFACE
#define INTERFACE ISndSample

DECLARE_INTERFACE_(ISndSample, IUnknown)
{
    // Comtools macro to declare IUnknown methods
    DECLARE_UNKNOWN_PURE();

    STDMETHOD_(void,    Play)(THIS) PURE;
    STDMETHOD_(void,    Pause)(THIS) PURE;
    STDMETHOD_(void,    Resume)(THIS) PURE;
    STDMETHOD_(void,    Stop)(THIS) PURE;
    STDMETHOD_(void,    Loop)(THIS) PURE;
    STDMETHOD_(void,    Mute)(THIS) PURE;
    STDMETHOD_(void,    UnMute)(THIS) PURE;
    STDMETHOD_(_Bool,  ResyncNeeded)(THIS_ uint32_t *pStartPos) PURE;
    STDMETHOD_(void,    Preempt)(THIS) PURE;

    STDMETHOD_(void,    SetVolume)(THIS_ int32_t vol) PURE;
    STDMETHOD_(void,    SetPan)(THIS_ int32_t pan) PURE;
    STDMETHOD_(void,    SetFrequency)(THIS_ uint32_t freq) PURE;
    STDMETHOD_(void,    SetData)(THIS_ int32_t data) PURE;
    STDMETHOD_(void,    SetPriority)(THIS_ int32_t pri) PURE;
    STDMETHOD_(void,  SetSuperInfo)(THIS_ void *pInfo) PURE;
    STDMETHOD_(void,    SetPosition)(THIS_ uint32_t pos) PURE;
    STDMETHOD_(void,    SetGroup)(THIS_ uint32_t group) PURE;

    STDMETHOD_(int32_t,   GetVolume)(THIS) PURE;
    STDMETHOD_(int32_t,   GetPan)(THIS) PURE;
    STDMETHOD_(uint32_t,  GetFrequency)(THIS) PURE;
    STDMETHOD_(int32_t,   GetData)(THIS) PURE;
    STDMETHOD_(int32_t,   GetPriority)(THIS) PURE;
    STDMETHOD_(void *,   GetSuperInfo)(THIS) PURE;
    STDMETHOD_(uint32_t,  GetPosition)(THIS) PURE;
    STDMETHOD_(void,    GetPositions)(THIS_ uint32_t *pW, uint32_t *pP) PURE;
    STDMETHOD_(void,    GetAttribs)(THIS_ sSndAttribs *pAttribs) PURE;
    STDMETHOD_(uint32_t,   GetGroup)(THIS) PURE;

    STDMETHOD_(uint32_t,   GetSerialNumber)(THIS) PURE;

    STDMETHOD_(void,        Fade)(THIS_ eSndFaders t, int32_t vol, int32_t time, eSndFadeFlags flags) PURE;
    STDMETHOD_(_Bool,     FadeActive)(THIS_ eSndFaders t) PURE;

    STDMETHOD_(uint32_t,   AvailToWrite)(THIS) PURE;
    STDMETHOD_(void,     CheckStream)(THIS) PURE;
    STDMETHOD_(void,     GetStatus)(THIS_ eSndState *pState, eSndFlagSet *pFlags) PURE;

    STDMETHOD_(_Bool,     BufferReady)(THIS_ uint32_t len) PURE;
    STDMETHOD_(eSndError, LoadBuffer)(THIS_ uint8_t * data, uint32_t len) PURE;
    STDMETHOD_(eSndError, LoadBufferIndirect)(THIS_ SndLoadFunction funk, void *pFunkData, uint32_t len) PURE;

    STDMETHOD_(void,    SilenceFill)(THIS_ uint32_t nBytes) PURE;
    STDMETHOD_(void,     RegisterFillCallback)(THIS_ SndFillCallback cBack, void *p) PURE;
    STDMETHOD_(void,     RegisterEndCallback)(THIS_ SndEndCallback cBack, void *p) PURE;
    STDMETHOD_(void,     RegisterPreemptCallback)(THIS_ SndEndCallback cBack, void *p) PURE;
    STDMETHOD_(void,     RegisterFadeCallback)(THIS_ eSndFaders t, SndEndCallback cBack, void *p) PURE;
    STDMETHOD_(void,     DumpData)(THIS_ _Bool turnOn ) PURE;  // start dumping data to raw file
    STDMETHOD_(uint32_t,   PlayTimeRemaining)(THIS) PURE;      // return milliseconds of playtime left
    STDMETHOD_(void,     SetName)(THIS_ char *pUserName) PURE;
    STDMETHOD_(char *,   GetName)(THIS) PURE;

    STDMETHOD_(void,     Squelch)(THIS_ int32_t sqLevel, uint32_t sqCount, eSndSquelchMode mode) PURE;

    STDMETHOD_(uint32_t,   TimeToSamples)(THIS_ uint32_t millisecs) PURE;
    STDMETHOD_(uint32_t,   SamplesToTime)(THIS_ uint32_t samples) PURE;

    STDMETHOD_(void,     Set3DPosition)(THIS_ sSndVector *pPosition) PURE;
    STDMETHOD_(void,     Get3DPosition)(THIS_ sSndVector *pPosition) PURE;
    STDMETHOD_(void,     Set3DVelocity)(THIS_ sSndVector *pVelocity) PURE;
    STDMETHOD_(void,     Get3DVelocity)(THIS_ sSndVector *pVelocity) PURE;
    STDMETHOD_(void,     Set3DConeAngles)(THIS_ uint32_t inside, uint32_t outside) PURE;
    STDMETHOD_(void,     Get3DConeAngles)(THIS_ uint32_t *pInside, uint32_t *pOutside) PURE;
    STDMETHOD_(void,     Set3DConeOrientation)(THIS_ sSndVector *pOrient) PURE;
    STDMETHOD_(void,     Get3DConeOrientation)(THIS_ sSndVector *pOrient) PURE;
    STDMETHOD_(void,     Set3DDistanceRange)(THIS_ float dmin, float dmax) PURE;
    STDMETHOD_(void,     Get3DDistanceRange)(THIS_ float *pMin, float *pMax) PURE;
    STDMETHOD_(void,     Set3DMode)(THIS_ eSnd3DMode mode) PURE;
    STDMETHOD_(void,     Get3DMode)(THIS_ eSnd3DMode *pMode) PURE;
    STDMETHOD_(void,     SetAmbientVolume)(THIS_ int32_t vol) PURE;
    STDMETHOD_(int32_t,    GetAmbientVolume)(THIS) PURE;
    STDMETHOD_(void,     Set3DMethod)(THIS_ eSnd3DMethod method) PURE;
    STDMETHOD_(eSnd3DMethod, Get3DMethod)(THIS) PURE;
    STDMETHOD_(void,     Set3DReverbMix)(THIS_ float mix) PURE;
    STDMETHOD_(void,     Set3DOcclusion)(THIS_ int32_t occlusionMillibels) PURE;
    STDMETHOD_(int32_t,    Kludge)(THIS_ int kludgeSelector, void *pKludgeStruct, int32_t sizeKludgeStruct ) PURE;
};

#define ISndSample_Play(p)                      COMCall0(p, Play)
#define  ISndSample_Pause(p)                 COMCall0(p, Pause)
#define  ISndSample_Resume(p)                COMCall0(p, Resume)
#define  ISndSample_Stop(p)                  COMCall0(p, Stop)
#define  ISndSample_Loop(p)                  COMCall0(p, Loop)
#define  ISndSample_Mute(p)                  COMCall0(p, Mute)
#define  ISndSample_UnMute(p)                COMCall0(p, UnMute)
#define  ISndSample_ResyncNeeded(p,a)        COMCall1(p, ResyncNeeded, a)
#define  ISndSample_Preempt(p)               COMCall0(p, Preempt)

#define  ISndSample_SetVolume(p,a)           COMCall1(p, SetVolume,a)
#define  ISndSample_SetPan(p,a)              COMCall1(p, SetPan,a)
#define  ISndSample_SetFrequency(p,a)        COMCall1(p, SetFrequency,a)
#define  ISndSample_SetData(p,a)             COMCall1(p, SetData,a)
#define  ISndSample_SetPriority(p,a)         COMCall1(p, SetPriority,a)
#define  ISndSample_SetSuperInfo(p,a)        COMCall1(p, SetSuperInfo,a)
#define  ISndSample_SetType(p,a)             COMCall1(p, SetType,a)
#define  ISndSample_SetPosition(p,a)         COMCall1(p, SetPosition,a)
#define  ISndSample_SetGroup(p,a)            COMCall1(p, SetGroup,a)

#define  ISndSample_GetVolume(p)             COMCall0(p, GetVolume)
#define  ISndSample_GetPan(p)                COMCall0(p, GetPan)
#define  ISndSample_GetFrequency(p)          COMCall0(p, GetFrequency)
#define  ISndSample_GetData(p)               COMCall0(p, GetData)
#define  ISndSample_GetPriority(p)           COMCall0(p, GetPriority)
#define  ISndSample_GetSuperInfo(p)          COMCall0(p, GetSuperInfo)
#define  ISndSample_GetType(p)               COMCall0(p, GetType)
#define  ISndSample_GetPosition(p)           COMCall0(p, GetPosition)
#define  ISndSample_GetPositions(p,a,b)      COMCall2(p, GetPositions, a, b)
#define  ISndSample_GetAttribs(p,a)          COMCall1(p, GetAttribs, a)
#define  ISndSample_GetGroup(p)              COMCall0(p, GetGroup)

#define  ISndSample_GetSerialNumber(p)       COMCall0(p, GetSerialNumber)

#define  ISndSample_Fade(p,a,b,c,d)          COMCall4(p, Fade,a,b,c,d)
#define  ISndSample_FadeActive(p,a)          COMCall1(p, FadeActive, a)

#define  ISndSample_AvailToWrite(p)          COMCall0(p, AvailToWrite)
#define  ISndSample_CheckStream(p)           COMCall0(p, CheckStream)
#define  ISndSample_GetStatus(p,a,b)         COMCall0(p, GetStatus,a,b)

#define  ISndSample_BufferReady(p,a)         COMCall1(p, BufferReady,a)
#define  ISndSample_LoadBuffer(p,a,b)        COMCall2(p, LoadBuffer,a,b)
#define  ISndSample_LoadBufferIndirect(p,a,b,c) COMCall3(p, LoadBufferIndirect,a,b,c)

#define  ISndSample_SilenceFill(p, nBytes)   COMCall1(p, SilenceFill, nBytes)
#define  ISndSample_RegisterFillCallback(p,f,a)    COMCall2(p, RegisterFillCallback, f, a)
#define  ISndSample_RegisterEndCallback(p,f,a)     COMCall2(p, RegisterEndCallback, f, a)
#define  ISndSample_RegisterPreemptCallback(p,f,a) COMCall2(p, RegisterEndCallback, f, a)
#define  ISndSample_RegisterFadeCallback(p,g,f,a)  COMCall3(p, RegisterFadeCallback, g, f, a)

#define  ISndSample_Release(p)               COMCall0(p, Release)
#define  ISndSample_DumpData(p,a)            COMCall1(p, DumpData, a)
#define  ISndSample_PlayTimeRemaining(p)     COMCall0(p, PlayTimeRemaining)

#define  ISndSample_SetName(p,a)             COMCall1(p, SetName, a)
#define  ISndSample_GetName(p)               COMCall0(p, GetName)

#define  ISndSample_Squelch(p,a,b,c)         COMCall3(p, Squelch, a, b, c)

#define  ISndSample_TimeToSamples(p,a)       COMCall1(p, TimeToSamples, a)
#define  ISndSample_SamplesToTime(p,a)       COMCall1(p, SamplesToTime, a)

#define ISndSample_Set3DPosition(p, a)       COMCall1(p, Set3DPosition, a)
#define ISndSample_Get3DPosition(p, a)       COMCall1(p, Get3DPosition, a)
#define ISndSample_Set3DVelocity(p, a)       COMCall1(p, Set3DVelocity, a)
#define ISndSample_Get3DVelocity(p, a)       COMCall1(p, Get3DVelocity, a)
#define ISndSample_Set3DConeAngles(p, a, b)  COMCall2(p, Set3DConeAngles, a, b)
#define ISndSample_Get3DConeAngles(p, a, b)  COMCall2(p, Get3DConeAngles, a, b)
#define ISndSample_Set3DConeOrientation(p,a) COMCall1(p, Set3DConeOrientation, a)
#define ISndSample_Get3DConeOrientation(p,a) COMCall1(p, Get3DConeOrientation, a)
#define ISndSample_Set3DDistanceRange(p,a,b) COMCall2(p, Set3DDistanceRange, a, b)
#define ISndSample_Get3DDistanceRange(p,a,b) COMCall2(p, Get3DDistanceRange, a, b)
#define ISndSample_Set3DMode(p, a)           COMCall1(p, Set3DMode, a)
#define ISndSample_Get3DMode(p, a)           COMCall1(p, Get3DMode, a)
#define ISndSample_SetAmbientVolume(p, a)    COMCall1(p, Set3DAmbientVolume, a)
#define ISndSample_GetAmbientVolume(p, a)    COMCall0(p, Get3DAmbientVolume)
#define ISndSample_Set3DMethod(p, a)         COMCall1(p, Set3DMethod, a)
#define ISndSample_Get3DMethod(p)            COMCall0(p, Get3DMethod)
#define ISndSample_Set3DReverbMix(p, a)      COMCall1(p, Set3DReverbMix, a)
#define ISndMixer_Kludge(p, a, b, c)               COMCall3(p, Kludge, a, b, c)
