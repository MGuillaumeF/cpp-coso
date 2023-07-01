import { existsSync, readFileSync, writeFileSync } from 'fs';
import path from 'path';

/**
 * 
 * @param manifestPath 
 * @param newVersion 
 */
function updateJsonManifest(manifestPath : string, newVersion : string) {
    const manifestPathResolved=path.resolve(__dirname, manifestPath)
    if (!existsSync(manifestPath)) {
        throw new Error(`file ${manifestPath} not found, version cannot be updated`, {cause : "ENOENTRY"})
    }
    const currentContent = JSON.parse(readFileSync(manifestPathResolved).toString());
    currentContent.version = newVersion
    writeFileSync(manifestPathResolved, JSON.stringify(currentContent, null, 2));
}
/**
 * 
 * @param filepath 
 * @param newVersion 
 * @param pattern 
 * @param options 
 */
function updateTxtFile(filepath : string, newVersion : string, pattern : RegExp, options? : {prefix?: string, suffix ?: string}) {
    const filePathResolved=path.resolve(__dirname, filepath)
    if (!existsSync(filePathResolved)) {
        throw new Error(`file ${filePathResolved} not found, version cannot be updated`, {cause : "ENOENTRY"})
    }
    const currentContent = readFileSync(filePathResolved).toString();

    const versionToInsert = [options?.prefix, newVersion, options?.suffix].filter(value => value !== undefined).join('')
    const updatedContent = currentContent.replace(pattern, versionToInsert);
    writeFileSync(filePathResolved, updatedContent);
}

/**
 * 
 * @param filepath 
 * @param newVersion 
 */
function updateCMakeListsFile(filepath : string, newVersion : string) {
    updateTxtFile(filepath, newVersion, /(project\(\S+ VERSION ")\d+\.\d+.\d+(?:\.\d+)?(?:\-\S+)("\))/, {prefix: '$1', suffix : '$2'})
}

(function main() {
    try {
        if (process.argv.length != 3) {
            throw new Error(`Arguments must be 3`, {cause : "EBADUSAGE"})
        }
        const newVersion = process.argv.pop();
        if (newVersion != undefined) { 
            const filePathResolved=path.resolve(__dirname, "project-update.config.json")
            if (!existsSync(filePathResolved)) {
                throw new Error(`file ${filePathResolved} not found, version cannot be updated`, {cause : "ENOENTRY"})
            }
            const currentContent = JSON.parse(readFileSync(filePathResolved).toString());
            if (currentContent?.npm?.length > 0) {
                currentContent.npm.forEach((filepath : string) : void => {
                    updateJsonManifest(path.resolve(filepath, 'package.json'), newVersion);
                })
            }
            if (currentContent?.vcpkg?.length > 0) {
                currentContent.vcpkg.forEach((filepath : string) : void => {
                    updateJsonManifest(path.resolve(filepath, 'vcpkg.json'), newVersion);
                })
            }
            if (currentContent?.cmake?.length > 0) {
                currentContent.cmake.forEach((filepath : string) : void => {
                    updateCMakeListsFile(path.resolve(filepath, 'CMakeLists.txt'), newVersion);
                })
            }
            if (currentContent?.custom?.length > 0) {
                currentContent.custom.forEach((params : {file : string, pattern : string, prefix ?: string, suffix ?: string}) : void => {
                    updateTxtFile(params.file, newVersion, new RegExp(params.pattern), {prefix : params.prefix,  suffix : params.suffix });
                })
            }
        } else {
            throw new Error(`version not found on command`, {cause : "ENOENTRY"}) 
        }
    } catch (e) {
        console.error('update failed', e)
    }

})();