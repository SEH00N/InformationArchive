#pragma once

#define SINGLE(type)				\
public:								\
	static type& GetInstance() {	\
		static type instance;		\
		return instance;			\
	}								\
									\
private:							\
	type() {}						\
	~type() {}						

//#define SINGLE(type) public: static type& GetInstance() { static type instance; return instance; } private: type() {} ~type() {}