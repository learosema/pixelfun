#include "quickjsenv.h"
#include <quickjs.h>

QuickJSEnv::QuickJSEnv(const std::string& code, ICanvas& api)
{
	m_pRuntime = std::make_shared<qjs::Runtime>();
	m_pContext = std::make_shared<qjs::Context>(*m_pRuntime);


	auto &module = m_pContext->addModule("p5-alike");



	m_pContext->eval(R"script(
		const WIDTH = 320;
		const HEIGHT = 200;

		function setup() {}
		function draw() {}
	)script");
	m_pContext->eval(code);
	m_code = code;
}

void QuickJSEnv::setup()
{
	tryCall("setup");
}

void QuickJSEnv::draw()
{
	tryCall("draw");
}


void QuickJSEnv::tryCall(const std::string &functionName)
{
	auto jsVal = m_pContext->eval(functionName);
	if (! JS_IsFunction(m_pContext->ctx, jsVal.v)) {
		return;
	}
	auto fun = (std::function<void()>)jsVal;
	fun();
}
