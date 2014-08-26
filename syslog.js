var syslog = require('./build/Release/syslog');

module.exports = {
  Logger: syslog,
  debug: 7,
  info: 6,
  notice: 5,
  warning: 4,
  error: 3,
  crit: 2,
  alert: 1,
  emerg: 0
};
