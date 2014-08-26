var syslog = require('../syslog');

var logger = syslog.Logger();
logger.log(syslog.error, 'test log');
