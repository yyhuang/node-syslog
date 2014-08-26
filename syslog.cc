#include <node.h>
#include "node-syslog.h"

using namespace v8;

Handle<Value> CreateObject(const Arguments& args) {
  HandleScope scope;
  return scope.Close(NodeSyslog::NewInstance(args));
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  NodeSyslog::Init();

  module->Set(String::NewSymbol("exports"),
      FunctionTemplate::New(CreateObject)->GetFunction());
}

NODE_MODULE(syslog, InitAll)
