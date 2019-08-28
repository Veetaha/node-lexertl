declare module 'node-pre-gyp' {

    /** 
     * Returns path to C++ native NodeJS addon based on package.json settings 
     * set according to 'node-pre-gyp' requirements.
     */
    export function find(packageJsonPath: string): string;

}