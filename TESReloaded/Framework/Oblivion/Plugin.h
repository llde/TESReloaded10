#pragma once

class CommandInfo;

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