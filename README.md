# node-ether-xtoy
a ether_aton, ether_ntoa bindings for Node.js

[![Node.js CI](https://github.com/PupilTong/node-ether-xtoy/actions/workflows/node.js.yml/badge.svg)](https://github.com/PupilTong/node-ether-xtoy/actions/workflows/node.js.yml)

# installation

`npm install ether-xtoy`

# examples
```javascript
const {ether_ntoa,ether_aton} = require('ether-xtoy');
//on amd64 linux
ether_ntoa(Buffer.from([-85, 11, 28, 13, 62, -17]);//returns ab:b:1c:d:3e:ef
ether_aton("ab:0b:1c:d:3e:ef");// returns Buffer.from([-85, 11, 28, 13, 62, -17]);
```

