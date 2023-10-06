//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Interfaces between the client.dll and engine
//
//===========================================================================//

#ifndef CDLL_INT_H
#define CDLL_INT_H
#ifdef _WIN32
#pragma once
#endif


#include "basetypes.h"
#include "interface.h"
#include "const.h"
#include "checksum_crc.h"
#include "datamap.h"
#include "bitbuf.h"
#include "ButtonCode.h"
#include "modes.h"

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------
class ClientClass;
struct model_t;
class CSentence;
struct vrect_t;
struct cmodel_t;
class IMaterial;
class CAudioSource;
class CMeasureSection;
class SurfInfo;
class ISpatialQuery;
struct cache_user_t;
class IMaterialSystem;
class VMatrix;
struct ScreenFade_t;
struct ScreenShake_t;
class CViewSetup;
class CEngineSprite;
class CGlobalVarsBase;
class CPhysCollide;
class CSaveRestoreData;
class INetChannelInfo;
struct datamap_t;
struct typedescription_t;
class CStandardRecvProxies;
struct client_textmessage_t;
class IAchievementMgr;
class CGamestatsData;
class KeyValues;
class IFileList;
class CRenamedRecvTableInfo;
class CMouthInfo;
class IConVar;

//-----------------------------------------------------------------------------
// Purpose: This data structure is filled in by the engine when the client .dll requests information about
//  other players that the engine knows about
//-----------------------------------------------------------------------------

// Engine player info, no game related infos here
// If you change this, change the two byteswap defintions: 
// cdll_client_int.cpp and cdll_engine_int.cpp
typedef struct player_info_s
{
	DECLARE_BYTESWAP_DATADESC();
	// scoreboard information
	char			name[MAX_PLAYER_NAME_LENGTH];
	// local server user ID, unique while server is running
	int				userID;
	// global unique player identifer
	char			guid[SIGNED_GUID_LEN + 1];
	// friends identification number
	uint32_t			friendsID;
	// friends name
	char			friendsName[MAX_PLAYER_NAME_LENGTH];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;
#if defined( REPLAY_ENABLED )
	// true if player is the Replay proxy
	bool			isreplay;
#endif
	// custom files CRC for this player
	CRC32_t			customFiles[MAX_CUSTOM_FILES];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
} player_info_t;

//-----------------------------------------------------------------------------
// Hearing info
//-----------------------------------------------------------------------------
struct AudioState_t
{
	Vector m_Origin;
	QAngle m_Angles;
	bool m_bIsUnderwater;
};


//-----------------------------------------------------------------------------
// Skybox visibility
//-----------------------------------------------------------------------------
enum SkyboxVisibility_t
{
	SKYBOX_NOT_VISIBLE = 0,
	SKYBOX_3DSKYBOX_VISIBLE,
	SKYBOX_2DSKYBOX_VISIBLE,
};

//-----------------------------------------------------------------------------
// Skybox materials
//-----------------------------------------------------------------------------
struct SkyBoxMaterials_t
{
	// order: "rt", "bk", "lf", "ft", "up", "dn"
	IMaterial* material[6];
};

//-----------------------------------------------------------------------------
// Purpose: The engine reports to the client DLL what stage it's entering so the DLL can latch events
//  and make sure that certain operations only happen during the right stages.
// The value for each stage goes up as you move through the frame so you can check ranges of values
//  and if new stages get added in-between, the range is still valid.
//-----------------------------------------------------------------------------
enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
		// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
// We've received all packets, we can now do interpolation, prediction, etc..
FRAME_NET_UPDATE_END,

// We're about to start rendering the scene
FRAME_RENDER_START,
// We've finished rendering the scene.
FRAME_RENDER_END
};

// Used by RenderView
enum RenderViewInfo_t
{
	RENDERVIEW_UNSPECIFIED = 0,
	RENDERVIEW_DRAWVIEWMODEL = (1 << 0),
	RENDERVIEW_DRAWHUD = (1 << 1),
	RENDERVIEW_SUPPRESSMONITORRENDERING = (1 << 2),
};

//-----------------------------------------------------------------------------
// Lightcache entry handle
//-----------------------------------------------------------------------------
DECLARE_POINTER_HANDLE(LightCacheHandle_t);


//-----------------------------------------------------------------------------
// Occlusion parameters
//-----------------------------------------------------------------------------
struct OcclusionParams_t
{
	float	m_flMaxOccludeeArea;
	float	m_flMinOccluderArea;
};


