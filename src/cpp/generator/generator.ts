import { Rules } from '../rules/rules';
import { StateMachine } from '../state-machine/state-machine';

export declare namespace Generator {
    export function build(rules: Rules, sm: StateMachine): void;
}