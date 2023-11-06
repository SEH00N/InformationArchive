#pragma once

#define SINGLE(type)				\
public:								\
	static type* GetInstance() {	\
		static type instance;		\
		return &instance;			\
	}								\
									\
private:							\
	type() {}						\
	~type() {}						

#define Deg2Rad 3.14f / 180.f
#define Rad2Deg 180.f / 3.14f

#define RECT_RENDER(hdc, posX, posY, scaleX, scaleY) Rectangle(hdc, posX - scaleX / 2, posY - scaleY / 2, posX + scaleX / 2, posY + scaleY / 2)
#define ELLIPSE_RENDER(hdc, posX, posY, scaleX, scaleY) Ellipse(hdc, posX - scaleX / 2, posY - scaleY / 2, posX + scaleX / 2, posY + scaleY / 2)
#define RECT_MAKE(posX, posY, scaleX, scaleY) { posX - scaleX / 2, posY - scaleY / 2, posX + scaleX / 2, posY + scaleY / 2 }

#define WINDOW_CLASS_NAME L"SEH00N"

#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720

#define DeltaTime TimeManager::GetInstance()->GetDeltaTime()

#define GetKeyState(key, state) KeyManager::GetInstance()->GetKey(key) == state

#define GetKeyNone(key) GetKeyState(key, KeyState::None)
#define GetKeyDown(key) GetKeyState(key, KeyState::Down)
#define GetKeyUp(key) GetKeyState(key, KeyState::Up)
#define GetKeyPress(key) GetKeyState(key, KeyState::Press)

//#define SINGLE(type) public: static type& GetInstance() { static type instance; return instance; } private: type() {} ~type() {}