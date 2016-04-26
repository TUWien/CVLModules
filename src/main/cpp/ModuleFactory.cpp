
#include "ModuleFactory.h"

#include <iostream>
#include <stdexcept>

#ifndef WIN32
#include <dlfcn.h>
#else
#include <windows.h>
#endif

namespace transkribus {

const std::string ModuleFactory::FACTORY_VARIABLE_NAME = "ModuleFactoryInstance";

void* ModuleFactory::loadLibrary(const std::string& libName) {

	void* library_handle = 0;

#ifndef WIN32
	library_handle = dlopen(libName.c_str(), RTLD_NOW | RTLD_GLOBAL);

	if (!library_handle) {
		throw std::runtime_error("cannot load library "+libName+" error: "+dlerror());
	}

#else
	library_handle = LoadLibrary(libName.c_str());

	if (!library_handle) {
		throw std::runtime_error("cannot load library " + libName);
	}
#endif

	return library_handle;
}

#ifndef WIN32

IModule* ModuleFactory::createModuleFromLib(const std::string& pathToLib, const std::vector<std::string>& pars)
{
	ModuleFactory* factory;

	std::cout << "opening lib: " << pathToLib << std::endl;

	// diem: see http://man7.org/linux/man-pages/man3/dlopen.3.html
	// "...so a dynamically loaded shared object is
	// not deallocated until dlclose() has been called on it as many times
	// as dlopen() has succeeded on it"
	// - I think we need to make void* library_handle a member variable (that is closed on destruction)
	// - this function should therefore not be static

	void* library_handle = loadLibrary(pathToLib);
	factory = (ModuleFactory*) dlsym(library_handle, FACTORY_VARIABLE_NAME.c_str());
	if (factory == NULL) {
		// diem: this runtime exception is crucial since nobody frees the library (hence memory is lost here)
		throw std::runtime_error("error extracting factory instance '" + FACTORY_VARIABLE_NAME + "' from lib " + pathToLib + " - error: " + dlerror());
	}

	return factory->create(pars);
}

#else

IModule* ModuleFactory::createModuleFromLib(const std::string& pathToLib, const std::vector<std::string>& pars)
{
	ModuleFactory* factory;
	std::cout << "opening lib: " << pathToLib << std::endl;

	HINSTANCE library_handle = LoadLibrary(pathToLib.c_str());

	if (!library_handle) {
		std::cout << "could not load" << pathToLib << std::endl;
		return 0;
	}

	factory = (ModuleFactory*) GetProcAddress(library_handle, FACTORY_VARIABLE_NAME.c_str());

	if (factory == NULL) {
		FreeLibrary(library_handle);
		std::cerr << "cannot load factory instance - google this: GetProcAddress " << GetLastError();
		throw std::runtime_error("error extracting factory instance '" + FACTORY_VARIABLE_NAME + "' from lib " + pathToLib);
	}

	return factory->create(pars);
}

#endif

//ILayoutAnalysis* PluginFactory::createLayoutAnalysis(const std::string& pathToLib)
//{
//	LayoutAnalysisFactory* factory;
//
//	cout << "opening layout analysis lib: " << pathToLib << endl;
//
//	void* library_handle = loadLibrary(pathToLib);
//	factory = (LayoutAnalysisFactory*) dlsym(library_handle, FACTORY_VARIABLE_NAME.c_str());
//	if (factory == NULL) {
//		throw runtime_error("error extracting variable " + FACTORY_VARIABLE_NAME + " from lib "+pathToLib+" - error: "+dlerror());
//	}
//
//	return factory->create();
//}


}
