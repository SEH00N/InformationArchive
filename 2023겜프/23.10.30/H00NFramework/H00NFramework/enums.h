#pragma once

enum class KeyState { None, Down, Up, Press };
enum class KeyType 
{ 
	Left, Right, Up, Down, Q, 
	W, E, R, T, Y, U, I, O, P, 
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M, Ctrl, 
	LAlt, LShift, Space, Return,
	Tab, Escape, LButton, RButton, 
	LAST
};

enum class ObjectGroup {
	Default,
	Player,
	Bullet,
	Monster,
	LAST = 30
};