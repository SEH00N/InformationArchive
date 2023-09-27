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

#define RECT_RENDER(hdc, posX, posY, scaleX, scaleY) Rectangle(hdc, posX - scaleX / 2, posY - scaleY / 2, posX + scaleX / 2, posY + scaleY / 2)
#define RECT_MAKE(posX, posY, scaleX, scaleY) { posX - scaleX / 2, posY - scaleY / 2, posX + scaleX / 2, posY + scaleY / 2 }

#define WINDOW_CLASS_NAME L"SEH00N"

#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720

//#define SINGLE(type) public: static type& GetInstance() { static type instance; return instance; } private: type() {} ~type() {}