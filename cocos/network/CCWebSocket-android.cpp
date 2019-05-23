//
// Created by jiang on 19-5-22.
//

#include "network/CCWebSocket-android.h"

#include "network/WebSocket.h"
#include "platform/android/jni/JniHelper.h"


#define JCLS_WEBSOCKET "org/cocos2dx/lib/Cocos2dxWebSocket"
#define J_BINARY_CLS_WEBSOCKET "org.cocos2dx.lib.Cocos2dxWebSocket"
#define JARG_STR        "Ljava/lang/String;"
#define JARG_DOWNLOADER "L" JCLS_WEBSOCKET ";"
#define JARG_TASK       "L" JCLS_TASK ";"

#include <string>
#include <mutex>
#include <unordered_map>

using namespace std;


static std::unordered_map<int64_t, cocos2d::network::WebSocket *> socketMap;

namespace cocos2d{

    static void _nativeTriggerEvent(::JNIEnv *env, ::jclass *klass, ::jlong cid, ::jstring eventName, ::jstring data, ::jboolean isBinary) {
        auto itr = socketMap.find(cid);
        if(itr != socketMap.end())
        {
            const char *ceventName = env->GetStringUTFChars(eventName, nullptr);
            const char *cdata = env->GetStringUTFChars(data, nullptr);
            itr->second->triggerEvent(ceventName, cdata, (bool)isBinary);
            env->ReleaseStringUTFChars(eventName, ceventName);
            env->ReleaseStringUTFChars(data, cdata);
        }
    }

    int64_t _callJavaConnect(const std::string &url,const std::vector<std::string> *protocals, const std::string & caFile)
    {
        jlong connectionID = -1;
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           J_BINARY_CLS_WEBSOCKET,
                                           "connect",
                                           "(" JARG_STR "[" JARG_STR JARG_STR")J")) {
            jstring jurl = methodInfo.env->NewStringUTF(url.c_str());
            jstring jcaFile = methodInfo.env->NewStringUTF(caFile.c_str());

            jclass stringClass = methodInfo.env->FindClass("java/lang/String");

            size_t protocalLength = protocals == nullptr ? 0 : protocals->size();

            jobjectArray jprotocals = methodInfo.env->NewObjectArray((jsize)protocalLength, stringClass, methodInfo.env->NewStringUTF(""));
            for(int i = 0 ; i < protocalLength ; i++ )
            {
                jstring item = methodInfo.env->NewStringUTF(protocals->at(i).c_str());
                methodInfo.env->SetObjectArrayElement(jprotocals, i, item);
            }

            connectionID = methodInfo.env->CallStaticLongMethod(methodInfo.classID, methodInfo.methodID, jurl, jprotocals, jcaFile);
            methodInfo.env->DeleteLocalRef(jurl);
            methodInfo.env->DeleteLocalRef(jcaFile);
            methodInfo.env->DeleteLocalRef(stringClass);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }

        return connectionID;
    }

    void _callJavaDisconnect(int64_t cid)
    {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           J_BINARY_CLS_WEBSOCKET,
                                           "disconnect",
                                           "(J)V")) {
            jlong connectionID = cid;
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, connectionID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }

    }


    void _callJavaSendBinary(int64_t cid, const unsigned char *data, size_t len)
    {

        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           J_BINARY_CLS_WEBSOCKET,
                                           "sendBinary",
                                           "(J[B)V")) {
            jlong connectionID = cid;
            jbyteArray jdata = methodInfo.env->NewByteArray((jsize)len);
            methodInfo.env->SetByteArrayRegion(jdata, 0, (jsize)len, (const jbyte *)data);
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, connectionID, jdata);
            methodInfo.env->DeleteLocalRef(jdata);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }

    }

    void _callJavaSendString(int64_t cid, const std::string &data) {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           J_BINARY_CLS_WEBSOCKET,
                                           "sendString",
                                           "(J"  JARG_STR ")V")) {
            jlong connectionID = cid;
            jstring jdata = methodInfo.env->NewStringUTF(data.c_str());
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, connectionID, jdata);
            methodInfo.env->DeleteLocalRef(jdata);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }

    static JNINativeMethod sMethodTable[] = {
            { "triggerEvent", "(J" JARG_STR JARG_STR "Z)V", (void*)_nativeTriggerEvent}
    };

    static bool _registerNativeMethods(JNIEnv* env)
    {
        jclass clazz = env->FindClass(JCLS_WEBSOCKET);
        if (clazz == nullptr)
        {
            CCLOGERROR("_registerNativeMethods: can't find java class:%s", JARG_DOWNLOADER);
            return false;
        }
        if (JNI_OK != env->RegisterNatives(clazz, sMethodTable, sizeof(sMethodTable) / sizeof(sMethodTable[0])))
        {
            CCLOGERROR("_registerNativeMethods: failed");
            if (env->ExceptionCheck())
            {
                env->ExceptionClear();
            }
            return false;
        }
        return true;
    }
}


