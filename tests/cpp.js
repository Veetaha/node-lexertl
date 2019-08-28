const {Rules} = require('../dist/bin-cpp/Debug/linux-x64/node-v72/napi-v4/lexertlts.node');
// (() => {
// for (let i = 0; i < 10; ++i) {
//     try {
try {new Rules([{regex: '12', id: 2 ** 16 }]) } catch (err) {}
try {new Rules([{regex: '12', id: 2 ** 16 + 1 }]) }catch (err) {}
//     } catch (err) {}
// }
setTimeout(() => {}, 6000)
