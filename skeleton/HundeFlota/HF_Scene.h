#pragma once
class HF_Scene
{
public: 
	HF_Scene() {}
	~HF_Scene() {}
	void init();
	void update(double t);
	void cleanup();

	void onKeyPress(unsigned char key); 
};

