/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.7
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package eu.transkribus.interfaces.native_wrapper.swig;

public class Native_ModuleFactory {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Native_ModuleFactory(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Native_ModuleFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        transkribus_interfacesJNI.delete_Native_ModuleFactory(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static String getFACTORY_VARIABLE_NAME() {
    return transkribus_interfacesJNI.Native_ModuleFactory_FACTORY_VARIABLE_NAME_get();
  }

  public Native_IModule create(StringVector pars) {
    long cPtr = transkribus_interfacesJNI.Native_ModuleFactory_create(swigCPtr, this, StringVector.getCPtr(pars), pars);
    return (cPtr == 0) ? null : new Native_IModule(cPtr, false);
  }

  public static Native_IModule createModuleFromLib(String pathToLib, StringVector pars) {
    long cPtr = transkribus_interfacesJNI.Native_ModuleFactory_createModuleFromLib(pathToLib, StringVector.getCPtr(pars), pars);
    return (cPtr == 0) ? null : new Native_IModule(cPtr, false);
  }

  public static Native_ILayoutAnalysis castILayoutAnalysis(Native_IModule module) {
    long cPtr = transkribus_interfacesJNI.Native_ModuleFactory_castILayoutAnalysis(Native_IModule.getCPtr(module), module);
    return (cPtr == 0) ? null : new Native_ILayoutAnalysis(cPtr, false);
  }

  public static Native_IHtr castIHtr(Native_IModule module) {
    long cPtr = transkribus_interfacesJNI.Native_ModuleFactory_castIHtr(Native_IModule.getCPtr(module), module);
    return (cPtr == 0) ? null : new Native_IHtr(cPtr, false);
  }

  public static Native_IBaseline2Polygon castIBaseline2Coords(Native_IModule module) {
    long cPtr = transkribus_interfacesJNI.Native_ModuleFactory_castIBaseline2Coords(Native_IModule.getCPtr(module), module);
    return (cPtr == 0) ? null : new Native_IBaseline2Polygon(cPtr, false);
  }

  public static Native_ITrainHtr castITrainHtr(Native_IModule module) {
    long cPtr = transkribus_interfacesJNI.Native_ModuleFactory_castITrainHtr(Native_IModule.getCPtr(module), module);
    return (cPtr == 0) ? null : new Native_ITrainHtr(cPtr, false);
  }

  public Native_ModuleFactory() {
    this(transkribus_interfacesJNI.new_Native_ModuleFactory(), true);
  }

}