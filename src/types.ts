export interface IRule<TId extends number = number> {
    regex: string;
    id:    TId;
    // TODO: add more properties
}

export declare class Rules<TId extends number = number> {

    constructor(initialRules: Iterable<IRule<TId>>);

    push(rule: IRule<TId>): void;

}