namespace cocos2d {
    static bool registered = false;


    namespace network {
        void _preloadJavaWebSocketClass()
        {
            if(!registered)
            {
                registered = _registerNativeMethods(JniHelper::getEnv());
            }
        }

        WebSocket::WebSocket()
        {

        }

        WebSocket::~WebSocket()
        {
            if(_connectionID > 0)
            {
                socketMap.erase(_connectionID);
            }
        }

        void WebSocket::closeAllConnections()
        {

        }

        bool WebSocket::init(const cocos2d::network::WebSocket::Delegate &delegate,
                             const std::string &url, const std::vector<std::string> *protocols,
                             const std::string &caFilePath) {

            _delegate = const_cast<Delegate*>(&delegate);
            _url = url;
            _caFilePath = caFilePath;
            _readyState = State::CONNECTING;

            if(_url.empty()) return false;

            _connectionID = _callJavaConnect(url, protocols, caFilePath);

            if(_connectionID > 0)
            {
                socketMap.emplace(_connectionID, this);
            }

            return true;
        }

        void WebSocket::send(const std::string &message)
        {
            _callJavaSendString(_connectionID, message);
        }

        void WebSocket::send(const unsigned char *binaryMsg, unsigned int len)
        {
            _callJavaSendBinary(_connectionID, binaryMsg, len);
        }

        void WebSocket::close()
        {
            //TODO, wait for result
            _callJavaDisconnect(_connectionID);
        }

        void WebSocket::closeAsync()
        {
            _callJavaDisconnect(_connectionID);
        }

        void WebSocket::triggerEvent(const std::string &eventName, const std::string &data,
                                     bool binary)
                                     {

            if(eventName == "open")
            {
                std::lock_guard<std::mutex> guard(_readyStateMutex);
                _readyState = State::OPEN;
                _delegate->onOpen(this);
            }
            else if(eventName == "message")
            {
                Data msg;
                msg.bytes = const_cast<char*>(data.c_str());
                msg.len = data.size();
                msg.isBinary = binary;
                _delegate->onMessage(this, msg);
            }
            else if(eventName == "closing")
            {
                std::lock_guard<std::mutex> guard(_readyStateMutex);
                _readyState = State::CLOSING;
            }
            else if(eventName == "closed")
            {
                std::lock_guard<std::mutex> guard(_readyStateMutex);
                _readyState = State::CLOSED;
                _delegate->onClose(this);
            }
            else if(eventName == "error")
            {
                std::lock_guard<std::mutex> guard(_readyStateMutex);
                _readyState = State::CLOSED;
                //TODO get reason
                _delegate->onError(this, ErrorCode::UNKNOWN);
            }
            else
            {
                CCLOGERROR("WebSocket invalidate event name %s", eventName.c_str());
            }

        }

        WebSocket::State WebSocket::getReadyState() {
            return _readyState;
        }
    }
}

