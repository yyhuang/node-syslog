#include <node.h>
#include <syslog.h>
#include "node-syslog.h"

using namespace v8;

NodeSyslog::NodeSyslog()
:options_(LOG_PID), facility_(LOG_LOCAL0), name_("node-syslog") {
}

NodeSyslog::~NodeSyslog() {
}

Persistent<Function> NodeSyslog::constructor;

void NodeSyslog::Init() {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("NodeSyslog"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // prototype
    tpl->PrototypeTemplate()->Set(String::NewSymbol("log"),
        FunctionTemplate::New(Log)->GetFunction());

    constructor = Persistent<Function>::New(tpl->GetFunction());
}

Handle<Value> NodeSyslog::NewInstance(const Arguments& args) {
    HandleScope scope;

    const unsigned argc = 3;
    Handle<Value> argv[argc] = { args[0], args[1], args[2] };
    Local<Object> instance = constructor->NewInstance(argc, argv);

    return scope.Close(instance);
}

Handle<Value> NodeSyslog::New(const Arguments& args) {
    HandleScope scope;

    NodeSyslog* nodesyslog = new NodeSyslog();
    if (args[0]->IsString()) {
        String::AsciiValue string(args[0]);
        nodesyslog->name_ = *string;
    }

    if (args[1]->IsNumber()) {
        nodesyslog->options_ = args[1]->Int32Value();
    }

    if (args[2]->IsNumber()) {
        nodesyslog->facility_ = args[2]->Int32Value();
    }

    nodesyslog->Wrap(args.This());

    return args.This();
}

Handle<Value> NodeSyslog::Log(const Arguments& args) {
    HandleScope scope;
    NodeSyslog* nodesyslog = ObjectWrap::Unwrap<NodeSyslog>(args.This());

    int level = LOG_INFO;
    if (args[0]->IsNumber()) {
        level = args[0]->Int32Value();
    }

    if (args[1]->IsString()) {
        openlog(nodesyslog->name_.c_str(), nodesyslog->options_, nodesyslog->facility_);
        String::AsciiValue message(args[1]);
        syslog(level, "%s", *message);
        closelog();
    }

    return scope.Close(Undefined());
}
