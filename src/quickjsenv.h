#pragma once

#include "iscriptenv.h"
#include "quickjspp.hpp"
#include "icanvas.h"

class QuickJSEnv: IScriptEnv {
public:
	QuickJSEnv(const std::string& code, ICanvas& api);

	void setup();

	void draw();

private:

	void tryCall(const std::string& functionName);

	std::shared_ptr<qjs::Runtime> m_pRuntime;
	std::shared_ptr<qjs::Context> m_pContext;
	std::string m_code;
};
