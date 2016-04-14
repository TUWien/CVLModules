/* File : transkribus_interfaces.i */
%module transkribus_interfaces

%include "image.i"
/*%include "arrays_java.i";*/

%include "std_vector.i"

namespace std {
   %template(StringVector) vector<string>;
};

%include "various.i"

%apply char **STRING_ARRAY { char **db }

%{
#include "../cpp/IBaseLine2Coords.h"
#include "../cpp/ILayoutAnalysis.h"
#include "../cpp/IHtr.h"
#include "../cpp/ModuleFactory.h"
%}

%rename (Native_IModule) IModule;
%rename (Native_IBaseline2Coords) IBaseline2Coords;
%rename (Native_ILayoutAnalysis) ILayoutAnalysis;
%rename (Native_IHtr) IHtr;

%rename (Native_ModuleFactory) ModuleFactory;

//%ignore LayoutAnalysisFactory;
//%ignore HtrFactory;

/* Let's just grab the original header files here */
%include "../cpp/IModule.h"
%include "../cpp/IBaseLine2Coords.h"
%include "../cpp/ILayoutAnalysis.h"
%include "../cpp/IHtr.h"
%include "../cpp/ModuleFactory.h"

