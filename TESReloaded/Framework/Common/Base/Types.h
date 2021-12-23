#pragma once

typedef unsigned char		UInt8;
typedef unsigned short		UInt16;
typedef unsigned long		UInt32;
typedef unsigned long long	UInt64;
typedef signed char			SInt8;
typedef signed short		SInt16;
typedef signed long			SInt32;
typedef signed long long	SInt64;
typedef float				Float32;
typedef double				Float64;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> inline UInt32 ThisCall(UInt32 Method, void* Instance, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4, T5 Arg5, T6 Arg6, T7 Arg7, T8 Arg8, T9 Arg9) { class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3, T4, T5, T6, T7, T8, T9); } u = { Method }; return ((T*)Instance->*u.m)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9); }
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> inline UInt32 ThisCall(UInt32 Method, void* Instance, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4, T5 Arg5, T6 Arg6, T7 Arg7, T8 Arg8) { class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3, T4, T5, T6, T7, T8); } u = { Method }; return ((T*)Instance->*u.m)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8); }
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> inline UInt32 ThisCall(UInt32 Method, void* Instance, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4, T5 Arg5, T6 Arg6, T7 Arg7) { class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3, T4, T5, T6, T7); } u = { Method }; return ((T*)Instance->*u.m)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7); }
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> inline UInt32 ThisCall(UInt32 Method, void* Instance, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4, T5 Arg5, T6 Arg6) { class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3, T4, T5, T6); } u = { Method }; return ((T*)Instance->*u.m)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6); }
template <typename T1, typename T2, typename T3, typename T4, typename T5> inline UInt32 ThisCall(UInt32 Method, void* Instance, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4, T5 Arg5) { class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3, T4, T5); } u = { Method }; return ((T*)Instance->*u.m)(Arg1, Arg2, Arg3, Arg4, Arg5); }
template <typename T1, typename T2, typename T3, typename T4> inline UInt32 ThisCall(UInt32 Method, void* Instance, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4) { class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3, T4); } u = { Method }; return ((T*)Instance->*u.m)(Arg1, Arg2, Arg3, Arg4); }
template <typename T1, typename T2, typename T3> inline UInt32 ThisCall(UInt32 Method, void* Instance, T1 Arg1, T2 Arg2, T3 Arg3) { class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2, T3); } u = { Method }; return ((T*)Instance->*u.m)(Arg1, Arg2, Arg3); }
template <typename T1, typename T2> inline UInt32 ThisCall(UInt32 Method, void* Instance, T1 Arg1, T2 Arg2) { class T {}; union { UInt32 x; UInt32(T::* m)(T1, T2); } u = { Method }; return ((T*)Instance->*u.m)(Arg1, Arg2); }
template <typename T1> inline UInt32 ThisCall(UInt32 Method, void* Instance, T1 Arg1) { class T {}; union { UInt32 x; UInt32(T::* m)(T1); } u = { Method }; return ((T*)Instance->*u.m)(Arg1); }
inline UInt32 ThisCall(UInt32 Method, void* Instance) { class T {}; union { UInt32 x; UInt32(T::* m)(); } u = { Method }; return ((T*)Instance->*u.m)(); }

inline float ThisCallF(UInt32 Method, void* Instance) { class T {}; union { UInt32 x; float(T::* m)(); } u = { Method }; return ((T*)Instance->*u.m)(); }