//-----------------------------------------------------------------------------
// Just an interface version name for the random number interface
// See vstdlib/random.h for the interface definition
// NOTE: If you change this, also change VENGINE_SERVER_RANDOM_INTERFACE_VERSION in eiface.h
//-----------------------------------------------------------------------------
#define VENGINE_CLIENT_RANDOM_INTERFACE_VERSION	"VEngineRandom001"

// change this when the new version is incompatable with the old
#define VENGINE_CLIENT_INTERFACE_VERSION		"VEngineClient014"
#define VENGINE_CLIENT_INTERFACE_VERSION_13		"VEngineClient013"

class IVEngineClient013
{
public:
	virtual int GetIntersectingSurfaces(const model_t* model, const Vector& vCenter, const float radius, const bool bOnlyVisibleSurfaces, SurfInfo* pInfos, const int nMaxInfos) = 0;
	virtual Vector GetLightForPoint(const Vector& pos, bool bClamp) = 0;
	virtual IMaterial* TraceLineMaterialAndLighting(const Vector& start, const Vector& end, Vector& diffuseLightColor, Vector& baseColor) = 0;
	virtual const char* ParseFile(const char* data, char* token, int maxlen) = 0;
	virtual bool CopyLocalFile(const char* source, const char* destination) = 0;
	virtual void GetScreenSize(int& width, int& height) = 0;
	virtual void ServerCmd(const char* szCmdString, bool bReliable = true) = 0;
	virtual void ClientCmd(const char* szCmdString) = 0;
	virtual bool GetPlayerInfo(int ent_num, player_info_t* pinfo) = 0;
	virtual int GetPlayerForUserID(int userID) = 0;
	virtual client_textmessage_t* TextMessageGet(const char* pName) = 0;
	virtual bool Con_IsVisible(void) = 0;
	virtual int GetLocalPlayer(void) = 0;
	virtual const model_t* LoadModel(const char* pName, bool bProp = false) = 0;
	virtual float Time(void) = 0;
	virtual float GetLastTimeStamp(void) = 0;
	virtual CSentence* GetSentence(CAudioSource* pAudioSource) = 0;
	virtual float GetSentenceLength(CAudioSource* pAudioSource) = 0;
	virtual bool IsStreaming(CAudioSource* pAudioSource) const = 0;
	virtual void GetViewAngles(QAngle& va) = 0;
	inline Vector GetViewAngles() { QAngle out = {}; GetViewAngles(out); return out; }
	virtual void SetViewAngles(QAngle& va) = 0;
	virtual int GetMaxClients(void) = 0;
	virtual	const char* Key_LookupBinding(const char* pBinding) = 0;
	virtual const char* Key_BindingForKey(ButtonCode_t code) = 0;
	virtual void StartKeyTrapMode(void) = 0;
	virtual bool CheckDoneKeyTrapping(ButtonCode_t& code) = 0;
	virtual bool IsInGame(void) = 0;
	virtual bool IsConnected(void) = 0;
	virtual bool IsDrawingLoadingImage(void) = 0;
	virtual void Con_NPrintf(int pos, const char* fmt, ...) = 0;
	virtual void Con_NXPrintf(const struct con_nprint_s* info, const char* fmt, ...) = 0;
	virtual int IsBoxVisible(const Vector& mins, const Vector& maxs) = 0;
	virtual int IsBoxInViewCluster(const Vector& mins, const Vector& maxs) = 0;
	virtual bool CullBox(const Vector& mins, const Vector& maxs) = 0;
	virtual void Sound_ExtraUpdate(void) = 0;
	virtual const char* GetGameDirectory(void) = 0;
	virtual const VMatrix& WorldToScreenMatrix() = 0;
	virtual const VMatrix& WorldToViewMatrix() = 0;
	virtual int GameLumpVersion(int lumpId) const = 0;
	virtual int GameLumpSize(int lumpId) const = 0;
	virtual bool LoadGameLump(int lumpId, void* pBuffer, int size) = 0;
	virtual int LevelLeafCount() const = 0;
	virtual ISpatialQuery* GetBSPTreeQuery() = 0;
	virtual void LinearToGamma(float* linear, float* gamma) = 0;
	virtual float LightStyleValue(int style) = 0;
	virtual void ComputeDynamicLighting(const Vector& pt, const Vector* pNormal, Vector& color) = 0;
	virtual void GetAmbientLightColor(Vector& color) = 0;
	virtual int GetDXSupportLevel() = 0;
	virtual bool SupportsHDR() = 0;
	virtual void Mat_Stub(IMaterialSystem* pMatSys) = 0;
	virtual void GetChapterName(char* pchBuff, int iMaxLength) = 0;
	virtual char const* GetLevelName(void) = 0;
	virtual int	GetLevelVersion(void) = 0;
	virtual struct IVoiceTweak_s* GetVoiceTweakAPI(void) = 0;
	virtual void EngineStats_BeginFrame(void) = 0;
	virtual void EngineStats_EndFrame(void) = 0;
	virtual void FireEvents() = 0;
	virtual int GetLeavesArea(int* pLeaves, int nLeaves) = 0;
	virtual bool DoesBoxTouchAreaFrustum(const Vector& mins, const Vector& maxs, int iArea) = 0;
	virtual void SetAudioState(const AudioState_t& state) = 0;
	virtual int SentenceGroupPick(int groupIndex, char* name, int nameBufLen) = 0;
	virtual int SentenceGroupPickSequential(int groupIndex, char* name, int nameBufLen, int sentenceIndex, int reset) = 0;
	virtual int SentenceIndexFromName(const char* pSentenceName) = 0;
	virtual const char* SentenceNameFromIndex(int sentenceIndex) = 0;
	virtual int SentenceGroupIndexFromName(const char* pGroupName) = 0;
	virtual const char* SentenceGroupNameFromIndex(int groupIndex) = 0;
	virtual float SentenceLength(int sentenceIndex) = 0;
	virtual void ComputeLighting(const Vector& pt, const Vector* pNormal, bool bClamp, Vector& color, Vector* pBoxColors = NULL) = 0;
	virtual void ActivateOccluder(int nOccluderIndex, bool bActive) = 0;
	virtual bool IsOccluded(const Vector& vecAbsMins, const Vector& vecAbsMaxs) = 0;
	virtual void* SaveAllocMemory(size_t num, size_t size) = 0;
	virtual void SaveFreeMemory(void* pSaveMem) = 0;
	virtual INetChannelInfo* GetNetChannelInfo(void) = 0;
	virtual void DebugDrawPhysCollide(const CPhysCollide* pCollide, IMaterial* pMaterial, matrix3x4_t& transform, const color32& color) = 0;
	virtual void CheckPoint(const char* pName) = 0;
	virtual void DrawPortals() = 0;
	virtual bool IsPlayingDemo(void) = 0;
	virtual bool IsRecordingDemo(void) = 0;
	virtual bool IsPlayingTimeDemo(void) = 0;
	virtual int GetDemoRecordingTick(void) = 0;
	virtual int GetDemoPlaybackTick(void) = 0;
	virtual int GetDemoPlaybackStartTick(void) = 0;
	virtual float GetDemoPlaybackTimeScale(void) = 0;
	virtual int GetDemoPlaybackTotalTicks(void) = 0;
	virtual bool IsPaused(void) = 0;
	virtual bool IsTakingScreenshot(void) = 0;
	virtual bool IsHLTV(void) = 0;
	virtual bool IsLevelMainMenuBackground(void) = 0;
	virtual void GetMainMenuBackgroundName(char* dest, int destlen) = 0;
	virtual void GetVideoModes(int& nCount, vmode_s*& pModes) = 0;
	virtual void SetOcclusionParameters(const OcclusionParams_t& params) = 0;
	virtual void GetUILanguage(char* dest, int destlen) = 0;
	virtual SkyboxVisibility_t IsSkyboxVisibleFromPoint(const Vector& vecPoint) = 0;
	virtual const char* GetMapEntitiesString() = 0;
	virtual bool IsInEditMode(void) = 0;
	virtual float GetScreenAspectRatio() = 0;
	virtual bool REMOVED_SteamRefreshLogin(const char* password, bool isSecure) = 0;
	virtual bool REMOVED_SteamProcessCall(bool& finished) = 0;
	virtual unsigned int GetEngineBuildNumber() = 0;
	virtual const char* GetProductVersionString() = 0;
	virtual void GrabPreColorCorrectedFrame(int x, int y, int width, int height) = 0;
	virtual bool IsHammerRunning() const = 0;
	virtual void ExecuteClientCmd(const char* szCmdString) = 0;
	virtual bool MapHasHDRLighting(void) = 0;
	virtual int	GetAppID() = 0;
	virtual Vector GetLightForPointFast(const Vector& pos, bool bClamp) = 0;
	virtual void ClientCmd_Unrestricted(const char* szCmdString) = 0;
	virtual void SetRestrictServerCommands(bool bRestrict) = 0;
	virtual void SetRestrictClientCommands(bool bRestrict) = 0;
	virtual void SetOverlayBindProxy(int iOverlayID, void* pBindProxy) = 0;
	virtual bool CopyFrameBufferToMaterial(const char* pMaterialName) = 0;
	virtual void ChangeTeam(const char* pTeamName) = 0;
	virtual void ReadConfiguration(const bool readDefault = false) = 0;
	virtual void SetAchievementMgr(IAchievementMgr* pAchievementMgr) = 0;
	virtual IAchievementMgr* GetAchievementMgr() = 0;
	virtual bool MapLoadFailed(void) = 0;
	virtual void SetMapLoadFailed(bool bState) = 0;
	virtual bool IsLowViolence() = 0;
	virtual const char* GetMostRecentSaveGame(void) = 0;
	virtual void SetMostRecentSaveGame(const char* lpszFilename) = 0;
	virtual void StartXboxExitingProcess() = 0;
	virtual bool IsSaveInProgress() = 0;
	virtual unsigned int OnStorageDeviceAttached(void) = 0;
	virtual void OnStorageDeviceDetached(void) = 0;
	virtual void ResetDemoInterpolation(void) = 0;
	virtual void SetGamestatsData(CGamestatsData* pGamestatsData) = 0;
	virtual CGamestatsData* GetGamestatsData() = 0;
	virtual void ServerCmdKeyValues(KeyValues* pKeyValues) = 0;
	virtual bool IsSkippingPlayback(void) = 0;
	virtual bool IsLoadingDemo(void) = 0;
	virtual bool IsPlayingDemoALocallyRecordedDemo() = 0;
	virtual	const char* Key_LookupBindingExact(const char* pBinding) = 0;
	virtual void AddPhonemeFile(const char* pszPhonemeFile) = 0;
	virtual float GetPausedExpireTime(void) = 0;
	virtual bool StartDemoRecording(const char* pszFilename, const char* pszFolder = NULL) = 0;
	virtual void StopDemoRecording(void) = 0;
	virtual void TakeScreenshot(const char* pszFilename, const char* pszFolder = NULL) = 0;
};

