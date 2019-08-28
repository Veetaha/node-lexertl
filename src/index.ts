import Path from 'path';
import * as Npg from 'node-pre-gyp';

export = require(Npg.find(Path.resolve(Path.join(
    __dirname, '../package.json'
)))) as typeof import('./types');
