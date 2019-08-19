import * as AddonType from './types';

const Addon: typeof AddonType = require('./Release/bitset.node');

console.dir(Addon, {
    depth: 5
});

export = Addon;