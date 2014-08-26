node-syslog
===========

a small practice for node syslog addon
=======

## Install

node-gyp configure build

## Usage

var syslog = require('syslog');

var logger = syslog.Logger();

logger.log(syslog.error, 'log message');
