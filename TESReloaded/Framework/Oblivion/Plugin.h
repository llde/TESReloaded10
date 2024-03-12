#pragma once

class CommandInfo;
enum CommandReturnType : UInt8
{
	kRetnType_Default,
	kRetnType_Form,
	kRetnType_String,
	kRetnType_Array,
	kRetnType_ArrayIndex,
	kRetnType_Ambiguous,

	kRetnType_Max
};

class PluginInterface {
public:
	enum Interface {
		kInterface_Console = 0,
		kInterface_Serialization,
		kInterface_StringVar,
		kInterface_IO,
		kInterface_Messaging,
		kInterface_ArrayVar,
		kInterface_CommandTable,
		kInterface_Script,
	};

	UInt32	Version;
	UInt32	GameVersion;
	UInt32	EditorVersion;
	UInt32	IsEditor;

	bool	(*RegisterCommand)(CommandInfo* Info);
	void	(*SetOpcodeBase)(UInt32 Opcode);
	void*	(*QueryInterface)(UInt32 ID);
	UInt32  (*GetPluginHandle)(void);
	bool	(*RegisterTypedCommand)(CommandInfo* info, CommandReturnType retnType);
	const char* (*GetOblivionDirectory)();
	bool	(*GetPluginLoaded)(const char* pluginName);
	UInt32  (*GetPluginVersion)(const char* pluginName);

};

class PluginInfo {
public:
	enum {
		kInfoVersion = 2
	};

	UInt32		InfoVersion;
	const char* Name;
	UInt32		Version;
};

class CommandTableInterface {
public:
	CommandInfo* (*Start)();
	CommandInfo* (*End)();
	CommandInfo* (*GetByOpcode)(UInt32 Opcode);
	CommandInfo* (*GetByName)(const char* Name);
	UInt32		 (*GetReturnType)(CommandInfo* Info);
	UInt32		 (*GetRequiredOBSEVersion)(CommandInfo* Info);
	PluginInfo*  (*GetParentPlugin)(CommandInfo* Info);
};

struct OBSEMessagingInterface
{
	struct Message {
		const char* sender;
		UInt32		type;
		UInt32		dataLen;
		void* data;
	};

	using EventCallback = void (*)(Message*);

	enum {
		kVersion = 1
	};

	UInt32	version;
	bool	(*RegisterListener)(UInt32 listener, const char* sender, EventCallback handler);
	bool	(*Dispatch)(UInt32 sender, UInt32 messageType, void* data, UInt32 dataLen, const char* receiver);
};
