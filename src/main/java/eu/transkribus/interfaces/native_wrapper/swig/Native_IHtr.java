/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.7
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */
package eu.transkribus.interfaces.native_wrapper.swig;

import eu.transkribus.interfaces.types.Image;

public class Native_IHtr extends Native_IModule {

    private transient long swigCPtr;

    protected Native_IHtr(long cPtr, boolean cMemoryOwn) {
        super(transkribus_interfacesJNI.Native_IHtr_SWIGUpcast(cPtr), cMemoryOwn);
        swigCPtr = cPtr;
    }

    protected static long getCPtr(Native_IHtr obj) {
        return (obj == null) ? 0 : obj.swigCPtr;
    }

    protected void finalize() {
        delete();
    }

    public synchronized void delete() {
        if (swigCPtr != 0) {
            if (swigCMemOwn) {
                swigCMemOwn = false;
                transkribus_interfacesJNI.delete_Native_IHtr(swigCPtr);
            }
            swigCPtr = 0;
        }
        super.delete();
    }
    
    public void process(String pathToOpticalModel, String pathToLanguageModel, String pathToCharacterMap, Native_Image image, String xmlInOut, String storageDir, StringVector lineIds, StringVector props) {
        transkribus_interfacesJNI.Native_IHtr_process(swigCPtr, this, pathToOpticalModel, pathToLanguageModel, pathToCharacterMap, Native_Image.getCPtr(image), image, xmlInOut, storageDir, StringVector.getCPtr(lineIds), lineIds, StringVector.getCPtr(props), props);
    }

}