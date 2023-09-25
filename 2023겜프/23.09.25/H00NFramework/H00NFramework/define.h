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

#define WINDOW_CLASS_NAME L"SEH00N"

#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720

//#define SINGLE(type) public: static type& GetInstance() { static type instance; return instance; } private: type() {} ~type() {}