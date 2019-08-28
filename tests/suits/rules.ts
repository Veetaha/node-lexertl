import { Rules } from '../helpers/index';

describe('Rules', () => {

    describe('constructor', () => {

        it('should throw on values not in range of uint16_t', () => {
            [2 ** 16, -1, NaN, Infinity, -Infinity].forEach(outOfRange => {
                console.log('testing ', outOfRange);
                expect(() => new Rules([{regex: 'a', id: outOfRange }]))
                    .toThrow(/value of .*? is out of destination's type range/);
            });
        });
    });
});

