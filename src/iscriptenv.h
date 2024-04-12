#pragma once

struct IScriptEnv {
	virtual void setup() = 0;
	virtual void draw() = 0;
};
