const addon = require('..');
const should = require('should');
const os = require('os');

describe('Addon', function () {
  it('should export symbols', function (done) {
    should.exist(addon.ether_ntoa);
    should.exist(addon.ether_aton);
    done();
  });
});

describe('ether_ntoa', function () {
  it('should throw an Error on invalid arguments', function (done) {
    (function () { addon.ether_ntoa(); }).should.throw();
    (function () { addon.ether_ntoa(null); }).should.throw();
    (function () { addon.ether_ntoa(1, 2); }).should.throw();
    (function () { addon.ether_ntoa('AAAAA'); }).should.throw();
    done();
  });

  it('should process buffers', function (done) {
    should.equal(addon.ether_ntoa(Buffer.from([-85, 11, 28, 13, 62, -17])), 'ab:b:1c:d:3e:ef');
    done();
  });
});

describe('ether_aton', function () {
  it('should throw an Error on invalid arguments', function (done) {
    (function () { addon.ether_aton(); }).should.throw();
    (function () { addon.ether_aton(null); }).should.throw();
    (function () { addon.ether_aton(1, 2); }).should.throw();
    done();
  });

  it('should throw an Error on invalid inputs', function (done) {
    (function () { addon.ether_aton(''); }).should.throw();
    (function () { addon.ether_aton('::'); }).should.throw();
    (function () { addon.ether_aton('1:2:3:4:5:6:7'); }).should.throw();
    done();
  });

  it('should process ethernet addresses', function (done) {
    should.equal(addon.ether_aton('ab:0b:1c:d:3e:ef').toString('hex'), 'ab0b1c0d3eef');
    done();
  });

});

