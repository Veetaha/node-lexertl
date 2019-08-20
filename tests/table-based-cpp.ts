import { StateMachine, TableBasedCpp, Rules, Generator } from '../dist';


describe('TableBasedCpp.generateCpp()', () => {
    it('should generate cpp code according to lexertl api', () => {
        const enum TokenType { Invalid, Number, Identifier }

        const rules = new Rules<TokenType>([
            { regex: "[0-9]+", id: TokenType.Number },
            { regex: "[a-z]+", id: TokenType.Identifier}
        ]);
        
        const sm = new StateMachine;

        Generator.build(rules, sm);

        sm.minimize();

        const gen = TableBasedCpp.generateCpp("lookup", sm);

        console.log("GENERATED: ", gen);
    });
})