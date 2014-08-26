#ifndef NODE_SYSLOG_H
#define NODE_SYSLOG_H

#include <node.h>
#include <string>

class NodeSyslog: node::ObjectWrap {

public:
    static void Init();
    static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

private:
    NodeSyslog();
    ~NodeSyslog();

    static v8::Persistent<v8::Function> constructor;
    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> Log(const v8::Arguments& args);

    int options_;
    int facility_;
    std::string name_;
};

#endif