VERSION_INTERFACE(EngineClient, IVEngineClient013*, "engine.dll", "VEngineClient013");

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "utlvector.h"

// from xboxstubs.h - thanks again spook :3
typedef struct _XUSER_DATA
{
	BYTE type;

	union
	{
		int nData;
		__int64 i64Data;
		double dblData;
		struct
		{
			unsigned int cbData;
			char* pwszData;
		} string;
		float fData;
		struct
		{
			unsigned int cbData;
			char* pbData;
		} binary;
	};
} XUSER_DATA, * PXUSER_DATA;

typedef struct _XUSER_PROPERTY
{
	DWORD dwPropertyId;
	XUSER_DATA value;
} XUSER_PROPERTY, * PXUSER_PROPERTY;

typedef struct _XUSER_CONTEXT
{
	DWORD dwContextId;
	DWORD dwValue;
} XUSER_CONTEXT, * PXUSER_CONTEXT;

class IBaseClientDLL
{
public:
	virtual int Init(CreateInterfaceFn appSystemFactory, CreateInterfaceFn physicsFactory, CGlobalVarsBase* pGlobals) = 0;
	virtual void PostInit() = 0;
	virtual void Shutdown(void) = 0;
	virtual bool ReplayInit(CreateInterfaceFn replayFactory) = 0;
	virtual bool ReplayPostInit() = 0;
	virtual void LevelInitPreEntity(char const* pMapName) = 0;
	virtual void LevelInitPostEntity() = 0;
	virtual void LevelShutdown(void) = 0;
	virtual ClientClass* GetAllClasses(void) = 0;
	virtual int HudVidInit(void) = 0;
	virtual void HudProcessInput(bool bActive) = 0;
	virtual void HudUpdate(bool bActive) = 0;
	virtual void HudReset(void) = 0;
	virtual void HudText(const char* message) = 0;
	virtual void IN_ActivateMouse(void) = 0;
	virtual void IN_DeactivateMouse(void) = 0;
	virtual void IN_Accumulate(void) = 0;
	virtual void IN_ClearStates(void) = 0;
	virtual bool IN_IsKeyDown(const char* name, bool& isdown) = 0;
	virtual void IN_OnMouseWheeled(int nDelta) = 0;
	virtual int IN_KeyEvent(int eventcode, ButtonCode_t keynum, const char* pszCurrentBinding) = 0;
	virtual void CreateMove(int sequence_number, float input_sample_frametime, bool active) = 0;
	virtual void ExtraMouseSample(float frametime, bool active) = 0;
	virtual bool WriteUsercmdDeltaToBuffer(bf_write* buf, int from, int to, bool isnewcommand) = 0;
	virtual void EncodeUserCmdToBuffer(bf_write& buf, int slot) = 0;
	virtual void DecodeUserCmdFromBuffer(bf_read& buf, int slot) = 0;
	virtual void View_Render(vrect_t* rect) = 0;
	virtual void RenderView(const CViewSetup& view, int nClearFlags, int whatToDraw) = 0;
	virtual void View_Fade(ScreenFade_t* pSF) = 0;
	virtual void SetCrosshairAngle(const QAngle& angle) = 0;
	virtual void InitSprite(CEngineSprite* pSprite, const char* loadname) = 0;
	virtual void ShutdownSprite(CEngineSprite* pSprite) = 0;
	virtual int GetSpriteSize(void) const = 0;
	virtual void VoiceStatus(int entindex, qboolean bTalking) = 0;
	virtual void InstallStringTableCallback(char const* tableName) = 0;
	virtual void FrameStageNotify(ClientFrameStage_t curStage) = 0;
	virtual bool DispatchUserMessage(int msg_type, bf_read& msg_data) = 0;
	virtual CSaveRestoreData* SaveInit(int size) = 0;
	virtual void SaveWriteFields(CSaveRestoreData*, const char*, void*, datamap_t*, typedescription_t*, int) = 0;
	virtual void SaveReadFields(CSaveRestoreData*, const char*, void*, datamap_t*, typedescription_t*, int) = 0;
	virtual void PreSave(CSaveRestoreData*) = 0;
	virtual void Save(CSaveRestoreData*) = 0;
	virtual void WriteSaveHeaders(CSaveRestoreData*) = 0;
	virtual void ReadRestoreHeaders(CSaveRestoreData*) = 0;
	virtual void Restore(CSaveRestoreData*, bool) = 0;
	virtual void DispatchOnRestore() = 0;
	virtual CStandardRecvProxies* GetStandardRecvProxies() = 0;
	virtual void WriteSaveGameScreenshot(const char* pFilename) = 0;
	virtual void EmitSentenceCloseCaption(char const* tokenstream) = 0;
	virtual void EmitCloseCaption(char const* captionname, float duration) = 0;
	virtual bool CanRecordDemo(char* errorMsg, int length) const = 0;
	virtual void OnDemoRecordStart(char const* pDemoBaseName) = 0;
	virtual void OnDemoRecordStop() = 0;
	virtual void OnDemoPlaybackStart(char const* pDemoBaseName) = 0;
	virtual void OnDemoPlaybackStop() = 0;
	virtual bool ShouldDrawDropdownConsole() = 0;
	virtual int GetScreenWidth() = 0;
	virtual int GetScreenHeight() = 0;
	virtual void WriteSaveGameScreenshotOfSize(const char* pFilename, int width, int height, bool bCreatePowerOf2Padded = false, bool bWriteVTF = false) = 0;
	virtual bool GetPlayerView(CViewSetup& playerView) = 0;
	virtual void SetupGameProperties(CUtlVector< XUSER_CONTEXT >& contexts, CUtlVector< XUSER_PROPERTY >& properties) = 0;
	virtual unsigned int GetPresenceID(const char* pIDName) = 0;
	virtual const char* GetPropertyIdString(const unsigned int id) = 0;
	virtual void GetPropertyDisplayString(unsigned int id, unsigned int value, char* pOutput, int nBytes) = 0;
	virtual void StartStatsReporting(HANDLE handle, bool bArbitrated) = 0;
	virtual void InvalidateMdlCache() = 0;
	virtual void IN_SetSampleTime(float frametime) = 0;
	virtual void ReloadFilesInList(IFileList* pFilesToReload) = 0;
	virtual bool HandleUiToggle() = 0;
	virtual bool ShouldAllowConsole() = 0;
	virtual CRenamedRecvTableInfo* GetRenamedRecvTableInfos() = 0;
	virtual CMouthInfo* GetClientUIMouthInfo() = 0;
	virtual void FileReceived(const char* fileName, unsigned int transferID) = 0;
	virtual const char* TranslateEffectForVisionFilter(const char* pchEffectType, const char* pchEffectName) = 0;
	virtual void ClientAdjustStartSoundParams(struct StartSoundParams_t& params) = 0;
	virtual bool DisconnectAttempt(void) = 0;
	virtual bool IsConnectedUserInfoChangeAllowed(IConVar* pCvar) = 0;
};

VERSION_INTERFACE(BaseClientDLL, IBaseClientDLL*, "client.dll", "VClient017");

#endif