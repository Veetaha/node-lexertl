import { StateMachine } from '../state-machine/state-machine';

export declare namespace TableBasedCpp {
    export function generateCpp(name: string, sm: StateMachine, pointers?: boolean): string;
}